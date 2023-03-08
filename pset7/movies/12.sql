-- list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.

-- 121164
-- 367594
-- 408236
-- 1014759
-- 1077368
-- 2567026

SELECT title
  FROM stars
       JOIN people
       ON stars.person_id = people.id
       JOIN movies
       ON movies.id = stars.movie_id
 WHERE name = 'Johnny Depp'
   AND movie_id IN
       (SELECT movie_id
          FROM people
               JOIN stars
               ON people.id = stars.person_id
         WHERE name = 'Helena Bonham Carter');