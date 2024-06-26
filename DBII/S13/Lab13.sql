SET search_path TO lab12;

-- Create the tables
CREATE TABLE employees (
  emp_no int,
  birth_date date,
  first_name varchar(14),
  last_name varchar(16),
  gender character(1),
  hire_date date,
  dept_no varchar(5),
  from_date date
);


CREATE TABLE salaries (
  emp_no int,
  salary int ,
  from_date date,
  to_date date
);

/* SET UP */

-- Upload the data (FROM TERMINAL)
\copy employees(emp_no, birth_date, first_name, last_name, gender, hire_date, dept_no, from_date) FROM 'C:\\Users\\jeffr\\Desktop\\data2\\employees.csv' DELIMITER ',' CSV HEADER;

\copy salaries(emp_no, salary, from_date, to_date) FROM 'C:\\Users\\jeffr\\Desktop\\data2\\salaries.csv' DELIMITER ',' CSV HEADER;

SELECT COUNT(*) FROM salaries;
SELECT COUNT(DISTINCT emp_no) FROM salaries;

-- Select all the distinct values of emp_no and count
SELECT COUNT(*) FROM employees;
SELECT COUNT(DISTINCT emp_no) FROM employees;

-- I want to return the rows that have the same emp_no more that one time of the table employees
SELECT emp_no, COUNT(*)
FROM employees
GROUP BY emp_no
HAVING COUNT(*) > 1;




/* PART 1. PARTITION BY LIST */

-- First, we take a look to the distribution of the data in base of the attribute dept_no
SELECT dept_no, COUNT(*)
FROM employees
GROUP BY dept_no
ORDER BY count(*) DESC;

-- Lets query the data and find out how long is the execution time
EXPLAIN ANALYZE
SELECT COUNT(*)
FROM employees
WHERE dept_no = 'd001';
-- Around 77.673 ms


-- Now we will create the partitions
-- Create the table that will handle the partitions
CREATE TABLE employees1 (
  emp_no int,
  birth_date date,
  first_name varchar(14),
  last_name varchar(16),
  gender character(1),
  hire_date date,
  dept_no varchar(5),
  from_date date
) PARTITION BY LIST (dept_no);

-- Create the partitions
CREATE TABLE employees1_1 PARTITION OF employees1 FOR VALUES IN ('d001', 'd005');
CREATE TABLE employees1_2 PARTITION OF employees1 FOR VALUES IN ('d002', 'd003', 'd004');
CREATE TABLE employees1_3 PARTITION OF employees1 FOR VALUES IN ('d006', 'd007', 'd008', 'd009');

-- Now we can insert the data into the partitioned table (IN TERMINAL)
\copy employees1(emp_no, birth_date, first_name, last_name, gender, hire_date, dept_no, from_date) FROM 'C:\\Users\\jeffr\\Desktop\\data2\\employees.csv' DELIMITER ',' CSV HEADER;

-- Check that the data was inserted equitably
SELECT
  (SELECT count(*) FROM employees1_1) AS employees1_1,
  (SELECT count(*) FROM employees1_2) AS employees1_2,
  (SELECT count(*) FROM employees1_3) AS employees1_3;
-- Aproximately 100k rows in each partition


-- We obligate psql to use the partition pruning
SET enable_partition_pruning = on;


-- Testing with some queryes to see the performance
EXPLAIN ANALYZE
SELECT COUNT(*) FROM employees1
WHERE dept_no = 'd001';
-- Amazing, around 22.727 ms


/* PART 2. PARITION BY RANGE */

-- First we take a look to the distribution of the data in base of the attribute hire_date
SELECT date_part('year', hire_date) AS year, COUNT(*)
FROM employees
GROUP BY year
ORDER BY year;

-- Lets query the data and find out how long is the execution time
EXPLAIN ANALYZE
SELECT COUNT(*)
FROM employees
WHERE date_part('year', hire_date) < 1988;
-- Around 123.554 ms

-- Now we will create the partitions
-- Create the table that will handle the partitions
CREATE TABLE employees2 (
  emp_no int,
  birth_date date,
  first_name varchar(14),
  last_name varchar(16),
  gender character(1),
  hire_date date,
  dept_no varchar(5),
  from_date date
) PARTITION BY RANGE (date_part('year', hire_date));

-- We create the partitions
CREATE TABLE employees2_before_1988 PARTITION OF employees2 FOR VALUES FROM (MINVALUE) TO (1988);
CREATE TABLE employees2_1988_1995 PARTITION OF employees2 FOR VALUES FROM (1988) TO (1995);
CREATE TABLE employees2_1995_2001 PARTITION OF employees2 FOR VALUES FROM (1995) TO (2001);

-- Now we can insert the data into the partitioned table (IN TERMINAL)
\copy employees2(emp_no, birth_date, first_name, last_name, gender, hire_date, dept_no, from_date) FROM 'C:\\Users\\jeffr\\Desktop\\data2\\employees.csv' DELIMITER ',' CSV HEADER;

-- The fragmentation in base of the vector [1988, 1995] is not equitable