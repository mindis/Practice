-- View with Notepad++ highlighting SQL 
-- Comments with SQL begin with '--' or uses the /* Comment In Here */ 
Table of Contents 
- Introduction
- Select Statement
	- Select
	- From
	- Where
	- Order By 
	- Select * 
- Rename Operator 
	- Getting rid of ambiguity 
	- Self-Joint
- Set Operators 
	- union all 
	- intersect
- Like Statement 
- Aggregation => Analysis on the data  
	- Duplicates matter in analysis 
	- In Statement 
- JOIN Operator 
- SQL Functions 
	i) Count(A), Count(*)
	ii) Max(A)
	iii) Min(A)
	iv) Sum(A)
	v) Avg(A) -- Average 
//-------------------------------------------------------------------
-- Introduction 
//-------------------------------------------------------------------
SQL 2 standard => SQL 92
SQL embedded in programs
SQL => Declarative language 
Query Optimizer => Take query written on database and 
figure out best way to execute that onto the database. 
SQL foundation is based on relational algebra. 

Data Definition Language
	- Create table
	- Drop table

Data Manipulation Language
	- Query the database
		- Select, From, Where
	- Modifying database 
		- Insert
		- Delete
		- Update
		
---------------------------------------------------------------------
-- SELECT Statement
---------------------------------------------------------------------
SQL 	  |		Relational Algebra
Select 	  |		Project
From  	  |		Cross Product		
Where	  |		Select 
NATURAL JOIN |  Natural Join -- automatically group same Attributes
INNER JOIN | 	Theta Join -- cross product with condition  (NOT Natural Join) 

Each Table is known as a Relation 
Each table has attributes (columns of table) 

To order the final output ascending, 
-- Code Begin
	Select attribute1
	from Relation1
	where Relation1.attribute1 > 0 and Relation2.attribute1 = 'Place' -- use 'and' to get multiple constraints
	ORDER BY attribute2 desc; 
-- Code End 

note: ORDER BY automatically sorts the results as it has to compare them anyway. 
It also removes duplicates as a result. To include duplicates, use 'union all' 

Note: Everything is NOT case sensitive except for literals (within '' marks)
Style Guidelines: 
	Keywords in full caps: SELECT
	Relation with first letter CAP: Student 
	attribute with all small alphabets: gpa 

-- Code Begin
	SELECT *
	UNION ALL 
	SELECT * 
	ORDER BY attribute1; 
-- Code End 

Almost everything in SQL is 
Commutative (Except (LEFT/RIGHT) OUTER JOIN)
Associative (Except(LEFT/RIGHT/FULL)  OUTER JOIN) 



SELECT *  -- means project all attributes 

---------------------------------------------------------------------
-- Set Operators
---------------------------------------------------------------------

i) UNION ALL
-- refer to Order By for examples

ii) INTERSECT
To get all students who apply to both 'CS' and 'EE' majors
-- Code Begin
	SELECT id FROM Apply WHERE Major = 'CS'
	INTERSECT
	SELECT id FROM Apply WHERE Major = 'EE' 
-- Code End

iii) EXCEPT (difference set operation) 

To get students who applied to CS but not to EE
-- Get all students who apply to CS and remove all students
-- from those list who applied to EE 

-- Approach 1: Using EXCEPT Operator
-- Code Begin
	SELECT id FROM Apply WHERE Major = 'CS'
	EXCEPT
	SELECT id FROM Apply WHERE Major = 'EE' 
-- Code End
-- This works, however, if no Except operator implemented. 

-- Approach 2: Self-Joints
-- Code Begin
	SELECT DISTINCT A1.id
	FROM Apply A1, Apply A2
	WHERE A1.id = A2.id AND A1.major = 'CS' AND A2.major != 'EE'
-- Code End
However, this finds all pairs of records where
first person in pair applied to CS  & 
second person in pair did not apply to EE
which is not what we want
(Second student can apply to anything else other than EE) 

-- Approach 3: Using subqueries
-- Code Begin
	SELECT id, name
	FROM Student
	WHERE id IN (SELECT id FROM Apply WHERE Major = 'CS')
		AND id NOT IN (SELECT id FROM Apply WHERE Major = 'EE');		
