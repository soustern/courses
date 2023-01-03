-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Conducted the first search analising the content of description at
-- the date and place in wich the crime ocurred:
SELECT description
    FROM crime_scene_reports
    WHERE month = 7
    AND day = 28
    AND year = 2021
    AND street = "Humphrey Street";

-- Analise the "activity" session at bakery_security_logs at the day, year
-- , month, hour and minute in wich the theft ocurred
SELECT hour, minute, activity, license_plate
    FROM bakery_security_logs
    WHERE month = 7
    AND day = 28
    AND year = 2021
    AND hour BETWEEN 9 AND 11
    AND minute BETWEEN 14 AND 25;

-- Analise the transcpit of interviews made during that time
SELECT name, transcript
    FROM interviews
    WHERE month = 7
    AND day = 28
    AND year = 2021;

-- Analise the airport data on the following day of origin
SELECT full_name, city
    FROM airports
    WHERE id IN (SELECT origin_airport_id
                    FROM flights
                    WHERE year = 2021
                    AND month = 7
                    AND day = 29)

-- Analise the airport data on the following day of destination
SELECT full_name, city
    FROM airports
    WHERE id IN (SELECT destination_airport_id
                    FROM flights
                    WHERE year = 2021
                    AND month = 7
                    AND day = 29);

-- Analise hour and minute of flights
SELECT hour, minute
    FROM flights
    WHERE year = 2021
    AND month = 7
    AND day = 29
    ORDER BY hour;

-- Analise flights at that hour
SELECT full_name, city
    FROM airports
    WHERE id IN (SELECT destination_airport_id
                    FROM flights
                    WHERE year = 2021
                    AND month = 7
                    AND day = 29
                    AND hour = 8
                    AND minute = 20);

-- Find passport from people at that flight
SELECT passport_number, seat
    FROM passengers
    WHERE flight_id IN (SELECT id
                            FROM flights
                            WHERE destination_airport_id IN (SELECT airports.id
                                FROM airports
                                WHERE city = "New York City"
                                AND full_name = "LaGuardia Airport"));

-- Find person with both license plate and passport
SELECT passport_number
    FROM people
    WHERE name = "Robin";

SELECT * FROM people WHERE name = "Robin";

-- Check atm Leggett Street
SELECT account_number, transaction_type
    FROM atm_transactions
    WHERE atm_location = "Leggett Street"
    AND year = 2021
    AND month = 7
    AND day = 28;

-- Select people with id found in bank accounts with account number
SELECT name, passport_number
    FROM people
    WHERE id IN (SELECT person_id
                     FROM bank_accounts
                    WHERE account_number = "28500762");

SELECT receiver, duration  FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = "Bruce") AND day = 28 AND month =  AND year = 2021;

SELECT name FROM people WHERE phone_number = "(375) 555-8161";

