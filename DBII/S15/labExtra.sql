SET search_path TO lab15;

-- Link al repositorio con todos los archivos para el laboratorio:
-- https://github.com/jeffreymonjacastro/2024-I/tree/main/DBII/S15

-- Crear la tabla venta particionada
CREATE TABLE venta (
    IdVenta SERIAL,
    DNI_Cliente INT,
    FechaVenta DATE,
    CodLocal VARCHAR(5),
    ImporteTotal FLOAT,
    IdEmpleado VARCHAR(6)
) PARTITION BY RANGE (FechaVenta);

-- Crear particiones para la tabla venta
CREATE TABLE venta_2000_2008 PARTITION OF venta
    FOR VALUES FROM ('2000-01-01') TO ('2009-01-01');

CREATE TABLE venta_2009_2016 PARTITION OF venta
    FOR VALUES FROM ('2009-01-01') TO ('2017-01-01');

CREATE TABLE venta_2017_2024 PARTITION OF venta
    FOR VALUES FROM ('2017-01-01') TO ('2025-01-01');

-- Crear tabla reclamo particionada por lista en CodLocal
CREATE TABLE reclamo (
    IdReclamo SERIAL,
    DNI_Cliente INT,
    FechaReclamo DATE,
    CodLocal VARCHAR(5),
    Descripcion VARCHAR(100),
    Estado VARCHAR(10)
) PARTITION BY LIST (CodLocal);

-- Crear particiones para la tabla reclamo
CREATE TABLE reclamo_loc1 PARTITION OF reclamo
    FOR VALUES IN ('LOC01', 'LOC02', 'LOC03', 'LOC04');

CREATE TABLE reclamo_loc2 PARTITION OF reclamo
    FOR VALUES IN ('LOC05', 'LOC06', 'LOC07', 'LOC08');

CREATE TABLE reclamo_loc3 PARTITION OF reclamo
    FOR VALUES IN ('LOC09', 'LOC10', 'LOC11', 'LOC12');

-- Verificando la distribución de los datos para cada una de las tablas
SELECT 'venta_2000_2008' AS tabla, COUNT(*) AS total_filas
FROM venta_2000_2008
UNION ALL
SELECT 'venta_2009_2016' AS tabla, COUNT(*) AS total_filas
FROM venta_2009_2016
UNION ALL
SELECT 'venta_2017_2024' AS tabla, COUNT(*) AS total_filas
FROM venta_2017_2024;

SELECT 'reclamo_loc1' AS tabla, COUNT(*) AS total_filas
FROM reclamo_loc1
UNION ALL
SELECT 'reclamo_loc2' AS tabla, COUNT(*) AS total_filas
FROM reclamo_loc2
UNION ALL
SELECT 'reclamo_loc3' AS tabla, COUNT(*) AS total_filas
FROM reclamo_loc3;

-- Consultas a las tablas
SELECT *
FROM venta
ORDER BY ImporteTotal DESC;

SELECT DISTINCT DNI_Cliente
FROM venta;

SELECT CodLocal, AVG(ImporteTotal) AS promedio_importe
FROM venta
GROUP BY CodLocal
ORDER BY CodLocal;

SELECT R.*
FROM reclamo R
JOIN venta V
ON R.DNI_Cliente = V.DNI_Cliente;

-- P1. Algoritmos distribuídos para consultas
/* Consulta 1
    El atributo ImporteTotal se generó en el rango de 1 a 1000,
    por lo que se tomó el vector de partición [333,666] en el atributo ImporteTotal
*/

-- Creando tablas temporales
CREATE OR REPLACE FUNCTION consulta1()
RETURNS TABLE (
    IdVenta INT,
    DNI_Cliente INT,
    FechaVenta DATE,
    CodLocal VARCHAR(5),
    ImporteTotal FLOAT,
    IdEmpleado VARCHAR(6)
) AS $$
BEGIN
    CREATE TEMPORARY TABLE temp_venta1 AS
        SELECT V.*
        FROM venta_2000_2008 V
        WHERE V.ImporteTotal < 333
        UNION ALL
        SELECT V.*
        FROM venta_2009_2016 V
        WHERE V.ImporteTotal < 333
        UNION ALL
        SELECT V.*
        FROM venta_2017_2024 V
        WHERE V.ImporteTotal < 333;

    CREATE TEMPORARY TABLE temp_venta2 AS
        SELECT V.*
        FROM venta_2000_2008 V
        WHERE V.ImporteTotal >= 333 AND V.ImporteTotal < 666
        UNION ALL
        SELECT V.*
        FROM venta_2009_2016 V
        WHERE V.ImporteTotal >= 333 AND V.ImporteTotal < 666
        UNION ALL
        SELECT V.*
        FROM venta_2017_2024 V
        WHERE V.ImporteTotal >= 333 AND V.ImporteTotal < 666;

    CREATE TEMPORARY TABLE temp_venta3 AS
        SELECT V.*
        FROM venta_2000_2008 V
        WHERE V.ImporteTotal >= 666
        UNION ALL
        SELECT V.*
        FROM venta_2009_2016 V
        WHERE V.ImporteTotal >= 666
        UNION ALL
        SELECT V.*
        FROM venta_2017_2024 V
        WHERE V.ImporteTotal >= 666;

    CREATE TEMPORARY TABLE temp_venta4 AS
        SELECT *
        FROM temp_venta1
        ORDER BY ImporteTotal DESC;

    CREATE TEMPORARY TABLE temp_venta5 AS
        SELECT *
        FROM temp_venta2
        ORDER BY ImporteTotal DESC;

    CREATE TEMPORARY TABLE temp_venta6 AS
        SELECT *
        FROM temp_venta3
        ORDER BY ImporteTotal DESC;

    RETURN QUERY
        SELECT *
        FROM temp_venta6
        UNION ALL
        SELECT *
        FROM temp_venta5
        UNION ALL
        SELECT *
        FROM temp_venta4;

    DROP TABLE IF EXISTS temp_venta1;
    DROP TABLE IF EXISTS temp_venta2;
    DROP TABLE IF EXISTS temp_venta3;
    DROP TABLE IF EXISTS temp_venta4;
    DROP TABLE IF EXISTS temp_venta5;
    DROP TABLE IF EXISTS temp_venta6;