-- Code End
-- note: The last line and this next line are equivalent
		AND NOT id IN (SELECT id FROM Apply WHERE Major = 'EE');		


---------------------------------------------------------------------
-- Rename 
---------------------------------------------------------------------
Rename are used for self joints and identify Attributes with same names
but in different Relations. 

-- To demonstrates Relation renaming and attribute renaming 
-- Code Begin
	Select S.attribute1, C.attribute1 as attributeNewName
	From Student S, College C -- renaming Relation Student to S 
	Where S.attribute1 = C.attribute1
-- Code End

-- Self Joints

-- Attempt to find all pairs of students with same GPA
-- Code Begin
	Select S1.ID
	From Student S1, Student S2
	where S1.gpa = S2.gpa
-- Code End

However, this executes every pair of students with same GPA 
but will include same students paired with itself. 
Therefore, exclude students paired with themself. 
-- Code Begin
	Select S1.ID
	From Student S1, Student S2
	where S1.gpa = S2.gpa and S1.ID != S2.ID
	-- note: '!=' can sometimes be written as '<>'
-- Code End

However, this will output pairs of students twice, 
one with StudentA + StudentB, the other with
StudentB + StudentA, which is the same pair, just different order. 
Therefore, use the '<' sign instead
-- Code Begin
	Select S1.ID
	From Student S1, Student S2
	where S1.gpa = S2.gpa and S1.ID < S2.ID
-- Code End


---------------------------------------------------------------------
-- LIKE statement
---------------------------------------------------------------------
-- LIKE statement is basically used for pattern maching
-- These special keys are known as Wildcards in SQL 
SQL  	| 		bash
%	 	|   	*		-- Any number of characters from 0 to infinity 
_		|		? 		-- Match single character
[A-C] 	|		[A-C]	-- A single character from domain A, B, C
[ABD]	|		[ABD]	-- A single character from domain A, B, D
[!bsp]  | 		[!bsp]	-- A single character that is NOT b,s,p
A		|		A		-- the character 'A' must be in this position


---------------------------------------------------------------------
-- Aggregation 
---------------------------------------------------------------------

- min
- max
- sum
- average
- count

Unlike Project in relational algebra, SQL maintains the duplicates 
because they influence the results of analysis. 

Why duplicates or no duplicates matter and influence results. 

Example: 
To calculate average GPA of students who applied to CS major
Approach 1: Using Subqueries (In Statement) 
-- Code Begin
	Select gpa 
	From Student
	Where id In (Select id From Apply where major = 'CS')
-- Code End
This approach will get you the unique students, so 
computation of average will be correct. 

Approach 2: Using Join
-- Code Begin
	Select gpa
	From Student, Apply
	Where Student.id = Apply.id and major = 'CS';
-- Code End 
However, students who apply to multiple times for 'CS', 
will get more than unique students. Therefore, computing average is wrong. 

Approach 3: Using Distinct operator

-- Code Begin
	Select distinct gpa
	From Student, Apply
	Where Student.id = Apply.id and major = 'CS';
-- Code End 
Since some students have same gpa, 
will end up getting rid of multiple unique students
with same gpa, therefore, lower number of students than all unique students,
so computation of average gpa is wrong as well. 


To calculate college with 
maximum enrollment. 

Approach 1: Using Subqueries
-- Begin Code
	SELECT cName 
	FROM College C1
	WHERE NOT EXISTS (SELECT * FROM College C2 WHERE C2.enrollment = C1.enrollment)
-- End Code

To calculate student with highest GPA 

Approach 1: Subquery 	
-- Begin Code
	SELECT studentName
	FROM Student C1
	WHERE NOT EXISTS (SELECT * FROM Student C2 WHERE C2.gpa > C1.gpa); 
-- End Code
-- Correct but may have duplicates if students tied with same highest gpa. 
Note: EXISTS means that the set in the (...) does not evaluate 
to the empty set. 
Note: NOT EXISTS means that the set in (...) does evaluate to the
empty set. 

