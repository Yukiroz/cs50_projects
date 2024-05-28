-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- The 3 interviews mention the bakery, so I'm looking for bakery mentions in the interviews table
SELECT id
FROM interviews
WHERE transcript LIKE '%bakery%';

SELECT transcript
FROM interviews
WHERE id = 161;

SELECT transcript
FROM interviews
WHERE id = 162;

SELECT transcript
FROM interviews
WHERE id = 163;

SELECT transcript
FROM interviews
WHERE id = 192;
-- Important clues:
-- The thief called someone right after the abducktion
-- The thief helper purchased tickets for a flight the next day after the theft
-- The thief used the atm in legget street.
-- The thief drove away from the bakery at the timeframe of 10:15 - 10:25

-- ATM check
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street';
-- Confirm that all transactions are on the same year as the ducknapping
SELECT year FROM atm_transactions
WHERE atm_transactions.month = 7 AND atm_transactions.day = 28;

-- SECURITY FOOTAGE check
SELECT name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE month = 7
AND day = 28
AND activity = 'exit'
AND hour = '10' AND
minute < 26
AND minute > 15;

-- Flights check
-- earliest flight
SELECT hour FROM flights
WHERE day = 29 and month = 7;

-- where the flight is headed
SELECT city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
WHERE flights.day = 29 AND flights.month = 7 AND flights.hour = 8;

-- People on the earliest flight
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id =  flights.origin_airport_id
WHERE airports.city = 'Fiftyville' AND flights.month = 7 AND flights.day = 29 AND flights.year = 2021 AND flights.hour = 8;

-- Phonecall: The only 2 people that are on the flight, used the atm and exited the bakery, at the correct timeframe are LUCA and BRUCE
SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60;

-- Since Bruce is the only person that fits the criteria we now look for the receiver
SELECT people.name FROM people
WHERE people.phone_number =
(SELECT receiver FROM phone_calls
JOIN people ON phone_number = phone_calls.caller
WHERE people.name = 'Bruce'
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60);
-- Bruce did it and Robin is the Accomplice