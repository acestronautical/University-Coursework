SELECT  ename
FROM    Emp
WHERE  dno=132;


SELECT  mgr
FROM    Dept
WHERE  dname = 'Marketing';

SELECT   *
FROM    Emp
WHERE  ename = 'Jack' AND sal>50000;

-- Theta joins
SELECT   *
FROM    Emp, Dept
WHERE  Emp.dno = Dept.dno;

SELECT   *
FROM    Emp, Dept, ProjectEmp, Proj
WHERE  Emp.dno = Dept.dno AND Emp.ssn = ProjectEmp.ssn AND ProjectEmp.proj_id = Proj.proj_id;

SELECT   Emp.ename, Dept.dno, Proj.ptitle
FROM    Emp, Dept, ProjectEmp, Proj
WHERE  Emp.dno = Dept.dno AND Emp.ssn = ProjectEmp.ssn AND ProjectEmp.proj_id = Proj.proj_id;

SELECT distinct  dno
FROM     Emp;

SELECT   ename, mgr
FROM    Emp, Dept
WHERE  Emp.dno = Dept.dno AND 
                mgr ='Alice';

SELECT   ename, mgr as manager
FROM    Emp, Dept
WHERE  Emp.dno = Dept.dno AND 
                manager='Alice';

-- renaming attributes
SELECT   ename,dno, 'temporary' as status
FROM    Emp
WHERE  sal<50000;  


SELECT   ename, sal
FROM    Emp
WHERE  ename='O''Fallon';

SELECT   eNaMe, sal*1.05 as newSalary
FROM    Emp
WHERE  ename='O''Fallon';

-- RENAMING RELATIONS

--employees who make more money than their manager
SELECT  E1.ename, D.dname,E1.sal, D.mgr, E2.sal as manager_sal
FROM     Emp as E1, Dept as D, Emp as E2
WHERE    E1.dno = D.dno AND
	     D.mgr = E2.ename AND  E1.sal > E2.sal;
			 
-- Employees who earn the same sal,  
SELECT  E1.ssn, E1.ename, E1.sal, E2.ssn, E2.ename, E2.sal
FROM      Emp as E1, Emp as E2
WHERE    E1.sal = E2.sal AND E1.ssn<>E2.ssn;
--we get each pair twice 

SELECT  E1.ssn, E1.ename, E1.sal, E2.ssn, E2.ename, E2.sal
FROM      Emp as E1, Emp as E2
WHERE    E1.sal = E2.sal AND E1.ssn < E2.ssn;
--we get each pair once 

--the employees who work on the same project as their manager        
SELECT   E1.ename, D.dname, E2.ename, PE1.proj_id, PE2.proj_id,P.ptitle
FROM     Emp as E1, Dept D, Emp as E2, ProjectEmp as PE1, ProjectEmp as PE2, Proj as P
WHERE    E1.dno = D.dno AND PE1.ssn = E1.ssn AND PE2.ssn = E2.ssn 
         AND P.proj_id = PE1.proj_id
	     AND D.mgr = E2.ename AND E1.ename <> E2.ename  
         AND PE1.proj_id = PE2.proj_id;
---------------------------------------------------------
-- conditions on dates and strings
SELECT  *
FROM 	Emp, Dept, ProjectEmp, Proj
WHERE   Emp.dno = Dept.dno AND Emp.ssn = ProjectEmp.ssn AND ProjectEmp.proj_id = Proj.proj_id AND
		 ename >'J' AND sal < 70000 
         AND Proj.startdate> '1/1/2017' AND ptitle LIKE '%Software' AND ename <>'Mary';;

-- querying for NULL values
SELECT ename, sal
FROM    Emp
WHERE  sal<=50K     OR sal>50K; 

SELECT ename, sal
FROM    Emp
WHERE  sal<=50000 OR sal>50000 OR sal is NULL; 

-- ordering 
SELECT *
FROM    Emp
WHERE  sal<=50000
ORDER BY dno, sal desc, ename;

SELECT *
FROM    Emp
WHERE  sal<=50000 OR sal IS NULL
ORDER BY dno NULLS FIRST, sal desc, ename;

--set operations
(SELECT  ename FROM Emp, Dept 
 WHERE Emp.dno=Dept.dno  AND dname = 'Purchasing')
UNION
(SELECT  ename FROM Emp, Dept 
 WHERE Emp.dno=Dept.dno  AND dname ='HR')
 -- eliminates duplicates in the results
 
