# OVERVIEW

This is a C programme to manage database of up to 100 students, with support for creating, editing, deleting, searching and generating class statistic. Data is persisted in text format file (students.dat).

## RUNNING INSTRUCTiON(MAKEFILE)
Before using the makefile function 
do ensure you have already installed Makefile Tools in the VSC extentsion
In the Makefile Tab, in "Make: " settings
under makefile: Make Path
copy and paste this:
```C:\msys64\usr\bin\make.exe```

under makefile: Makefile Path
it should already have this:
```makefile```

if it dont, find it in ```..\studentmanagement\makefile``` if you didnt change anything when downloaded.

After all these settings
1. In the configurations: set it to [Default]
2. In the Build target: set it to [all]
3. Press the bubble tea button and it should compile
something like
```gcc -Wall -Wextra -g -std=c11 -c main.c -o main.o```
```gcc -Wall -Wextra -g -std=c11 -c fileDat.c -o fileDat.o```
```gcc -Wall -Wextra -g -std=c11 -c crud.c -o crud.o```
```gcc -Wall -Wextra -g -std=c11 -c menu.c -o menu.o```
```gcc -Wall -Wextra -g -std=c11 -c statistics.c -o statistics.o```
```gcc -Wall -Wextra -g -std=c11 -c validation.c -o validation.o```
```gcc -Wall -Wextra -g -std=c11 -o student main.o fileDat.o crud.o menu.o statistics.o validation.o```
will show

It should be successful, and you will see students.exe in the folder.
Now in the terminal, enter this to run the exe
```./student.exe```

## RUNNING INSTRUCTiON(terminal)
In the Visual Code Studio terminal
To compile:
```gcc -o student.exe main.c fileDat.c crud.c menu.c statistics.c validation.c```

To run exe:
```./student exe```

## Example Output
idk ah maybe this
=========================================================
ID       First Name   Last Name   GPA   Enrollment Date
=========================================================
1001     Tan          Ah Kau        3.50  2023-01-15
1002     Dogulas      Ong           2.80  2023-02-12
1003     Clara        Lee           3.90  2023-03-05
=========================================================

# student-system
