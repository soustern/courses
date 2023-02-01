SELECT name FROM people
WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT movies.id FROM movies INNER JOIN stars ON movies.id = stars.movie_id INNER JOIN ratings ON stars.movie_id = ratings.movie_id INNER JOIN people ON stars.person_id = people.id WHERE name = "Kevin Bacon" AND birth = "1958"))
AND name != "Kevin Bacon";