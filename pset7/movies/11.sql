-- list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.

SELECT title
  FROM movies, people, stars, ratings
 WHERE movies.id = stars.movie_id
   AND people.id = stars.person_id
   AND movies.id = ratings.movie_id
   AND name = 'Chadwick Boseman'
 ORDER BY rating DESC
 LIMIT 5;