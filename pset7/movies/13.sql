-- list the names of all people who starred in a movie in which Kevin Bacon also starred
-- KB 102

-- Get people from those movies
SELECT name
  FROM stars, people
 WHERE stars.person_id = people.id
   AND movie_id IN
       (SELECT movie_id
          FROM stars, people
         WHERE stars.person_id = people.id
           AND name = 'Kevin Bacon'
        )
   AND NOT name = 'Kevin Bacon';