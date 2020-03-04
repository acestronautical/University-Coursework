# Ace Cassidy-HW2-CPTS451-Spring'20

## A

### Q1

```SQL
SELECT distinct course.courseno, course.coursemajor, credits
FROM Student, Course, Enroll
WHERE studentmajor='CptS' AND trackcode='SE'
ORDER BY course.courseno, course.coursemajor
;
```