SELECT  ename  
FROM Emp, Dept 
WHERE Emp.dno=Dept.dno  AND (dname = 'Purchasing' OR dname='HR');
--have duplicates

(SELECT  ename FROM Emp, Dept 
 WHERE Emp.dno=Dept.dno  AND dname = 'Purchasing')
INTERSECT
(SELECT  ename FROM Emp, Dept 
 WHERE Emp.dno=Dept.dno  AND dname ='HR')
 
SELECT  ename,dname  
FROM Emp, Dept 
WHERE Emp.dno=Dept.dno  AND (dname = 'Purchasing' AND dname='HR');
-- no results


--NOT all systems support intersect operator. Alternative query for intersect.
SELECT  E1.ssn,E1.ename 
FROM Emp E1, emp E2
WHERE E1.ssn = E2.ssn AND E1.dno = 111 AND E2.dno=888;


(SELECT  ename FROM Emp, Dept 
 WHERE Emp.dno=Dept.dno  AND dname = 'Purchasing')
EXCEPT
(SELECT  ename FROM Emp, Dept 
 WHERE Emp.dno=Dept.dno  AND dname ='HR')

SELECT  E1.ssn,E1.ename 
FROM Emp E1, emp E2
WHERE E1.ssn = E2.ssn AND E1.dno = 111 AND E2.dno<>888;

-- will not work.. will get additional results
-- later we will see how write this using subquery conditions. 

SELECT   R.A FROM R
 intersect 
(    (SELECT   S.A FROM S)
      union	
      (SELECT   T.A FROM T)
);

((SELECT   R.A FROM R) intersect (SELECT   S.A FROM S))
union	
((SELECT   R.A FROM R) intersect (SELECT   T.A FROM T));


(SELECT   R.A FROM R, S  WHERE   R.A=S.A)
union
(SELECT   R.A FROM R, T WHERE   R.A=T.A);

SELECT R.A
FROM R,S,T
WHERE R.A=S.A or R.A=T.A;
---------------------------------------

Aggregation

SELECT MIN(sal), MAX(sal), AVG(sal)
FROM   Emp, Dept
WHERE  Emp.dno = Dept.dno  and  Dept.dname = 'Marketing';

--output: relation with a single attribute with a single row
-- if no grouping the aggragate functions are applied to complete column. 
-- Except count, all aggregations apply to a single attribute
-- Count can be used on more than one attribute, even *

SELECT  COUNT(ename) FROM Emp;
SELECT  COUNT(*) FROM Emp;

SELECT  COUNT(distinct ename) FROM Emp;

SELECT  COUNT(distinct dno) FROM Emp;
------------
-- When there is grouping aggregate functions applied to attribute value in each group. 
SELECT Dept.dno,SUM(sal), COUNT(ename)
FROM   Emp, Dept
WHERE  Emp.dno = Dept.dno 
GROUP BY Dept.dno;

SELECT Dept.dno,ename, SUM(sal), COUNT(ename)
FROM   Emp, Dept
WHERE  Emp.dno = Dept.dno 
GROUP BY Dept.dno,ename;

----------
SELECT dno
FROM Emp 
GROUP BY dno
ORDER BY dno;
--vs
SELECT distinct dno
FROM Emp 
ORDER BY dno;

SELECT distinct dno,sal
FROM Emp
ORDER BY dno;
-- vs
SELECT dno,sal
FROM Emp
GROUP BY dno,sal
ORDER BY dno;

--------

SELECT dname, SUM(sal), COUNT(ssn)
FROM   Emp, Dept
WHERE  Emp.dno = Dept.dno 
GROUP BY dname;

SELECT dname, SUM(sal), COUNT(ssn)
FROM   Emp, Dept
WHERE  Emp.dno = Dept.dno 
GROUP BY dname
HAVING COUNT(ssn)>2;

--------------------------
-- Projects with employees from at least 6 different departments.   

SELECT proj_id, Emp.ssn, dno 	
FROM  ProjectEmp, Emp			
WHERE  ProjectEmp.ssn = Emp.ssn  
ORDER BY proj_id, dno



SELECT proj_id, COUNT(distinct dno) as countDept
FROM  ProjectEmp, Emp		
WHERE  ProjectEmp.ssn = Emp.ssn 
GROUP BY proj_id
HAVING COUNT(distinct dno) >= 6
ORDER BY countDept
  


