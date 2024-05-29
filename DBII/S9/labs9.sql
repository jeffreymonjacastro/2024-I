-- Crear la tabla article
CREATE TABLE article(
                        body text,
                        body_indexed text
);

-- Extensión pg_trgm: tipo de índice invertido para búsquedas de texto
CREATE EXTENSION pg_trgm;

-- Insertar datos en la tabla article
INSERT INTO article
SELECT md5(random()::text)
FROM (
         SELECT *
         FROM generate_series(1, 1000000)
                  AS id
     )
         AS T;

-- Actualizar la columna body_indexed con la columna body
UPDATE article
SET body_indexed = body;

-- Se crea un índice optimizado para búsquedas de texto en el campo body_indexed
CREATE INDEX artice_idx
    ON article
    USING GIN(body_indexed gin_trgm_ops);


EXPLAIN ANALYSE

SELECT COUNT(*)
FROM article
WHERE body
    ILIKE '%abc%';

-- N = 10^6 => 1227.334 ms


EXPLAIN ANALYSE

SELECT COUNT(*)
FROM article
WHERE body_indexed
    ILIKE '%abcd%';

-- N = 10^6 => 9.787 ms

DELETE FROM article;