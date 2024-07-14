SET search_path TO lab14;

/* P0. Crear tabla particionada */

-- Crear la tabla alumnos que será particionada
CREATE TABLE alumnos (
    dni varchar(8),
    nombre varchar(30),
    ciudad varchar(30),
    grupo varchar(1),
    promedio float,
    edad int,
    sexo varchar(1)
) PARTITION BY LIST (ciudad);

-- Crear una tabla 'fantasma' que se utilizará para ejecutar el trigger principal
CREATE TABLE tempalumnos (
    dni varchar(8),
    nombre varchar(30),
    ciudad varchar(30),
    grupo varchar(1),
    promedio float,
    edad int,
    sexo varchar(1)
);

SET enable_partition_pruning = on;

-- Crear la partición para los alumnos de Lima
CREATE TABLE alumnos_lima
PARTITION OF alumnos
FOR VALUES IN ('Lima');

-- Crear la partición para los alumnos de Callao
CREATE TABLE alumnos_callao
PARTITION OF alumnos
FOR VALUES IN ('Callao');


/* P1. Creación dinámica de nuevos fragmentos */

-- Creando el procedimiento almacenado para la creación de nuevas particiones e inserción de datos
CREATE OR REPLACE FUNCTION create_partition_and_insert() RETURNS trigger AS
    $BODY$
        DECLARE
            partition_city TEXT;
            partition TEXT;
            parent_table TEXT := 'alumnos';
        BEGIN
            partition_city := NEW.ciudad;
            partition := parent_table || '_' || lower(partition_city);

            IF NOT EXISTS(
                SELECT ciudad FROM alumnos WHERE ciudad = quote_literal(NEW.ciudad)
            ) THEN
                RAISE NOTICE 'A partition % has been created', partition;
                EXECUTE 'CREATE TABLE ' || partition || ' PARTITION OF ' || parent_table || ' FOR VALUES IN (' || quote_literal(partition_city) || ');';
            END IF;

            EXECUTE 'INSERT INTO ' || parent_table || ' VALUES (' || quote_literal(NEW.dni) || ', ' ||
                                                   quote_literal(NEW.nombre) || ', ' ||
                                                   quote_literal(NEW.ciudad) || ', ' ||
                                                   quote_literal(NEW.grupo) || ', ' ||
                                                   NEW.promedio || ', ' ||
                                                   NEW.edad || ', ' ||
                                                   quote_literal(NEW.sexo) || ');';
            RETURN NULL;
        END
    $BODY$
LANGUAGE plpgsql VOLATILE
COST 100;


-- Creando el trigger que ejecutará el store procedure
CREATE OR REPLACE TRIGGER partition_insert_trigger
BEFORE INSERT ON tempalumnos
FOR EACH ROW EXECUTE PROCEDURE create_partition_and_insert();


-- Insertar datos en la tabla alumnos
INSERT INTO tempalumnos VALUES ('12345666', 'Juan', 'Lima', 'A', 15.5, 18, 'M');
INSERT INTO tempalumnos VALUES ('12345667', 'Pedro', 'Callao', 'B', 14.5, 19, 'M');
INSERT INTO tempalumnos VALUES ('12345667', 'Pedro', 'Arequipa', 'B', 14.5, 19, 'M');
INSERT INTO tempalumnos VALUES ('12345667', 'Pedro', 'Ica', 'B', 14.5, 19, 'M');
INSERT INTO tempalumnos VALUES ('12345667', 'Pedro', 'Huanuco', 'B', 14.5, 19, 'M');
INSERT INTO tempalumnos VALUES ('12345667', 'Pedro', 'Arequipa', 'B', 14.5, 19, 'M');

-- Realizando una consulta para verificar que los datos se han insertado en la partición correcta
EXPLAIN ANALYZE
SELECT * FROM alumnos WHERE ciudad = 'Lima';

/*
Indague sobre el uso de triggers y primary key en tablas particionadas ¿Será posible su uso?

Uso de Triggers y Primary Key en Tablas Particionadas en PostgreSQL
En PostgreSQL, la partición de tablas es una técnica para gestionar grandes conjuntos de datos dividiendo una tabla en tablas más pequeñas llamadas "particiones". Esto puede mejorar el rendimiento y la gestión de datos. Sin embargo, hay algunas consideraciones importantes cuando se utilizan claves primarias y triggers en tablas particionadas.

Triggers en Tablas Particionadas
¿Es posible el uso de triggers en tablas particionadas?
Sí, es posible utilizar triggers en tablas particionadas en PostgreSQL. Sin embargo, hay algunos detalles a tener en cuenta:

Triggers en la Tabla Padre: Los triggers definidos en la tabla padre se aplican a todas las particiones. Esto es útil si deseas implementar lógica común para todas las particiones.

Triggers en Particiones Individuales: También puedes definir triggers en particiones individuales si necesitas lógica específica para una partición en particular.

Consideraciones de Rendimiento: Definir triggers en tablas particionadas puede impactar el rendimiento, especialmente si los triggers realizan operaciones complejas o si se activan con alta frecuencia.

Clave Primaria en Tablas Particionadas
¿Es posible usar una clave primaria en tablas particionadas?
Sí, puedes definir una clave primaria en una tabla particionada en PostgreSQL, pero hay ciertas limitaciones y comportamientos que debes considerar.

Clave Primaria en la Tabla Padre: Puedes definir una clave primaria en la tabla padre. Sin embargo, PostgreSQL no soporta la herencia de restricciones de claves primarias a las particiones automáticamente. Esto significa que la clave primaria no se impone automáticamente en cada partición.

Claves Únicas y Restricciones: Puedes definir restricciones únicas en la tabla padre, pero estas no se propagan automáticamente a las particiones. Debes definir restricciones únicas en cada partición individualmente.

Implementación Manual de Claves Primarias: Si necesitas que cada partición tenga una clave primaria, debes crear manualmente la clave primaria en cada partición. Esto puede implicar escribir scripts para automatizar la creación de particiones con las restricciones necesarias.

*/