END;
$$ LANGUAGE plpgsql;

SELECT *
FROM consulta1();

-- Consulta1 para el plan de ejecucion
SELECT *
FROM (
    SELECT *
    FROM (
        SELECT V.*
        FROM venta_2000_2008 V
        WHERE V.ImporteTotal >= 666
        UNION ALL
        SELECT V.*
        FROM venta_2009_2016 V
        WHERE V.ImporteTotal >= 666
        UNION ALL
        SELECT V.*
        FROM venta_2017_2024 V
        WHERE V.ImporteTotal >= 666
    ) AS temp_venta3
    ORDER BY ImporteTotal DESC
) AS temp_venta6
UNION ALL
SELECT *
FROM (
    SELECT *
    FROM (
        SELECT V.*
        FROM venta_2000_2008 V
        WHERE V.ImporteTotal >= 333 AND V.ImporteTotal < 666
        UNION ALL
        SELECT V.*
        FROM venta_2009_2016 V
        WHERE V.ImporteTotal >= 333 AND V.ImporteTotal < 666
        UNION ALL
        SELECT V.*
        FROM venta_2017_2024 V
        WHERE V.ImporteTotal >= 333 AND V.ImporteTotal < 666
    ) AS temp_venta2
    ORDER BY ImporteTotal DESC
) AS temp_venta5
UNION ALL
SELECT *
FROM (
    SELECT *
    FROM (
        SELECT V.*
        FROM venta_2000_2008 V
        WHERE V.ImporteTotal < 333
        UNION ALL
        SELECT V.*
        FROM venta_2009_2016 V
        WHERE V.ImporteTotal < 333
        UNION ALL
        SELECT V.*
        FROM venta_2017_2024 V
        WHERE V.ImporteTotal < 333
    ) AS temp_venta1
    ORDER BY ImporteTotal DESC
) AS temp_venta4;

/* Consulta 2
    El atributo DNI_Cliente se generó en el rango de 70000000 a 77500000
   por lo que se tomó el vector de partición [72500000, 75000000] en el atributo DNI_Cliente
*/

-- Con tablas temporales
CREATE OR REPLACE FUNCTION consulta2()
RETURNS TABLE (
    DNI_Cliente INT
) AS $$
BEGIN
    CREATE TEMPORARY TABLE temp_venta1 AS
        SELECT V.DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente < 72500000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente < 72500000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente < 72500000;

    CREATE TEMPORARY TABLE temp_venta2 AS
        SELECT V.DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000;

    CREATE TEMPORARY TABLE temp_venta3 AS
        SELECT V.DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente >= 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente >= 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente >= 75000000;

    CREATE TEMPORARY TABLE temp_venta4 AS
        SELECT DISTINCT V.DNI_Cliente
        FROM temp_venta1 V;

    CREATE TEMPORARY TABLE temp_venta5 AS
        SELECT DISTINCT V.DNI_Cliente
        FROM temp_venta2 V;

    CREATE TEMPORARY TABLE temp_venta6 AS
        SELECT DISTINCT V.DNI_Cliente
        FROM temp_venta3 V;

    RETURN QUERY
        SELECT *
        FROM temp_venta6
        UNION ALL
        SELECT *
        FROM temp_venta5
        UNION ALL
        SELECT *
        FROM temp_venta4;

    DROP TABLE IF EXISTS temp_venta1;
    DROP TABLE IF EXISTS temp_venta2;
    DROP TABLE IF EXISTS temp_venta3;
    DROP TABLE IF EXISTS temp_venta4;
    DROP TABLE IF EXISTS temp_venta5;
    DROP TABLE IF EXISTS temp_venta6;
END;
$$ LANGUAGE plpgsql;

SELECT *
FROM consulta2();

