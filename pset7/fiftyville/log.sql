-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Looking up crimes on July 28th 2021 on Humphrey Street
--  Maybe the crime was reported a day late?
SELECT description FROM crime_scene_reports WHERE year=2021 AND month = 7 AND day=28 AND street LIKE "Humphrey%" ;
-- Looking up info in interview transcripts that include the word bakery
SELECT transcript FROM interviews WHERE transcript LIKE "%bakery%" AND year=2021;
--Looking up the earliest flight out of fiftyville
SELECT city
FROM airports
WHERE id =
(SELECT destination_airport_id
FROM flights
WHERE origin_airport_id=(SELECT id FROM airports WHERE city LIKE "%FiftyVille%")
AND year=2021 AND month = 7 AND day = 29
ORDER BY hour,minute
LIMIT 1);
-- Looking up passengers that withdrew money from the Legget street ATM on the earliest flight out of FiftyVille
SELECT passport_number FROM passengers WHERE flight_id =
(SELECT id
FROM flights
WHERE origin_airport_id=(SELECT id FROM airports WHERE city LIKE "%FiftyVille%")
AND year=2021 AND month = 7 AND day = 29
ORDER BY hour,minute
LIMIT 1) AND passport_number IN
(SELECT passport_number
FROM people
JOIN bank_accounts
ON id=person_id
WHERE bank_accounts.account_number IN
(SELECT account_number
FROM atm_transactions
WHERE year=2021 AND month = 7 AND day = 28 AND atm_location LIKE "%Leggett%"));
-- Trace the right phone call and cross-reference the phone number with phone numbers of the passengers in the query above
SELECT name,id,phone_number FROM people WHERE phone_number IN
(SELECT caller
FROM phone_calls
WHERE year =2021
AND month=7
AND day=28
AND duration BETWEEN 45 AND 70)
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id =
(SELECT id
FROM flights
WHERE origin_airport_id=(SELECT id FROM airports WHERE city LIKE "%FiftyVille%")
AND year=2021 AND month = 7 AND day = 29
ORDER BY hour,minute
LIMIT 1) AND passport_number IN
(SELECT passport_number
FROM people
JOIN bank_accounts
ON id=person_id
WHERE bank_accounts.account_number IN
(SELECT account_number
FROM atm_transactions
WHERE year=2021 AND month = 7 AND day = 28 AND atm_location LIKE "%Leggett%")));
-- Hard Coded Suspicious Numbers Cause SQL statements to f-ing long. Anyway, potential accomplices
SELECT *
FROM phone_calls
WHERE year=2021
AND month=7
AND day=28
AND caller = '(826) 555-1652' OR caller = '(367) 555-5533'
AND duration BETWEEN 45 AND 70;
-- Suspects License Plates
SELECT license_plate FROM people WHERE id = 395717 OR id = 686048
--
SELECT * FROM bakery_security_logs WHERE license_plate IN
(
    SELECT license_plate FROM people WHERE id = 395717 OR id = 686048
);
--
SELECT * from people WHERE license_plate='94KL13X';
--
SELECT * from people WHERE phone_number='(375) 555-8161';