Approach 2: Joins

-- Begin Code
	SELECT DISTINCT S1.sName, S1.gpa
	FROM Student S1, Student S2
	WHERE S1.gpa > S2.gpa; 
-- End Code
-- Wrong as this finds all students who do not have lowest GPA


Approach 3: Joins with ALL
-- Begin Code
	SELECT sName, gpa
	FROM Student
	WHERE GPA >= ALL (SELECT gpa FROM Student); 
-- End Code



---------------------------------------------------------------------
-- JOIN Operator 
---------------------------------------------------------------------

JOIN operator helps processor find out better way to find
efficient operation. 

example on how to use
-- Begin Code
	SELECT Apply.id, sName, gpa, Apply.cName, enrollment
	FROM (Apply JOIN Student ON Apply.id = Student.id) JOIN College
	ON Apply.cName = College.cName
-- End Code

INNER JOIN => Theta Join

To be able to do natural join on certain columns only, use USING

-- Begin Code
	SELECT sName, gpa
	FROM Student JOIN Apply USING(id)
	WHERE size < 1000 AND major = 'CS' and cName = 'Stanford'; 
-- End Code

Note: Most SQL systems won't let you use both USING and ON operator in same statement

Note: Natural Join a Relation with itself gives you back the same Relation. 

OUTER JOIN

- LEFT OUTER JOIN 
	- takes any tuples on Left Relation, and if doesn't have 
		right matching tuple, it will padd the right side with NULL
- RIGHT OUTER JOIN
The other side operation is just RIGHT OUTER JOIN
Note: Can always do RIGHT side using LEFT but swapping the Relations being compared
- FULL OUTER JOIN =  LEFT OUTER JOIN UNION RIGHT OUTER JOINf
				note: UNION removes duplicates 
To find students who did not applied anywhere, 
-- Begin Code
	SELECT sName, id, cName, major
	FROM Student LEFT OUTER JOIN Apply USING(id); 
-- End Code

Note: Both top and bottom code are equivalent 

-- Begin Code
	SELECT sName, id, cName, major
	FROM Student NATURAL LEFT OUTER JOIN Apply USING(id); 
-- End Code

---------------------------------------------------------------------
-- SQL Functions 
---------------------------------------------------------------------
Aggregation
SUM
AVG
COUNT
MIN
MAX 
To stop duplicates from contributing to aggregation, 
use SELECT DISTINCT 

Aggregation only applied to those in each group
note: If you do not use GROUP BY, then any aggregation will be applied to entire relation (table) as 1 big group. 

GROUP BY .. 

--Given A B C D E, 
--doing 

GROUP BY A, B, C 
--means 
--you can only do 
Select A, B, C -- as attributes by itself 
but you can aggregate anything
Select max(A), min(B), count(C), avg(D), sum(E) 
-- note: doing this below is wrong 
Select D , E 
GROUP BY A, B, C 

-- note: Below is also wrong
SELECT avg(cNum)
FROM Offering, Course
WHere OFfering.dept = Course.dept and Offering.cnum = Course.cnum
GROUP BY Offering.dept 
-- This is wrong because cNum is ambigious, should have done avg(Offering.cnum) OR avg(Course.cnum) instead! 



note: All the rules on Select above with A, B, C, D, E 
also applies to HAVING when you have GROUP BY 

Where => Decides which tuples to keep
Having => Decides which groups to keep 

Count(*) => Return number of records (tuples (rows)) in table , returns number of tuples 
In other words, count(*) counts number of tuples (rows) 

Select(*) => Select all attributes in this relation 
Can use expressions in Select!!
Select SID, grade-10 as adjustedGrade

Select sum(amount) as totalSum, 1 as level -- 1 is a constant in the whole attribute for level 

or concatenate strings in select
Select dept||cnum
From Course; 



CREATE TABLE country (
    code character(3) NOT NULL,
    name text NOT NULL,
    continent text NOT NULL,
    population integer NOT NULL
);

-- Creation and manipulation of tables

