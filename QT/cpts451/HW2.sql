-- Homework2                                                             CPTS451
-- Ace Casidy                                                         Spring '20

-- post
CREATE TABLE posts(
  -- popularity COMPUTED
  ID int PRIMARY KEY,
  kind char,
  ts timestamp,
  content varchar,
  userID int NOT NULL, -- publishes
  FOREIGN KEY(userID) REFERENCES users(ID)
);
-- about
CREATE TABLE about (
  PRIMARY KEY(postID, courseworkID),
  postID int,
  courseworkID int,
  FOREIGN KEY(postID) REFERENCES posts(ID),
  FOREIGN KEY(courseworkID) REFERENCES courseworks(ID)
);
-- responds
CREATE TABLE responds (
  rToPost int,
  rForPost int,
  PRIMARY KEY(rToPost, rForPost),
  FOREIGN KEY(rToPost) REFERENCES posts(ID),
  FOREIGN KEY(rForPost) REFERENCES posts(ID)
);
-- likes
CREATE TABLE likes (
  postID int,
  userID int,
  PRIMARY KEY(postID, userID),
  FOREIGN KEY(postID) REFERENCES posts(ID),
  FOREIGN KEY(userID) REFERENCES users(ID)
);
-- users
CREATE TABLE users (
  ID int PRIMARY KEY,
  firstName varchar(50),
  lastName varchar(50),
  email varchar(50)
);
-- phones
CREATE TABLE phones (
  PRIMARY KEY(ID, num),
  num varchar(11),
  type char,
  userID int,
  FOREIGN KEY(userID) REFERENCES users(ID)
);
-- instructors
CREATE TABLE instructors (
  userID int PRIMARY KEY,
  title varchar,
  FOREIGN KEY(userID) REFERENCES users(ID)
);
-- students
CREATE TABLE students (
  userID int PRIMARY KEY,
  major varchar(4),
  FOREIGN KEY(userID) REFERENCES users(ID)
);
-- submits
CREATE TABLE submits (
  assignmentID int,
  studentID int,
  PRIMARY KEY(assignmentID, studentID),
  FOREIGN KEY(assignmentID) REFERENCES assignments(courseworkID),
  FOREIGN KEY(studentID) REFERENCES students(userID)
);
-- takes
CREATE TABLE takes (
  examID int,
  studentID int,
  score int,
  PRIMARY KEY(examID, studentID),
  FOREIGN KEY(examID) REFERENCES exams(courseworkID),
  FOREIGN KEY(studentID) REFERENCES students(userID)
);
-- courseworks
CREATE TABLE courseworks(
  ID int PRIMARY KEY,
  title varchar,
  courseNum int,
  sectionNum int,
  term int,
  year int,
  major varchar(4),
  FOREIGN KEY(courseNum, sectionNum, term, year, major) REFERENCES classes(courseNum, sectionNum, term, year, major)
);
-- assignments
CREATE TABLE assignments (
  courseworkID int PRIMARY KEY,
  deadline datetime,
  FOREIGN KEY(courseworkID) REFERENCES courseworks(ID)
);
-- exams
CREATE TABLE exams (
  courseworkID int PRIMARY KEY,
  examTime time,
  examLocation varchar,
  FOREIGN KEY(courseworkID) REFERENCES courseworks(ID)
);
-- classes
CREATE TABLE classes(
  PRIMARY KEY(courseNum, sectionNum, term, year, major),
  enrollmentLimit int,
  endDate date,
  startDate date,
  courseNum int,
  sectionNum int,
  term int,
  year int,
  major varchar(4),
  FOREIGN KEY(courseNum) REFERENCES courses(num),
  FOREIGN KEY(major) REFERENCES courses(major)
);
-- enrolls_in
CREATE TABLE enrolls_in (
  grade char,
  PRIMARY KEY(
    courseNum,
    sectionNum,
    term,
    year,
    major,
    studentID
  ),
  courseNum int,
  sectionNum int,
  term int,
  year int,
  major varchar(4),
  FOREIGN KEY(courseNum, sectionNum, term, year, major) REFERENCES classes(
    courseNum,
    sectionNum,
    term,
    year,
    major
  ),
  studentID int,
  FOREIGN KEY(studentID) REFERENCES students(userID)
);
-- teaches
CREATE TABLE teaches(
  PRIMARY KEY(
    courseNum,
    sectionNum,
    term,
    year,
    major,
    instructorID
  ),
  courseNum int,
  sectionNum int,
  term int,
  year int,
  major varchar(4),
  FOREIGN KEY(courseNum, sectionNum, term, year, major) REFERENCES classes(
    courseNum,
    sectionNum,
    term,
    year,
    major
  ),
  instructorID int,
  FOREIGN KEY(instructorID) REFERENCES instructors(userID)
);
-- courses
CREATE TABLE courses (
  major varchar(4),
  courseNum int,
  title varchar,
  level int
);
-- prerequisites
CREATE TABLE prerequisites (
  pOfMajor varchar(4),
  pOfCourseNum int,
  pForMajor varchar(4),
  pForCourseNum int,
  PRIMARY KEY(pOfCourseNum, pOfMajor, pForCourseNum, pForMajor),
  FOREIGN KEY(pOfMajor, pOfCourseNum) REFERENCES courses(major, courseNum),
  FOREIGN KEY(pForMajor, pForCourseNum) REFERENCES courses(major, courseNum),
);

-- Could not enforce total participation for enrolls_in and teaches