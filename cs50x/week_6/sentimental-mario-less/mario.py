from cs50 import get_int


def main():
    """ Program that makes rows of # with the quantity of # being defined by user input """

    # Variable tha wiil be used to insert the spaves
    increment = 1

    # Get user input
    answer = get_int("Height: ")

    # Ask height again if user input is not beetwen 1 and 8
    while answer < 1 or answer > 8:
        print("Height must be beetwen 1 and 8")
        answer = get_int("Height: ")

    # Summon the function passing the two variables, one defined, one collected
    squares_and_spaces(answer, increment)


def squares_and_spaces(height, increment):
    """ Function that will format the rows """

    # Check recursion stoping condition
    if height == 0:
        return

    # Recurssion: Height goes down one
    # Recurssion: Increment goes up one
    squares_and_spaces(height - 1, increment + 1)

    # Print space the amount of "increment - 1" at that recurssion position
    for i in range(increment - 1):
        print(" ", end="")

    # Print # the amount of "height" at that recurssion position
    for i in range(height):
        print("#", end="")

    # print(" ", end="")

    # for i in range(height):
        # print("#", end="")

    # print a line break at the end of each recurssion position
    print("")


# Summon main
main()