CREATE TABLE countrylanguage (
    countrycode character(3) NOT NULL,
    countrylanguage text NOT NULL,
    isofficial boolean,
    percentage real
);

INSERT INTO country(code,name,continent,population) VALUES
('BOR', 'Borduria', 'Pangaea', 1000),
('CAG', 'Cagliostro', 'Pangaea', 250),
('MAR', 'Qumar', 'Pangaea', 3380); 

INSERT INTO countrylanguage(countrycode, countrylanguage) VALUES
('BOR', 'English'),
('BOR', 'Italian'),
('BOR', 'Klingon');

DELETE FROM country
WHERE population < 300;

UPDATE Country
SET continent = 'Luna'
WHERE name = 'Borduria';
CSC343 2013 Test 1 Question 5 
LIKE is basically like bash * thingy where all groups of names are together. 		

create table names(first text, last text, unique (first, last));

CREATE TABLE Invite (
 name TEXT,
 campus TEXT DEFAULT ‘StG’,
 email TEXT,
 age INT);
 -- note: can insert as subquery 
 -- note: Any value not in parentheses when inserting will default to NULL 
INSERT INTO Invite(name, email)
( SELECT firstname, email
 FROM Student
 WHERE cgpa > 3.4 ) ;
 
INSERT INTO «relation» VALUES «list of tuples»;
INSERT INTO «relation» («subquery»);

UPDATE «relation»
 SET «list of attribute assignments»
 WHERE «condition on tuples»;
 
DELETE FROM «relation»
 WHERE «condition»;

 DELETE FROM Course
WHERE NOT EXISTS (
 SELECT *
 FROM Took JOIN Offering
 ON Took.oid = Offering.oid
 WHERE
 grade > 50 AND
 Offering.dept = Course.dept AND
 Offering.cnum = Course.cnum
);

NULLS
note: NULLS may behave different ways in different DBMS
below are behaviour of NULLS for this course? 

Can be created using 
Left Outer Join, Right Outer Join, Full Outer JOin 
- do not contribute to results of aggregation, but if no NON-NULL values in a group, the result of aggregation is NULL 
							-- count(NULL) = 0 (special case) instead of count(NULL) = NULL 
- Can compare an attribute value to NULL using ( IS NULL , IS NOT NULL) 
- keys cannot be NULL! Unique attributes that are not keys can be NULL 
-- e.g. 
SELECT *
 FROM Course
 WHERE breadth IS NULL;
-- Tuple is in query <=> where clause is true (NOT FALSE OR UNKNOWN) 

-- NULLS in setOperations (UNION, INTERSECT, EXCEPT) are considered equal 
-- NULLS with UNIQUE are considered to be different
-- e.g. 
/*
create table names(first text, last text, unique (first, last));
What will the result of the following be?
(a) Doing this twice: insert into names values (’Diane’, ’Horton’);
(b) Doing this twice: insert into names values (null, ’Liu’);
Solution:
csc343h-dianeh=> insert into names values (’Diane’, ’Horton’);
INSERT 0 1
csc343h-dianeh=> insert into names values (’Diane’, ’Horton’);
ERROR: duplicate key value violates unique constraint "names_pkey"
DETAIL: Key (first, last)=(Diane, Horton) already exists.
csc343h-dianeh=> insert into names values (null, ’Liu’);
INSERT 0 1
csc343h-dianeh=> insert into names values (null, ’Liu’);
INSERT 0 1
csc343h-dianeh=> select * from names;
first | last
-------+------
| Liu
| Liu
(2 rows)The unique constraint will not allow two tuples with the same values for first and last. But in this
context, two null values are considered to be different.
*/

Basically, 
If an attribute is defined as unique (BUT not keys), 
each NULL is treated as different unique values. 
However, keys cannot have NULL values. 
Note: For INTERSECT/EXCEPT/UNION (set operations), NULL are treated to be the same values 


-- New truth table
-- True = 1
-- UNKNOWN = 0.5 (UNKNOWN Represents NULL values) 
-- False = 0

AND => MIN of compared
OR => MAX of compared 
NOT => 1 - compared 


