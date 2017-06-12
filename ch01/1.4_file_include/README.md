Chapter 1: INTRDUCTION
----------------------

#### 1.4

C allows statements of the form
```c
#include filename
```
which reads filename and inserts its contents in place of the include statement.
Include statements may be nested; inother words, the file filename may itself contain an include statement, but, obviously, a file can't include itself in anychain.
Write a program that reads in a file and outputs the file as modified by the include statements.
