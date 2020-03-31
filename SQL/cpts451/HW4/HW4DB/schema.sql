-- DROP TABLE IF EXISTS TrackRequirements;
-- DROP TABLE IF EXISTS Prereq;
-- DROP TABLE IF EXISTS Enroll;
-- DROP TABLE IF EXISTS Student;
-- DROP TABLE IF EXISTS Tracks;
-- DROP TABLE IF EXISTS Course;
-- DROP TABLE IF EXISTS Majors;


CREATE TABLE Majors (
    major       VARCHAR(12),
	description VARCHAR,
	PRIMARY KEY(major)
);

CREATE TABLE Course (
    courseMajor VARCHAR(12),
	courseNo  	VARCHAR(6),
	credits   	INTEGER NOT NULL,
    enroll_limit INTEGER,
	PRIMARY KEY(courseNo, courseMajor),
	FOREIGN KEY (courseMajor) REFERENCES Majors(major)
);

CREATE TABLE Tracks (
	trackMajor VARCHAR(12),
	trackCode  VARCHAR(10),
	title  	   VARCHAR,
	PRIMARY KEY(trackMajor, trackCode),
	FOREIGN KEY (trackMajor) REFERENCES Majors(major)
);

CREATE TABLE Student (
	sID  		 CHAR(8),
	sName  	     VARCHAR(30),
	studentMajor VARCHAR(12),
	trackCode 	 VARCHAR(10),
	PRIMARY KEY(sID),
	FOREIGN KEY (studentMajor,trackCode) REFERENCES Tracks(trackMajor,trackCode)
);

CREATE TABLE Enroll (
    courseMajor VARCHAR(12),
	courseNo    VARCHAR(6),
	sID  		CHAR(8),
	grade 	    FLOAT NOT NULL,
	PRIMARY KEY (courseMajor, courseNo, sID),	
	FOREIGN KEY (courseMajor,courseNo) REFERENCES Course(courseMajor,courseNo),
	FOREIGN KEY (sID) REFERENCES Student(sID)
);

CREATE TABLE Prereq (
    courseMajor VARCHAR(12),
	courseNo    VARCHAR(6),
    preMajor    VARCHAR(12),
	preCourseNo VARCHAR(6),
	PRIMARY KEY (courseMajor,courseNo, preMajor, preCourseNo),	
	FOREIGN KEY (courseMajor,courseNo) REFERENCES Course(courseMajor,courseNo),
	FOREIGN KEY (preMajor,preCourseNo) REFERENCES Course(courseMajor,courseNo)
);

CREATE TABLE TrackRequirements (
	trackMajor  VARCHAR(12),
	trackCode   VARCHAR(10),
	courseMajor VARCHAR(12),
	courseNo  	VARCHAR(6),
	PRIMARY KEY (trackMajor,trackCode,courseMajor,courseNo),
	FOREIGN KEY (trackMajor,trackCode) REFERENCES Tracks(trackMajor,trackCode),
	FOREIGN KEY (courseNo,courseMajor) REFERENCES Course(courseNo,courseMajor)
);