Pattern Operators

attribute LIKE pattern
attribute NOT LIKE pattern 
1. If we have something like this:
where name LIKE "_test_"
then only name that has exactly six characters, with the middle four characters = "test" will be in result
2. for the below:
where name LIKE "%test%"
This means as lone as the name includes "test", even if the name is just "test" and has no other character, then the name will be in the result
3. for this one:
where name LIKE "test"
In this case the name has to be exactly "test", no extra character in order to be in the result

'abc' LIKE 'abc'    <i>true</i>
'abc' LIKE 'a%'     <i>true</i>
'abc' LIKE '_b_'    <i>true</i>
'abc' LIKE 'c'      <i>false</i>



SQL uses bag semantics for SELECT-FROM-WHERE queries,
 but set semantics for EXCEPT, UNION, and INTERSECT.
 
In each case, we can override the default.
Override using Select Distinct (Set semantics) 
Override using UNION/INTERSECT/EXCEPT ALL (Bag semantics) 
UNION ALL means count more than once if appear more than once
UNION means count once if only appear once. 

If appear more than once: 
	Set => Only count once
	Bag => Count multiple 


Redefining output 
1.  For renaming at output, if year = 1990 (integer) and u wanna output '1990s' instead, write this 
SELECT movie_id, title, CAST(year AS VARCHAR(4)) || 's' AS decade 
FROM tableName; 

2. To convert 1995 to 1990, 
SELECT ((year/10)*10) AS year, 
FROM Movies; 

From R, S /*<=>*/ From R Cross Join S --(Cross product)
From R Natural Join S -- Natural Join 

Subquery 
-- All subqueries must be in braces () 
-- All subqueries must be an entire query (Select, From, Where) and not just a relation name.
Subquery in FROM need to be outputted as a relation
											-- note: <> => != in SQL 
Subquery in Where need to be outputted as a single value if using , >, < , == , >= , <= , <> , max, sum, count, min, avg (Operators) without ANY, ALL 
					-- can be outputted as many values if using 
					-- (Operators)  ANY, ALL, 
					-- EXISTS,  NOT EXISTS ( EXISTS is true if there is at least 1 tuple, NOT EXISTS is true if there is no tuples in subquery 
					-- as operands to UNION, INTERSECT, EXCEPT 
					-- NOT IN, IN 
					note: If using IN, NOT IN, the comparison must be selected in subquery 
					e.g. 
						SELECT sid, dept||cnum AS course, grade
						FROM Took NATURAL JOIN Offering
						WHERE
						 grade >= 80 AND
						 (cnum, dept) IN ( -- notice how comparison here in braces
						 SELECT cnum, dept -- is the same as the selected here in braces 
						 FROM Took NATURAL JOIN Offering
						 NATURAL JOIN Student
						 WHERE surname = 'Lakemeyer');

(a) Suppose we have these relations: R(a, b) and S(b, c). What does this query do?
SELECT a
FROM R
WHERE b in (SELECT b FROM S);
Solution: It finds a values from R whose b occurs in S.
Note: In this case, it does not produce duplicated values 
(b) Can we express this query without using subqueries?
Solution: You might think this query is equivalent:
SELECT a
FROM R, S
WHERE R.b = S.b; 
(Or we could do a natural join.) But they are not the same in all cases. If a tuple from R connects
successfully with more than one tuple from S, this new query will yield duplicates that the original did
not. Cause it does a cartesian product from R ans S, and in this case, it will produce duplicated values of a
if duplicated values of b exists in S. 
(c) To solve this using cartesian product (From R, S) use select distinct instead 
Create View Sb As
Select Distinct b 
From S; 
Select a
From R, Sb 
Where R.b = S.b; 
note: This produces same output as (a) method above. 


						 
Relational Algebra 
Max/Min; 
1. Pair all non max
2. Max = Ori - paired

>= k; 

exactly k;
1.  (>= k) -  (>= k+1) 

at most k; 
1. All - (>= k+1) 
every; 
- make all combos that should have occured
- subtract those that did occurto get failure
- subtract failure form should have occured 

