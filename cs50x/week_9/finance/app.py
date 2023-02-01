import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():

    # Declare a variable that will increment
    increment = 0

    # Select all stocks present at the database where id is equal to the current loged in user
    stocks = db.execute(
        "SELECT * FROM stocks WHERE id = ?", session["user_id"])

    # Save the sum of all the brought stocks on a variable
    storage = db.execute(
        "SELECT sum(price_total) FROM stocks WHERE id = ?", session["user_id"])
    for item in storage:
        sum = item["sum(price_total)"]
        if sum:
            increment += 1

    # Select cash value present at the current account
    storage = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"])
    for item in storage:
        cash = item["cash"]

    if increment > 0:
        return render_template("index.html", stocks=stocks, sum=sum, cash=cash)
    else:
        return render_template("index_alt.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        # Check if given stock symbol exists in API database
        if not lookup(request.form.get("symbol")):
            return apology("Nothing has been found")

        # Check if given shares number is not fractal
        user_given_shares = request.form.get("shares")
        if not user_given_shares.isdigit():
            return apology("Invalid number of shares")

        # Check if given number of shares is a positive integer
        if int(request.form.get("shares")) <= 0:
            return apology("Invalid number of shares")

        # Declare a variable to receive the dictionary that is returned by lookup function
        stocks = lookup(request.form.get("symbol"))

        # Declare a variable to receive the amount of cash the current loged in user has
        storage = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])

        # A list of dictionaries will be received [{'cash': 10000}]
        # To access the value 10.000 we must first iterate the received list
        # And give the value of the received dictionary to another variable and cast a float onto it
        for item in storage:
            current_cash = float(item["cash"])

        # Update current cash value on variable
        shares = int(request.form.get("shares"))
        price = float(stocks["price"])
        current_cash = current_cash - (price * shares)

        if current_cash < 0:
            return apology("Not enough money!")

        # Update current cash value on database
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   current_cash, session["user_id"])

        # Update bought stock in "stocks" database ----------------------------------------->>>>>>>>

        # To do this, we must first store the value of the "fetchone()" function onto a variable and
        # Check if the returned value is none (That would mean that no item with said symbol exists)

        storage = db.execute(
            "SELECT * FROM stocks WHERE symbol = ? AND id = ?", stocks["symbol"], session["user_id"])
        increment = 0

        for item in storage:
            increment += 1

        # If check does not equal to none, we must update, else, we must insert
        if increment > 0:

            symbol = stocks["symbol"]

            name = stocks["name"]

            # XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            storage = db.execute(
                "SELECT shares FROM stocks WHERE id = ? AND symbol = ?", session["user_id"], stocks["symbol"])
            for item in storage:
                current_shares = int(item["shares"])
            new_shares = current_shares + shares

            # XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            storage = db.execute(
                "SELECT price_total FROM stocks WHERE id = ? AND symbol = ?", session["user_id"], stocks["symbol"])
            for item in storage:
                current_price_total = float(item["price_total"])
            new_price_total = current_price_total + (price * shares)

            db.execute("UPDATE stocks SET shares = ?, price = ?, price_total = ? WHERE id = ? AND symbol = ?",
                       new_shares, stocks["price"], new_price_total, session["user_id"], stocks["symbol"])
        else:

            db.execute("INSERT INTO stocks (id, symbol, name, shares, price, price_total) VALUES(?, ?, ?, ?, ?, ?)",
                       session["user_id"], stocks["symbol"], stocks["name"], shares, stocks["price"], float(stocks["price"]) * shares)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # Check if given stock symbol exists in API database
        if not lookup(request.form.get("symbol")):
            return apology("Nothing has been found")

        # Create a variable to receive the variable that the lookup function returns
        stocks = lookup(request.form.get("symbol"))

        return render_template("quoted.html", stocks=stocks)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password and confirmation were submitted
        elif not request.form.get("password") and not request.form.get("confirmation"):
            return apology("must provide password and confirmation", 400)

        # Pass user input to variables
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure given username doesnt already exist at database
        rows = db.execute("SELECT * FROM users")
        for row in rows:
            if username == row["username"]:
                return apology("Username already exists", 400)

        # Ensure given password and confirmation are equal
        if confirmation != password:
            return apology("Password and confirmation must be equal", 400)

        # Define a hash value using the given password
        hash = generate_password_hash(
            password, method='pbkdf2:sha256', salt_length=8)

        # Insert into database
        db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        # Redirect user to login form
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":

        # Check if given stock symbol exists in API database
        if not lookup(request.form.get("symbol")):
            return apology("Nothing has been found")

        # Transform "shares" in a int
        storage = db.execute("SELECT shares FROM stocks WHERE id = ? AND symbol = ?",
                             session["user_id"], request.form.get("symbol"))
        for item in storage:
            current_shares = item["shares"]

        # Check if given number of shares is a positive integer
        if int(request.form.get("shares")) < 0 or int(request.form.get("shares")) > current_shares:
            return apology("Invalid number of shares")

        # Receive stocks from database
        stocks = lookup(request.form.get("symbol"))

        # Transform stocks["price"] string in a float
        current_price = float(stocks["price"])

        # Variables and calculations for new money amount
        user_given_shares = int(request.form.get("shares"))

        storage = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])
        for item in storage:
            current_cash = float(item["cash"])

        new_cash = current_cash + (user_given_shares * current_price)

        # Update the amount of cash user has
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   new_cash, session["user_id"])

        # Update new stock values

        symbol = request.form.get("symbol")
        price = float(stocks["price"])

        # Check if all shares have been sold, if so, remove the hole thing from database
        if int(request.form.get("shares")) == current_shares:
            db.execute("DELETE FROM stocks WHERE id = ? AND symbol = ?",
                       session["user_id"], symbol)
        else:

            # Store current stock information onto variables
            # XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            storage = db.execute("SELECT shares FROM stocks WHERE id = ? AND symbol = ?", session["user_id"], stocks["symbol"])
            for item in storage:
                current_shares = int(item["shares"])
            new_shares = current_shares - user_given_shares

            # XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            storage = db.execute("SELECT price_total FROM stocks WHERE id = ? AND symbol = ?", session["user_id"], stocks["symbol"])
            for item in storage:
                current_price_total = float(item["price_total"])
            new_price_total = current_price_total - (price * user_given_shares)

            # Update on database
            db.execute("UPDATE stocks SET shares = ?, price = ?, price_total = ? WHERE id = ? AND symbol = ?",
            new_shares, stocks["price"], new_price_total, session["user_id"], stocks["symbol"])

        return redirect("/")
    else:

        # Select all stocks present at the database where id is equal to the current loged in user
        stocks = db.execute(
            "SELECT * FROM stocks WHERE id = ?", session["user_id"])

        return render_template("sell.html", stocks=stocks)