-- Consulta2 para el plan de ejecucion
SELECT *
FROM (
    SELECT DISTINCT DNI_Cliente
    FROM (
        SELECT V.DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente >= 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente >= 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente >= 75000000
    ) AS temp_venta3

    UNION ALL

    SELECT DISTINCT DNI_Cliente
    FROM (
        SELECT V.DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000
    ) AS temp_venta2

    UNION ALL

    SELECT DISTINCT DNI_Cliente
    FROM (
        SELECT V.DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente < 72500000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente < 72500000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente < 72500000
    ) AS temp_venta1
) AS final_result;


/*
    Consulta 3
    El atributo CodLocal se generó con los valores LOC01 - LOC12,
    por lo que se dividió en 3 grupos de 4 valores cada uno: [LOC01 a LOC04], [LOC05 a LOC08], [LOC09 a LOC12]
*/

-- Con tablas temporales
CREATE OR REPLACE FUNCTION consulta3()
RETURNS TABLE (
    CodLocal VARCHAR(5),
    PromedioImporte FLOAT
) AS $$
BEGIN
    CREATE TEMPORARY TABLE temp_venta1 AS
        SELECT V.CodLocal, SUM(V.ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM venta_2000_2008 V
        WHERE V.CodLocal IN ('LOC01', 'LOC02', 'LOC03', 'LOC04')
        GROUP BY V.CodLocal
        UNION ALL
        SELECT V.CodLocal, SUM(V.ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM venta_2009_2016 V
        WHERE V.CodLocal IN ('LOC01', 'LOC02', 'LOC03', 'LOC04')
        GROUP BY V.CodLocal
        UNION ALL
        SELECT V.CodLocal, SUM(V.ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM venta_2017_2024 V
        WHERE V.CodLocal IN ('LOC01', 'LOC02', 'LOC03', 'LOC04')
        GROUP BY V.CodLocal;

    CREATE TEMPORARY TABLE temp_venta2 AS
        SELECT V.CodLocal, SUM(V.ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM venta_2000_2008 V
        WHERE V.CodLocal IN ('LOC05', 'LOC06', 'LOC07', 'LOC08')
        GROUP BY V.CodLocal
        UNION ALL
        SELECT V.CodLocal, SUM(V.ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM venta_2009_2016 V
        WHERE V.CodLocal IN ('LOC05', 'LOC06', 'LOC07', 'LOC08')
        GROUP BY V.CodLocal
        UNION ALL
        SELECT V.CodLocal, SUM(V.ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM venta_2017_2024 V
        WHERE V.CodLocal IN ('LOC05', 'LOC06', 'LOC07', 'LOC08')
        GROUP BY V.CodLocal;

    CREATE TEMPORARY TABLE temp_venta3 AS
        SELECT V.CodLocal, SUM(V.ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM venta_2000_2008 V
        WHERE V.CodLocal IN ('LOC09', 'LOC10', 'LOC11', 'LOC12')
        GROUP BY V.CodLocal
        UNION ALL
        SELECT V.CodLocal, SUM(V.ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM venta_2009_2016 V
        WHERE V.CodLocal IN ('LOC09', 'LOC10', 'LOC11', 'LOC12')
        GROUP BY V.CodLocal
        UNION ALL
        SELECT V.CodLocal, SUM(V.ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM venta_2017_2024 V
        WHERE V.CodLocal IN ('LOC09', 'LOC10', 'LOC11', 'LOC12')
        GROUP BY V.CodLocal;

    CREATE TEMPORARY TABLE temp_venta4 AS
        SELECT V.CodLocal, SUM(SumaImporte)/SUM(CantVentas)
        FROM temp_venta1 V
        GROUP BY V.CodLocal;

    CREATE TEMPORARY TABLE temp_venta5 AS
        SELECT V.CodLocal, SUM(SumaImporte)/SUM(CantVentas)
        FROM temp_venta2 V
        GROUP BY V.CodLocal;

    CREATE TEMPORARY TABLE temp_venta6 AS
        SELECT V.CodLocal, SUM(SumaImporte)/SUM(CantVentas)
        FROM temp_venta3 V
        GROUP BY V.CodLocal;

    RETURN QUERY
        SELECT *
        FROM temp_venta6
        UNION ALL
        SELECT *
        FROM temp_venta5
        UNION ALL
        SELECT *
        FROM temp_venta4;

    DROP TABLE IF EXISTS temp_venta1;
    DROP TABLE IF EXISTS temp_venta2;
    DROP TABLE IF EXISTS temp_venta3;
    DROP TABLE IF EXISTS temp_venta4;
    DROP TABLE IF EXISTS temp_venta5;
    DROP TABLE IF EXISTS temp_venta6;
END;
$$ LANGUAGE plpgsql;

SELECT *
FROM consulta3()
ORDER BY CodLocal;

-- Consulta3 para el plan de ejecucion
SELECT *
FROM (
    SELECT CodLocal, SUM(SumaImporte) / SUM(CantVentas) AS PromedioImporte
    FROM (
        SELECT CodLocal, SUM(ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM (
            SELECT V.CodLocal, V.ImporteTotal
            FROM venta_2000_2008 V
            WHERE V.CodLocal IN ('LOC01', 'LOC02', 'LOC03', 'LOC04')
            UNION ALL
            SELECT V.CodLocal, V.ImporteTotal
            FROM venta_2009_2016 V
            WHERE V.CodLocal IN ('LOC01', 'LOC02', 'LOC03', 'LOC04')
            UNION ALL
            SELECT V.CodLocal, V.ImporteTotal
            FROM venta_2017_2024 V
            WHERE V.CodLocal IN ('LOC01', 'LOC02', 'LOC03', 'LOC04')
        ) AS temp_venta1
        GROUP BY CodLocal
    ) AS aggregated_temp_venta1
    GROUP BY CodLocal

    UNION ALL

    SELECT CodLocal, SUM(SumaImporte) / SUM(CantVentas) AS PromedioImporte
    FROM (
        SELECT CodLocal, SUM(ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM (
            SELECT V.CodLocal, V.ImporteTotal
            FROM venta_2000_2008 V
            WHERE V.CodLocal IN ('LOC05', 'LOC06', 'LOC07', 'LOC08')
            UNION ALL
            SELECT V.CodLocal, V.ImporteTotal
            FROM venta_2009_2016 V
            WHERE V.CodLocal IN ('LOC05', 'LOC06', 'LOC07', 'LOC08')
            UNION ALL
            SELECT V.CodLocal, V.ImporteTotal
            FROM venta_2017_2024 V
            WHERE V.CodLocal IN ('LOC05', 'LOC06', 'LOC07', 'LOC08')
        ) AS temp_venta2
        GROUP BY CodLocal
    ) AS aggregated_temp_venta2
    GROUP BY CodLocal

    UNION ALL

    SELECT CodLocal, SUM(SumaImporte) / SUM(CantVentas) AS PromedioImporte
    FROM (
        SELECT CodLocal, SUM(ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
        FROM (
            SELECT V.CodLocal, V.ImporteTotal
            FROM venta_2000_2008 V
            WHERE V.CodLocal IN ('LOC09', 'LOC10', 'LOC11', 'LOC12')
            UNION ALL
            SELECT V.CodLocal, V.ImporteTotal
            FROM venta_2009_2016 V
            WHERE V.CodLocal IN ('LOC09', 'LOC10', 'LOC11', 'LOC12')
            UNION ALL
            SELECT V.CodLocal, V.ImporteTotal
            FROM venta_2017_2024 V
            WHERE V.CodLocal IN ('LOC09', 'LOC10', 'LOC11', 'LOC12')
        ) AS temp_venta3
        GROUP BY CodLocal
    ) AS aggregated_temp_venta3
    GROUP BY CodLocal
) AS final_result
ORDER BY CodLocal;

/*
    Consulta 4
    El atributo DNI_Cliente se generó en el rango de 70000000 a 77500000
    por lo que se tomó el vector de partición [72500000, 75000000] en el atributo DNI_Cliente
*/

-- Con tablas temmporales
CREATE OR REPLACE FUNCTION consulta4()
RETURNS TABLE (
    IdReclamo INT,
    DNI_Cliente INT,
    FechaReclamo DATE,
    CodLocal VARCHAR(5),
    Descripcion VARCHAR(100),
    Estado VARCHAR(10)
) AS $$
BEGIN
    CREATE TEMPORARY TABLE temp_venta1 AS
        SELECT V.DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente < 72500000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente < 72500000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente < 72500000;

    CREATE TEMPORARY TABLE temp_venta2 AS
        SELECT V.DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000;

    CREATE TEMPORARY TABLE temp_venta3 AS
        SELECT V.DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente >= 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente >= 75000000
        UNION ALL
        SELECT V.DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente >= 75000000;

    CREATE TEMPORARY TABLE temp_reclamo1 AS
        SELECT R.*
        FROM reclamo_loc1 R
        WHERE R.DNI_Cliente < 72500000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc2 R
        WHERE R.DNI_Cliente < 72500000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc3 R
        WHERE R.DNI_Cliente < 72500000;

    CREATE TEMPORARY TABLE temp_reclamo2 AS
        SELECT R.*
        FROM reclamo_loc1 R
        WHERE R.DNI_Cliente >= 72500000 AND R.DNI_Cliente < 75000000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc2 R
        WHERE R.DNI_Cliente >= 72500000 AND R.DNI_Cliente < 75000000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc3 R
        WHERE R.DNI_Cliente >= 72500000 AND R.DNI_Cliente < 75000000;

    CREATE TEMPORARY TABLE temp_reclamo3 AS
        SELECT R.*
        FROM reclamo_loc1 R
        WHERE R.DNI_Cliente >= 75000000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc2 R
        WHERE R.DNI_Cliente >= 75000000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc3 R
        WHERE R.DNI_Cliente >= 75000000;

    CREATE TEMPORARY TABLE temp_join1 AS
        SELECT R.*
        FROM temp_reclamo1 R
        JOIN temp_venta1 V
        ON R.DNI_Cliente = V.DNI_Cliente;

    CREATE TEMPORARY TABLE temp_join2 AS
        SELECT R.*
        FROM temp_reclamo2 R
        JOIN temp_venta2 V
        ON R.DNI_Cliente = V.DNI_Cliente;

    CREATE TEMPORARY TABLE temp_join3 AS
        SELECT R.*
        FROM temp_reclamo3 R
        JOIN temp_venta3 V
        ON R.DNI_Cliente = V.DNI_Cliente;

    RETURN QUERY
        SELECT *
        FROM temp_join1
        UNION ALL
        SELECT *
        FROM temp_join2
        UNION ALL
        SELECT *
        FROM temp_join3;

    DROP TABLE IF EXISTS temp_venta1;
    DROP TABLE IF EXISTS temp_venta2;
    DROP TABLE IF EXISTS temp_venta3;
    DROP TABLE IF EXISTS temp_reclamo1;
    DROP TABLE IF EXISTS temp_reclamo2;
    DROP TABLE IF EXISTS temp_reclamo3;
    DROP TABLE IF EXISTS temp_join1;
    DROP TABLE IF EXISTS temp_join2;
    DROP TABLE IF EXISTS temp_join3;
END;
$$ LANGUAGE plpgsql;

SELECT COUNT(*)
FROM consulta4();

-- Consulta4 para el plan de ejecucion
SELECT *
FROM (
    SELECT *
    FROM (
        SELECT R.*
        FROM reclamo_loc1 R
        WHERE R.DNI_Cliente < 72500000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc2 R
        WHERE R.DNI_Cliente < 72500000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc3 R
        WHERE R.DNI_Cliente < 72500000
    ) AS temp_reclamo1
    JOIN (
        SELECT DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente < 72500000
        UNION ALL
        SELECT DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente < 72500000
        UNION ALL
        SELECT DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente < 72500000
    ) AS temp_venta1
    ON temp_reclamo1.DNI_Cliente = temp_venta1.DNI_Cliente

    UNION ALL

    SELECT *
    FROM (
        SELECT R.*
        FROM reclamo_loc1 R
        WHERE R.DNI_Cliente >= 72500000 AND R.DNI_Cliente < 75000000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc2 R
        WHERE R.DNI_Cliente >= 72500000 AND R.DNI_Cliente < 75000000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc3 R
        WHERE R.DNI_Cliente >= 72500000 AND R.DNI_Cliente < 75000000
    ) AS temp_reclamo2
    JOIN (
        SELECT DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000
        UNION ALL
        SELECT DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000
        UNION ALL
        SELECT DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente >= 72500000 AND V.DNI_Cliente < 75000000
    ) AS temp_venta2
    ON temp_reclamo2.DNI_Cliente = temp_venta2.DNI_Cliente

    UNION ALL

    SELECT *
    FROM (
        SELECT R.*
        FROM reclamo_loc1 R
        WHERE R.DNI_Cliente >= 75000000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc2 R
        WHERE R.DNI_Cliente >= 75000000
        UNION ALL
        SELECT R.*
        FROM reclamo_loc3 R
        WHERE R.DNI_Cliente >= 75000000
    ) AS temp_reclamo3
    JOIN (
        SELECT DNI_Cliente
        FROM venta_2000_2008 V
        WHERE V.DNI_Cliente >= 75000000
        UNION ALL
        SELECT DNI_Cliente
        FROM venta_2009_2016 V
        WHERE V.DNI_Cliente >= 75000000
        UNION ALL
        SELECT DNI_Cliente
        FROM venta_2017_2024 V
        WHERE V.DNI_Cliente >= 75000000
    ) AS temp_venta3
    ON temp_reclamo3.DNI_Cliente = temp_venta3.DNI_Cliente
) AS final_result;

/* P2 - CONSULTAS EN 3 SERVIDORES */

CREATE EXTENSION dblink;

-- C1
SELECT *
FROM (
    SELECT *
    FROM (
        SELECT V.*
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT * FROM venta_2000_2008 WHERE ImporteTotal >= 666')
                 AS V(IdVenta INT, DNI_Cliente INT, FechaVenta DATE, CodLocal VARCHAR, ImporteTotal FLOAT,
                      IdEmpleado VARCHAR)
        UNION ALL
        SELECT V.*
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT * FROM venta_2009_2016 WHERE ImporteTotal >= 666')
                 AS V(IdVenta INT, DNI_Cliente INT, FechaVenta DATE, CodLocal VARCHAR, ImporteTotal FLOAT,
                      IdEmpleado VARCHAR)
        UNION ALL
        SELECT V.*
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT * FROM venta_2017_2024 WHERE ImporteTotal >= 666')
                 AS V(IdVenta INT, DNI_Cliente INT, FechaVenta DATE, CodLocal VARCHAR, ImporteTotal FLOAT,
                      IdEmpleado VARCHAR)) AS temp_venta3
    ORDER BY ImporteTotal DESC
) AS temp_venta6

UNION ALL

SELECT *
FROM (
    SELECT *
    FROM (
        SELECT V.*
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT * FROM venta_2000_2008 WHERE ImporteTotal >= 333 AND ImporteTotal < 666')
                 AS V(IdVenta INT, DNI_Cliente INT, FechaVenta DATE, CodLocal VARCHAR, ImporteTotal FLOAT,
                      IdEmpleado VARCHAR)
        UNION ALL
        SELECT V.*
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT * FROM venta_2009_2016 WHERE ImporteTotal >= 333 AND ImporteTotal < 666')
                 AS V(IdVenta INT, DNI_Cliente INT, FechaVenta DATE, CodLocal VARCHAR, ImporteTotal FLOAT,
                      IdEmpleado VARCHAR)
        UNION ALL
        SELECT V.*
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT * FROM venta_2017_2024 WHERE ImporteTotal >= 333 AND ImporteTotal < 666')
                 AS V(IdVenta INT, DNI_Cliente INT, FechaVenta DATE, CodLocal VARCHAR, ImporteTotal FLOAT,
                      IdEmpleado VARCHAR)) AS temp_venta2
      ORDER BY ImporteTotal DESC) AS temp_venta5

UNION ALL

SELECT *
FROM (
    SELECT *
    FROM (
        SELECT V.*
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT * FROM venta_2000_2008 WHERE ImporteTotal < 333')
                 AS V(IdVenta INT, DNI_Cliente INT, FechaVenta DATE, CodLocal VARCHAR, ImporteTotal FLOAT,
                      IdEmpleado VARCHAR)
        UNION ALL
        SELECT V.*
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT * FROM venta_2009_2016 WHERE ImporteTotal < 333')
                 AS V(IdVenta INT, DNI_Cliente INT, FechaVenta DATE, CodLocal VARCHAR, ImporteTotal FLOAT,
                      IdEmpleado VARCHAR)
        UNION ALL
        SELECT V.*
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT * FROM venta_2017_2024 WHERE ImporteTotal < 333')
                 AS V(IdVenta INT, DNI_Cliente INT, FechaVenta DATE, CodLocal VARCHAR, ImporteTotal FLOAT,
                      IdEmpleado VARCHAR)) AS temp_venta1
    ORDER BY ImporteTotal DESC
) AS temp_venta4
ORDER BY ImporteTotal DESC;

--C2
SELECT DISTINCT DNI_Cliente
FROM (
    SELECT *
    FROM (
        SELECT V.DNI_Cliente
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT DNI_Cliente FROM venta_2000_2008 WHERE DNI_Cliente >= 75000000')
                 AS V(DNI_Cliente INT)
        UNION ALL
        SELECT V.DNI_Cliente
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT DNI_Cliente FROM venta_2009_2016 WHERE DNI_Cliente >= 75000000')
                 AS V(DNI_Cliente INT)
        UNION ALL
        SELECT V.DNI_Cliente
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT DNI_Cliente FROM venta_2017_2024 WHERE DNI_Cliente >= 75000000')
                 AS V(DNI_Cliente INT)
    ) AS temp_venta3
) AS temp_venta6

UNION ALL

SELECT DISTINCT DNI_Cliente
FROM (
    SELECT *
    FROM (
        SELECT V.DNI_Cliente
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT DNI_Cliente FROM venta_2000_2008 WHERE DNI_Cliente >= 72500000 AND DNI_Cliente < 75000000')
                 AS V(DNI_Cliente INT)
        UNION ALL
        SELECT V.DNI_Cliente
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT DNI_Cliente FROM venta_2009_2016 WHERE DNI_Cliente >= 72500000 AND DNI_Cliente < 75000000')
                 AS V(DNI_Cliente INT)
        UNION ALL
        SELECT V.DNI_Cliente
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT DNI_Cliente FROM venta_2017_2024 WHERE DNI_Cliente >= 72500000 AND DNI_Cliente < 75000000')
                 AS V(DNI_Cliente INT)
    ) AS temp_venta2
) AS temp_venta5

UNION ALL

SELECT DISTINCT DNI_Cliente
FROM (
    SELECT *
    FROM (
        SELECT V.DNI_Cliente
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT DNI_Cliente FROM venta_2000_2008 WHERE DNI_Cliente < 72500000')
                 AS V(DNI_Cliente INT)
        UNION ALL
        SELECT V.DNI_Cliente
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT DNI_Cliente FROM venta_2009_2016 WHERE DNI_Cliente < 72500000')
                 AS V(DNI_Cliente INT)
        UNION ALL
        SELECT V.DNI_Cliente
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT DNI_Cliente FROM venta_2017_2024 WHERE DNI_Cliente < 72500000')
                 AS V(DNI_Cliente INT)
    ) AS temp_venta1
) AS temp_venta4;

-- C3
SELECT CodLocal, SUM(SumaImporte) / SUM(CantVentas) AS PromedioImporte
FROM (
    SELECT CodLocal, SUM(ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
    FROM (
        SELECT V.CodLocal, V.ImporteTotal
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT CodLocal, ImporteTotal FROM venta_2000_2008 WHERE CodLocal IN (''LOC01'', ''LOC02'', ''LOC03'', ''LOC04'')')
                 AS V(CodLocal VARCHAR, ImporteTotal FLOAT)
        UNION ALL
        SELECT V.CodLocal, V.ImporteTotal
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT CodLocal, ImporteTotal FROM venta_2009_2016 WHERE CodLocal IN (''LOC01'', ''LOC02'', ''LOC03'', ''LOC04'')')
                 AS V(CodLocal VARCHAR, ImporteTotal FLOAT)
        UNION ALL
        SELECT V.CodLocal, V.ImporteTotal
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT CodLocal, ImporteTotal FROM venta_2017_2024 WHERE CodLocal IN (''LOC01'', ''LOC02'', ''LOC03'', ''LOC04'')')
                 AS V(CodLocal VARCHAR, ImporteTotal FLOAT)) AS temp_venta1
    GROUP BY CodLocal) AS aggregated_temp_venta1
GROUP BY CodLocal

UNION ALL

SELECT CodLocal, SUM(SumaImporte) / SUM(CantVentas) AS PromedioImporte
FROM (
    SELECT CodLocal, SUM(ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
    FROM (
        SELECT V.CodLocal, V.ImporteTotal
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT CodLocal, ImporteTotal FROM venta_2000_2008 WHERE CodLocal IN (''LOC05'', ''LOC06'', ''LOC07'', ''LOC08'')')
                 AS V(CodLocal VARCHAR, ImporteTotal FLOAT)
        UNION ALL
        SELECT V.CodLocal, V.ImporteTotal
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT CodLocal, ImporteTotal FROM venta_2009_2016 WHERE CodLocal IN (''LOC05'', ''LOC06'', ''LOC07'', ''LOC08'')')
                 AS V(CodLocal VARCHAR, ImporteTotal FLOAT)
        UNION ALL
        SELECT V.CodLocal, V.ImporteTotal
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT CodLocal, ImporteTotal FROM venta_2017_2024 WHERE CodLocal IN (''LOC05'', ''LOC06'', ''LOC07'', ''LOC08'')')
                 AS V(CodLocal VARCHAR, ImporteTotal FLOAT)) AS temp_venta2
    GROUP BY CodLocal) AS aggregated_temp_venta2
GROUP BY CodLocal

UNION ALL

SELECT CodLocal, SUM(SumaImporte) / SUM(CantVentas) AS PromedioImporte
FROM (
    SELECT CodLocal, SUM(ImporteTotal) AS SumaImporte, COUNT(*) AS CantVentas
    FROM (
        SELECT V.CodLocal, V.ImporteTotal
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT CodLocal, ImporteTotal FROM venta_2000_2008 WHERE CodLocal IN (''LOC09'', ''LOC10'', ''LOC11'', ''LOC12'')')
                 AS V(CodLocal VARCHAR, ImporteTotal FLOAT)
        UNION ALL
        SELECT V.CodLocal, V.ImporteTotal
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT CodLocal, ImporteTotal FROM venta_2009_2016 WHERE CodLocal IN (''LOC09'', ''LOC10'', ''LOC11'', ''LOC12'')')
                 AS V(CodLocal VARCHAR, ImporteTotal FLOAT)
        UNION ALL
        SELECT V.CodLocal, V.ImporteTotal
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT CodLocal, ImporteTotal FROM venta_2017_2024 WHERE CodLocal IN (''LOC09'', ''LOC10'', ''LOC11'', ''LOC12'')')
                 AS V(CodLocal VARCHAR, ImporteTotal FLOAT)) AS temp_venta3
    GROUP BY CodLocal) AS aggregated_temp_venta3
GROUP BY CodLocal;


--C4
SELECT *
FROM (
    SELECT *
    FROM (
        SELECT R.*
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT * FROM reclamo_loc1_loc4 WHERE DNI_Cliente < 72500000')
                 AS R(IdReclamo INT, DNI_Cliente INT, FechaReclamo DATE, CodLocal VARCHAR, Descripcion VARCHAR,
                      Estado VARCHAR)
        UNION ALL
        SELECT R.*
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT * FROM reclamo_loc5_loc8 WHERE DNI_Cliente < 72500000')
                 AS R(IdReclamo INT, DNI_Cliente INT, FechaReclamo DATE, CodLocal VARCHAR, Descripcion VARCHAR,
                      Estado VARCHAR)
        UNION ALL
        SELECT R.*
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT * FROM reclamo_loc9_loc12 WHERE DNI_Cliente < 72500000')
                 AS R(IdReclamo INT, DNI_Cliente INT, FechaReclamo DATE, CodLocal VARCHAR, Descripcion VARCHAR,
                      Estado VARCHAR)
    ) AS temp_reclamo1
    JOIN (
        SELECT DNI_Cliente
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT DNI_Cliente FROM venta_2000_2008 WHERE DNI_Cliente < 72500000')
                AS V(DNI_Cliente INT)
        UNION ALL
        SELECT DNI_Cliente
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT DNI_Cliente FROM venta_2009_2016 WHERE DNI_Cliente < 72500000')
                AS V(DNI_Cliente INT)
        UNION ALL
        SELECT DNI_Cliente
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT DNI_Cliente FROM venta_2017_2024 WHERE DNI_Cliente < 72500000')
                AS V(DNI_Cliente INT)
    ) AS temp_venta1
    ON temp_reclamo1.DNI_Cliente = temp_venta1.DNI_Cliente
) AS result1

UNION ALL

SELECT *
FROM (
    SELECT *
    FROM (
        SELECT R.*
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT * FROM reclamo_loc1_loc4 WHERE DNI_Cliente >= 72500000 AND DNI_Cliente < 75000000')
                 AS R(IdReclamo INT, DNI_Cliente INT, FechaReclamo DATE, CodLocal VARCHAR, Descripcion VARCHAR,
                      Estado VARCHAR)
        UNION ALL
        SELECT R.*
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT * FROM reclamo_loc5_loc8 WHERE DNI_Cliente >= 72500000 AND DNI_Cliente < 75000000')
                 AS R(IdReclamo INT, DNI_Cliente INT, FechaReclamo DATE, CodLocal VARCHAR, Descripcion VARCHAR,
                      Estado VARCHAR)
        UNION ALL
        SELECT R.*
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT * FROM reclamo_loc9_loc12 WHERE DNI_Cliente >= 72500000 AND DNI_Cliente < 75000000')
                 AS R(IdReclamo INT, DNI_Cliente INT, FechaReclamo DATE, CodLocal VARCHAR, Descripcion VARCHAR,
                      Estado VARCHAR)
    ) AS temp_reclamo2
    JOIN (
        SELECT DNI_Cliente
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                 'SELECT DNI_Cliente FROM venta_2000_2008 WHERE DNI_Cliente >= 72500000 AND DNI_Cliente < 75000000')
              AS V(DNI_Cliente INT)
        UNION ALL
        SELECT DNI_Cliente
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                 'SELECT DNI_Cliente FROM venta_2009_2016 WHERE DNI_Cliente >= 72500000 AND DNI_Cliente < 75000000')
              AS V(DNI_Cliente INT)
        UNION ALL
        SELECT DNI_Cliente
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                 'SELECT DNI_Cliente FROM venta_2017_2024 WHERE DNI_Cliente >= 72500000 AND DNI_Cliente < 75000000')
              AS V(DNI_Cliente INT)
    ) AS temp_venta2
    ON temp_reclamo2.DNI_Cliente = temp_venta2.DNI_Cliente
) AS result2

UNION ALL

SELECT *
FROM (
    SELECT *
    FROM (
        SELECT R.*
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                    'SELECT * FROM reclamo_loc1_loc4 WHERE DNI_Cliente >= 75000000')
                 AS R(IdReclamo INT, DNI_Cliente INT, FechaReclamo DATE, CodLocal VARCHAR, Descripcion VARCHAR,
                      Estado VARCHAR)
        UNION ALL
        SELECT R.*
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                    'SELECT * FROM reclamo_loc5_loc8 WHERE DNI_Cliente >= 75000000')
                 AS R(IdReclamo INT, DNI_Cliente INT, FechaReclamo DATE, CodLocal VARCHAR, Descripcion VARCHAR,
                      Estado VARCHAR)
        UNION ALL
        SELECT R.*
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                    'SELECT * FROM reclamo_loc9_loc12 WHERE DNI_Cliente >= 75000000')
                 AS R(IdReclamo INT, DNI_Cliente INT, FechaReclamo DATE, CodLocal VARCHAR, Descripcion VARCHAR,
                      Estado VARCHAR)
    ) AS temp_reclamo3
    JOIN (
        SELECT DNI_Cliente
        FROM dblink('dbname=db1 user=user1 password=password1 host=localhost port=5433',
                 'SELECT DNI_Cliente FROM venta_2000_2008 WHERE DNI_Cliente >= 75000000')
              AS V(DNI_Cliente INT)
        UNION ALL
        SELECT DNI_Cliente
        FROM dblink('dbname=db2 user=user2 password=password2 host=localhost port=5434',
                 'SELECT DNI_Cliente FROM venta_2009_2016 WHERE DNI_Cliente >= 75000000')
              AS V(DNI_Cliente INT)
        UNION ALL
        SELECT DNI_Cliente
        FROM dblink('dbname=db3 user=user3 password=password3 host=localhost port=5435',
                 'SELECT DNI_Cliente FROM venta_2017_2024 WHERE DNI_Cliente >= 75000000')
              AS V(DNI_Cliente INT)
    ) AS temp_venta3
    ON temp_reclamo3.DNI_Cliente = temp_venta3.DNI_Cliente
) AS result3;
