-- Keep a log of any SQL queries you execute as you solve the mystery.

-- See all the tables in DB
.tables

-- See all tables' schemas
.schema

-- Observe crime description
SELECT description FROM crime_scene_reports WHERE street LIKE "Humphrey%" AND month = 7 AND day = 28;

-- Look at bakery report at that time
SELECT hour, minute, activity, license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour BETWEEN 9 AND 10;

-- Look at witness report transcripts
SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- Witness ruth: Search for a licence plate that left between 10.15 and 10.25
SELECT license_plate
  FROM bakery_security_logs
 WHERE month = 7 AND day = 28
   AND hour = 10
   AND minute BETWEEN 10 AND 25
   AND activity = 'exit';

-- Witness Eugene: Search person_id from bank accounts, that made an ATM transaction earlier than 10.15 on Leggett Street
SELECT person_id FROM bank_accounts AS ba
  JOIN atm_transactions AS atmt ON ba.account_number = atmt.account_number
 WHERE ba.account_number IN
       (SELECT account_number
          FROM atm_transactions
         WHERE month = 7 AND day = 28
           AND atm_location = 'Leggett Street'
           AND transaction_type LIKE '%withdraw%')
;

-- Witness Raymond: Look for callers that match witness' story.
SELECT caller, receiver FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60;


-- Look whom we get as suspects from witness reports. 514353 Diana and 686048 Bruce
SELECT DISTINCT p.id, name FROM people AS p
  JOIN phone_calls AS pc ON p.phone_number = pc.caller
  JOIN bakery_security_logs AS bsl ON p.license_plate = bsl.license_plate
  JOIN bank_accounts AS ba ON ba.person_id = p.id
  JOIN atm_transactions AS atmt ON ba.account_number = atmt.account_number
 WHERE p.phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE month = 7 AND day = 28
           AND duration <= 60
       )
   AND p.license_plate IN
       (SELECT license_plate
  FROM bakery_security_logs
 WHERE month = 7 AND day = 28
   AND hour = 10
   AND minute BETWEEN 10 AND 25
   AND activity = 'exit'
       )
   AND ba.account_number IN
       (SELECT account_number
          FROM atm_transactions
         WHERE month = 7 AND day = 28
           AND atm_location = 'Leggett Street'
           AND transaction_type LIKE '%withdraw%'
       )
;

-- Which one of those two suspects flies out by first flight tomorrow?
SELECT p.id, p.name FROM people AS p
  JOIN passengers AS psg ON p.passport_number = psg.passport_number
  JOIN flights AS f ON f.id = psg.flight_id
  JOIN airports AS a ON f.origin_airport_id = a.id
 WHERE p.passport_number IN
       (SELECT passport_number FROM passengers WHERE f.id =
               (SELECT f.id FROM flights AS f
                  JOIN airports AS a ON f.origin_airport_id = a.id
                 WHERE origin_airport_id =
                       (SELECT id FROM airports WHERE city = "Fiftyville")
                   AND month = 7 AND day = 29
                 ORDER BY f.hour, f.minute
                 LIMIT 1
                 )
       )
;

-- Combine 2 selects and get Bruce
SELECT t1.name FROM
(SELECT DISTINCT name FROM people AS p
  JOIN phone_calls AS pc ON p.phone_number = pc.caller
  JOIN bakery_security_logs AS bsl ON p.license_plate = bsl.license_plate
  JOIN bank_accounts AS ba ON ba.person_id = p.id
  JOIN atm_transactions AS atmt ON ba.account_number = atmt.account_number
 WHERE p.phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE month = 7 AND day = 28
           AND duration <= 60
       )
   AND p.license_plate IN
       (SELECT license_plate
  FROM bakery_security_logs
 WHERE month = 7 AND day = 28
   AND hour = 10
   AND minute BETWEEN 10 AND 25
   AND activity = 'exit'
       )
   AND ba.account_number IN
       (SELECT account_number
          FROM atm_transactions
         WHERE month = 7 AND day = 28
           AND atm_location = 'Leggett Street'
           AND transaction_type LIKE '%withdraw%'
       )
)      t1

INNER JOIN

(SELECT p.name FROM people AS p
  JOIN passengers AS psg ON p.passport_number = psg.passport_number
  JOIN flights AS f ON f.id = psg.flight_id
  JOIN airports AS a ON f.origin_airport_id = a.id
 WHERE p.passport_number IN
       (SELECT passport_number FROM passengers WHERE f.id =
               (SELECT f.id FROM flights AS f
                  JOIN airports AS a ON f.origin_airport_id = a.id
                 WHERE origin_airport_id =
                       (SELECT id FROM airports WHERE city = "Fiftyville")
                   AND month = 7 AND day = 29
                 ORDER BY f.hour, f.minute
                 LIMIT 1
                 )
       )
)      t2
    ON t1.name = t2.name
;

-- no need to combine so much in one query, actually. Let's find the destination airport. New York City
SELECT city FROM airports AS a
  JOIN flights AS f ON f.destination_airport_id = a.id
 WHERE f.id = 36;

--  Whom did Bruce call at 10:15? Robin
SELECT p.name FROM people as p
  JOIN phone_calls AS pc ON p.phone_number = pc.receiver
 WHERE caller =
       (SELECT phone_number FROM people WHERE id = 686048)
   AND month = 7 AND day = 28
   AND duration <= 60
;