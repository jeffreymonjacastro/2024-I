/* P0. Crear tabla particionada */

-- Crear la tabla alumnos
CREATE TABLE alumnos (
    dni varchar(8),
    nombre varchar(30),
    ciudad varchar(30),
    grupo varchar(1),
    promedio float,
    edad int,
    sexo varchar(1)
) PARTITION BY LIST (ciudad);

-- Crear la partición para los alumnos de Lima
CREATE TABLE alumnos_lima
PARTITION OF alumnos
FOR VALUES IN ('Lima');

-- Crear la partición para los alumnos de Callao
CREATE TABLE alumnos_callao
PARTITION OF alumnos
FOR VALUES IN ('Callao');


/* P1. Creación dinámica de nuevos fragmentos */

-- Creando el procedimiento almacenado para la creación de nuevas particiones
CREATE OR REPLACE FUNCTION create_partition_and_insert() RETURNS trigger AS
    $BODY$
        DECLARE
            partition_city TEXT;
            partition_name TEXT;
        BEGIN
            partition_city := NEW.ciudad;
            partition_name := TG_RELNAME || '_' || partition_city;

            IF NOT EXISTS(SELECT relname FROM pg_class WHERE relname=partition) THEN
                RAISE NOTICE 'A partition has been created %',partition;
                EXECUTE 'CREATE TABLE ' || partition || ' (check (date = ''' || NEW.date || ''')) INHERITS (' || TG_RELNAME || ');';
            END IF;
            EXECUTE 'INSERT INTO ' || partition || ' SELECT(' || TG_RELNAME || ' ' || quote_literal(NEW) || ').* RETURNING patent_id;';
            RETURN NULL;
        END;
    $BODY$
LANGUAGE plpgsql VOLATILE
COST 100;

-- Creando el trigger que ejecutará el store procedure
CREATE TRIGGER partition_insert_trigger
BEFORE INSERT ON alumnos
FOR EACH ROW EXECUTE PROCEDURE create_partition_and_insert();