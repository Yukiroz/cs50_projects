SELECT name FROM people
JOIN stars ON people.id = person_id
JOIN movies ON movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth;