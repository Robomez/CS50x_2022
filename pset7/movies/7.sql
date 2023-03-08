-- list all movies released in 2010 and their ratings,
    -- in descending order by rating
    -- For movies with the same rating, order them alphabetically by title.

select title, rating
  FROM movies, ratings
 WHERE movies.id = ratings.movie_id
   AND year = 2010
 ORDER BY rating DESC, title;