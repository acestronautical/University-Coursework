-- DROP TABLE IF EXISTS TrackRequirements; 

-- CREATE TABLE TrackRequirements (
-- 	trackMajor  VARCHAR(12),
-- 	trackCode   VARCHAR(10),
-- 	courseMajor VARCHAR(12),
-- 	courseNo  	VARCHAR(6),
-- 	PRIMARY KEY (trackMajor,trackCode,courseMajor,courseNo),
-- 	FOREIGN KEY (trackMajor,trackCode) REFERENCES Tracks(trackMajor,trackCode),
-- 	FOREIGN KEY (courseNo,courseMajor) REFERENCES Course(courseNo,courseMajor)
-- );


INSERT INTO TrackRequirements (trackMajor,trackCode,courseMajor,courseNo) VALUES 
												  ('CptS','SE','CptS','121'),
												  ('CptS','SE','CptS','122'),	
												  ('CptS','SE','CptS','223'),	
												  ('CptS','SE','CptS','260'),	
												  ('CptS','SE','CptS','322'),	
												  ('CptS','SE','CptS','355'),	
												  ('CptS','SE','CptS','421'),	
												  ('CptS','SE','CptS','423'),	
												  ('CptS','SE','CptS','317'),	
												  ('CptS','SE','CptS','360'),
												  ('CptS','SE','CptS','323'),	
												  ('CptS','SE','CptS','451'),
												  ('CptS','SE','CptS','422'),
  												  ('CptS','SYS','CptS','460'),	
												  ('CptS','SYS','CptS','451'),
												  ('CptS','SYS','CptS','464'),
												  ('CptS','SYS','CptS','466'),
												  ('CptS','SYS','CptS','121'),
												  ('CptS','SYS','CptS','122'),	
												  ('CptS','SYS','CptS','223'),	
												  ('CptS','SYS','CptS','260'),	
												  ('CptS','SYS','CptS','322'),	
												  ('CptS','SYS','CptS','355'),	
												  ('CptS','SYS','CptS','421'),	
												  ('CptS','SYS','CptS','423'),	
												  ('CptS','SYS','CptS','317'),	
												  ('CptS','SYS','CptS','360'),
  												  ('CptS','G','CptS','460'),	
												  ('CptS','G','CptS','451'),
												  ('CptS','G','CptS','422'),
												  ('CptS','G','CptS','443'),
											      ('CptS','G','CptS','121'),
												  ('CptS','G','CptS','122'),	
												  ('CptS','G','CptS','223'),	
												  ('CptS','G','CptS','260'),	
												  ('CptS','G','CptS','322'),	
												  ('CptS','G','CptS','355'),	
												  ('CptS','G','CptS','421'),	
												  ('CptS','G','CptS','423'),	
												  ('CptS','G','CptS','317'),	
												  ('CptS','G','CptS','360'),
												  ('EE','ME','EE','214'),
												  ('EE','ME','EE','234'),
												  ('EE','ME','EE','261'),
												  ('EE','ME','EE','262'),
												  ('EE','ME','EE','311'),												  
												  ('EE','ME','EE','321'),
												  ('EE','ME','EE','331'),
												  ('EE','ME','EE','334'),												  
												  ('EE','ME','EE','341'),
												  ('EE','ME','EE','351'),  
												  ('EE','ME','EE','415'),  												  
												  ('EE','ME','EE','416'),  												  
												  ('EE','ME','EE','431'),
												  ('EE','ME','EE','451'),
												  ('EE','ME','EE','483'),
												  ('EE','ME','EE','476'),
												  ('EE','ME','EE','499'),
												  ('EE','POW','EE','214'),
												  ('EE','POW','EE','234'),
												  ('EE','POW','EE','261'),
												  ('EE','POW','EE','262'),
												  ('EE','POW','EE','311'),												  
												  ('EE','POW','EE','321'),  
												  ('EE','POW','EE','331'),
												  ('EE','POW','EE','334'),												  
												  ('EE','POW','EE','341'), 
												  ('EE','POW','EE','351'), 
												  ('EE','POW','EE','415'), 												  
												  ('EE','POW','EE','416'), 												  
												  ('EE','POW','EE','361'),
												  ('EE','POW','EE','362'),
												  ('EE','POW','EE','483'),
												  ('EE','POW','EE','476'),
												  ('EE','POW','EE','499');
