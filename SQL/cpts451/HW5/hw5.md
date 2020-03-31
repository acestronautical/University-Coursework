---
geometry: margin=2cm
output: pdf_document
---

# Ace Cassidy &ensp; CPTS451 &ensp; HW5 &ensp; Spring'20

## Question 1

a. Create a table “MySales “ in the database and load the data from the provided file into that table (use PostgreSQL). Please refer to the Milestone-1 description for instructions on how to import a .csv file in PostgreSQL.

    ```BASH
    CREATE TABLE mysales(
    pname VARCHAR,
    category VARCHAR,
    price INT,
    discount INT,
    month VARCHAR);

    \copy mysales(pname,category,price,discount,month) FROM 'salesData.csv' DELIMITER ',' CSV
    ```

b. You find the following FDs in sales data:

    * pname, category -> price
    * month->discount

    Write two SQL queries which will verify that these FDs hold on the sales data.

    ```SQL
    SELECT pname, category
    FROM mysales
    GROUP BY (pname, category)
    HAVING COUNT (DISTINCT price) > 1;
    ```

    ```SQL
    SELECT month
    FROM mysales
    GROUP BY month
    HAVING COUNT (DISTINCT discount) > 1;
    ```

c. Decompose the table to BCNF relations and create SQL tables for the decomposed schema. Show your work. Create primary keys and foreign keys where appropriate.Turn in the SQL commands for creating the tables

    ```SQL
    SELECT pname, category
    FROM mysales
    GROUP BY (pname, category)
    HAVING COUNT (DISTINCT price) > 1;
    ```
