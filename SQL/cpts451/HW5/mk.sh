#!/bin/bash

export PGUSER="postgres";
export PGPASSWORD='postgres';
export PGHOST='localhost';

echo 'db reset start'
psql --dbname=postgres < dbreset.sql
echo 'db reset done'

echo 'csv start'
psql --dbname=hw5 < csv.psql
echo 'csv done'

echo 'decompose start'
psql --dbname=hw5 < decompose.psql
echo 'decompose done'

psql --dbname=hw5