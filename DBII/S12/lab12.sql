-- Creación de tabla persona con particiones
CREATE TABLE persona (
    id 		    int not null,
    fecha_nac 	date not null,
    cod_pais 	character(2) not null,
    nombre 	    varchar(30)
) PARTITION BY LIST (cod_pais);


-- Particion para personas viviendo en Peru
CREATE TABLE persona_pe PARTITION OF persona FOR VALUES IN ('PE');

-- Particion para personas viviendo en Latinoamerica
CREATE TABLE persona_lat PARTITION OF persona FOR VALUES IN ('EC', 'BO', 'CH', 'AR', 'CO','BR', 'VE');

-- Particion para el resto de personas del mundo
CREATE TABLE persona_resto PARTITION OF persona  DEFAULT;

-- Se puede crear una partición con algún cod_pais ya existente en otras particiones?
CREATE TABLE persona_2 PARTITION OF persona FOR VALUES IN ('AR', 'PE');
-- No se puede, ya que los valores traslaparían con otras particiones


-- Inserción de datos en la partición persona_pe
INSERT INTO persona
VALUES(1, '2020-12-01', 'PE', 'Juan');

-- Inserción de datos en la partición persona_lat
INSERT INTO persona
VALUES(2, '2020-12-01', 'EC', 'Pedro');

-- Inserción de datos en la partición persona_resto
INSERT INTO persona
VALUES(3, '2020-12-01', 'US', 'Maria');


-- Ver desde qué particiones se extrae la información
explain analyze
SELECT * FROM persona;

EXPLAIN ANALYZE
SELECT * FROM persona
WHERE cod_pais = 'PE'
AND fecha_nac > '2020-01-01';