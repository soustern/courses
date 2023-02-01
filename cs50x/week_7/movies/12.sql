SELECT title FROM movies
    WHERE id IN
    (SELECT movies.id FROM movies INNER JOIN stars ON movies.id = stars.movie_id INNER JOIN ratings ON stars.movie_id = ratings.movie_id INNER JOIN people ON stars.person_id = people.id WHERE name = "Johnny Depp")
    AND id IN
    (SELECT movies.id FROM movies INNER JOIN stars ON movies.id = stars.movie_id INNER JOIN ratings ON stars.movie_id = ratings.movie_id INNER JOIN people ON stars.person_id = people.id WHERE name = "Helena Bonham Carter");

