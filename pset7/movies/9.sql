--  list the names of all people who starred in a movie released in 2004,
    -- ordered by birth year

SELECT DISTINCT(name)
  FROM people, movies, stars
 WHERE people.id = stars.person_id
   AND movies.id = stars.movie_id
   AND movies.year = 2004
 ORDER BY birth;