---------
-- Employees working in departments with at least 2 employees
SELECT Emp.ssn, Emp.ename, count(*) 		
FROM  Emp, Dept 			
WHERE  Emp.dno = Dept.dno  
GROUP BY Emp.ssn,Emp.ename      			       
HAVING count(distinct Dept.dno) > 1      		       
ORDER BY Emp.ssn,Emp.ename; 

SELECT E1.ssn, E1.ename,  SUM(E2.sal)  		
FROM  Emp  E1, Dept, Emp  E2			
WHERE  E1.dno = Dept.dno  AND E2.ename = Dept.mgr 
GROUP BY E1.ssn,E1.ename      			       
HAVING count(distinct Dept.dno) > 1      		       
ORDER BY E1.ssn,E1.ename; 

---------
--SUBQUERIES
-----------
SELECT E1.ssn, E1.ename
FROM Emp as E1, Emp as E2
WHERE E2.ename = 'Jack' AND E1.dno = E2.dno

SELECT ssn,ename
FROM Emp
WHERE dno IN
	(SELECT dno
	FROM Emp
	WHERE ename = 'Jack')

---------
--List departments which has employees with salaries more than 60K
SELECT dno,dname
FROM  Dept
WHERE dno IN
	( SELECT dno                              	
	  FROM Emp			
	  WHERE sal>60000); 
      
SELECT dno,dname
FROM   Emp E1, Dept D
WHERE  E1.dno=D.dno AND sal>60000;

---------
--List the department names who has more than 2 employees
    SELECT Emp.dno
    FROM Emp, Dept
    WHERE Emp.dno=Dept.dno
    GROUP BY Emp.dno
    HAVING COUNT(ssn)>2;

SELECT dname, dno 
FROM Dept 
WHERE dno IN
  (SELECT Dept.dno
    FROM Emp, Dept
    WHERE Emp.dno=Dept.dno
    GROUP BY Dept.dno
    HAVING COUNT(ssn)>2)

------
-- Employees who work in Purchasing department but not in HR department.
(SELECT  ename FROM Emp, Dept 
 WHERE Emp.dno=Dept.dno  AND dname = 'Purchasing')
EXCEPT
(SELECT  ename FROM Emp, Dept 
 WHERE Emp.dno=Dept.dno  AND dname ='HR')

SELECT  E1.ename 
FROM emp as E1, emp as E2, Dept as D1, Dept as D2
WHERE E1.ssn = E2.ssn AND E1.dno = D1.dno AND D1.dname = 'Purchasing' AND
      E2.dno<>D2.dno AND D2.dname='HR';
	  

select * from emp
select * from dept

SELECT  E.ename 
FROM emp E
WHERE E.ssn IN 
	(SELECT ssn FROM Emp,Dept where Emp.dno=Dept.dno AND dname='Purchasing') 
AND E.ssn NOT IN 
    (SELECT ssn FROM Emp,Dept where Emp.dno=Dept.dno AND dname='HR');


--Find employee(s) with the highest salary

SELECT ename,max(sal)
FROM Emp

SELECT  distinct ename, sal 
FROM    emp
WHERE sal >= ALL 
	(SELECT MAX(sal) 
	 FROM  Emp);

SELECT distinct ename,ssn
FROM Emp 
WHERE sal >= ALL
	(SELECT sal
	 FROM Emp
	 WHERE sal IS NOT NULL)

--------
--Who makes more than someone in the Hardware department?

SELECT ename,sal
FROM Emp
WHERE sal >= ANY
		(SELECT sal
		FROM Emp,  Dept
		WHERE Emp.dno = Dept.dno AND  Dept.dname = 'Hardware' sal IS NOT NULL);

SELECT ename,sal
FROM Emp
WHERE sal >= ALL
		(SELECT sal 
		FROM Emp,  Dept
		WHERE Emp.dno = Dept.dno AND  Dept.dname = 'Hardware' AND sal IS NOT NULL);
		
--------
--Who works in the 'Production' department?
SELECT   ename,dno
FROM     Emp
WHERE  Emp.dno =
		(SELECT dno
		 FROM  Dept
		 WHERE dname='Production');
         
--SUBQUERIES in FROM
SELECT dno, SUM(sal) as totalSal, COUNT(ename) as numEmp
FROM   Emp
GROUP BY dno
HAVING COUNT(ssn)>1;

SELECT Temp.dno, Temp.totalSal, Temp.numEmp
FROM   (
	SELECT dno, SUM(sal) as totalSal , COUNT(ename) as numEmp
	FROM   Emp
	GROUP BY dno
 ) AS Temp
