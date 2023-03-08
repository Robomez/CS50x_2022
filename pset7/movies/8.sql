-- list the names of all people who starred in Toy Story

SELECT name
  FROM people, movies, stars
 WHERE movies.id = stars.movie_id
   AND people.id = stars.person_id
   AND title = 'Toy Story';