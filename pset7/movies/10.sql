-- list the names of all people (people)
    --who have directed a movie (directors)
    --that received a rating of at least 9.0. (ratings?)

SELECT DISTINCT(name)
  FROM people, directors, ratings
 WHERE people.id = directors.person_id
   AND directors.movie_id = ratings.movie_id
   AND rating >= 9;