WHERE Temp.numEmp > 1;

 -----
--Find the employees in the departments whose total salary amount is more than $200K
--- find the total salary in each department
--- return those whose total salary is > 200K
SELECT Emp.ename
FROM   Emp
WHERE Emp.dno IN (
	SELECT dno
	FROM   Emp
	GROUP BY dno
	HAVING SUM(sal) >200000);

SELECT Emp.ename
FROM   (
	SELECT dno, SUM(sal) as totalSal 
	FROM   Emp
	GROUP BY dno
 ) AS Temp, Emp
WHERE Temp.dno=Emp.dno  AND Temp.totalSal>200000;

-----------------------------------
--- Addtional Subquery Examples
-----------------------------------
--Employees who work on some project
SELECT distinct Emp.ssn, ename 
FROM projectEmp, Emp
WHERE ProjectEmp.ssn=Emp.ssn;

SELECT distinct ssn, ename 
FROM Emp
WHERE ssn IN (SELECT ssn FROM projectEmp);

SELECT distinct ssn, ename 
FROM Emp as E
WHERE EXISTS (SELECT * FROM projectEmp as PE
               WHERE E.ssn = PE.ssn);


--Employees who doesn't work on any projects
SELECT distinct ssn, ename 
FROM Emp
WHERE ssn NOT IN (SELECT ssn FROM projectEmp);

SELECT ssn, ename 
FROM Emp as E
WHERE NOT EXISTS (SELECT * FROM projectEmp as PE
                   WHERE E.ssn = PE.ssn);
				   
-----------
--Find the employee with highest salary 
SELECT  distinct ename, sal 
FROM emp
WHERE sal >= ALL 
	(SELECT MAX(sal) 
	 FROM  Emp);

 
SELECT distinct ename, sal 
FROM Emp as E1
WHERE NOT EXISTS (SELECT * FROM Emp as E2
                   WHERE E1.sal < E2.sal) AND 
                   E1.sal IS NOT NULL;


-- Find the employees whose salary is greater than overall average salary.
select *
from Emp E
where sal > 
		(SELECT AVG(sal) 
		 FROM Emp E2);

-- Find the employees whose avg salary is greater than the average salary in the department they work in.
select *
from Emp E1
where sal > 
		(SELECT AVG(sal) 
		 FROM Emp E2
         WHERE E1.dno = E2.dno);
   

 ---Find the employees that work on all projects
SELECT * 
FROM Emp E
WHERE NOT EXISTS (
   SELECT *
   FROM Proj
	WHERE proj_id NOT IN 
     	(SELECT proj_id 
	 	 FROM ProjectEmp
		 WHERE ssn = E.ssn)
)

------
--Find the department names that has the max total salary amount among all departments
-- 1. find the total sal in each dept
-- 2. find the max among the total sal.

SELECT *
FROM (SELECT dno, SUM(sal) as totalSal 
      FROM   Emp
      GROUP BY dno) as Temp2
      WHERE totalSal = 
        	(SELECT max(Temp1.totalSal)
	         FROM (SELECT dno, SUM(sal) as totalSal 
	 	           FROM   Emp
		           GROUP BY dno) as Temp1)      


-- Additional examples	 
	 
--Suppliers(sid, sname, address)  
--Parts(pid, pname, color)  
--Catalog(sid, pid, cost)

--Query 1: Find the distinct sids of suppliers who supply only red parts.

(SELECT sid 
 FROM Catalog C1, Parts P1
 WHERE C1.pid=P1.pid AND
       P1.color='Red') 
EXCEPT
(SELECT sid 
 FROM Catalog C2, Parts P2
 WHERE C2.pid=P2.pid AND
       P2.color<>'Red'); 


SELECT distinct C.sid
FROM Catalog C1, Parts P1
WHERE C1.pid = P1.pid AND
	  P1.color='Red' AND
      NOT EXISTS (SELECT * FROM Catalog C2, Parts P2
                   WHERE C2.pid=P2.pid AND
                 	     P2.color<>'Red' AND
                         C1.sid=C2.sid);
                         
SELECT distinct sid
FROM Catalog 
WHERE sid IN 
	(SELECT sid 
     FROM Catalog C1, Parts P1
     WHERE C1.pid=P1.pid AND
           P1.color='Red') 
    AND sid NOT IN 
	(SELECT sid 
     FROM Catalog C2, Parts P2
     WHERE C2.pid=P2.pid AND
           P2.color<>'Red'); 
          