-- DROP TABLE IF EXISTS Tracks; 

-- CREATE TABLE Tracks (
-- 	trackMajor VARCHAR(12),
-- 	trackCode  VARCHAR(10),
-- 	title  	   VARCHAR,
-- 	PRIMARY KEY(trackMajor, trackCode),
-- 	FOREIGN KEY (trackMajor) REFERENCES Majors(major)
-- );

INSERT INTO Tracks (trackMajor,trackCode,title) VALUES ('CptS','SE','Software Engineering Track'),
												  ('CptS','SYS','Systems Track'),	
												  ('CptS','G','General Track'),	
												  ('EE','CE', 'Computer Engineering Track'),	
												  ('EE','ME', 'Microelectronics Track'),	
												  ('EE','POW','Power Track');