SELECT title FROM movies INNER JOIN stars ON movies.id = stars.movie_id INNER JOIN ratings ON stars.movie_id = ratings.movie_id INNER JOIN people ON stars.person_id = people.id WHERE name = "Chadwick Boseman" AND title != "Message from the King" ORDER BY rating DESC;