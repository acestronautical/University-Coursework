#!/bin/bash

psql --host=localhost --dbname=hw4 --username=postgres < schema.sql
psql --host=localhost --dbname=hw4 --username=postgres < majors.sql
psql --host=localhost --dbname=hw4 --username=postgres < course.sql
psql --host=localhost --dbname=hw4 --username=postgres < tracks.sql
psql --host=localhost --dbname=hw4 --username=postgres < student.sql
psql --host=localhost --dbname=hw4 --username=postgres < enroll.sql
psql --host=localhost --dbname=hw4 --username=postgres < prereq.sql
psql --host=localhost --dbname=hw4 --username=postgres < trackReq.sql