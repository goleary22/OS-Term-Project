# OS-Term-Project
Design and implement a program that simulates the job scheduling, CPU scheduling, and deadlock avoidance of an operating system.

## Directions to build and run this program:

To BUILD: 

In the osSimulator directory:   g++ -g *.cpp -o build/osSimulator.out"

To RUN:

build/osSimulator.out input.txt

## Inputs - input.txt file

i0: 
C 1 M=200 S=12 Q=4
A 3 J=1 M=20 S=5 R=10 P=1
A 4 J=2 M=30 S=2 R=12 P=2
A 9 J=3 M=10 S=8 R=4 P=1
Q 12 J=1 D=5
A 13 J=4 M=20 S=4 R=11 P=2
Q 14 J=3 D=2
A 24 J=5 M=20 S=10 R=9 P=1
A 25 J=6 M=20 S=4 R=12 P=2
D 9999


i1: 
C 1 M=200 S=12 Q=4
A 2 J=1 M=20 S=5 R=10 P=1
A 3 J=2 M=30 S=7 R=10 P=2
D 4
D 5
Q 6 J=2 D=5
D 7
D 8
D 9999


i2:
C 1 M=200 S=12 Q=4
A 3 J=1 M=20 S=5 R=10 P=1
A 4 J=2 M=30 S=8 R=12 P=2
A 9 J=3 M=10 S=2 R=4 P=1
Q 12 J=1 D=5
A 13 J=4 M=20 S=11 R=11 P=2
Q 14 J=3 D=2
Q 25 J=4 D=11
L 26 J=3 D=2
D 9999


## Output:
**Note that actual outputs do not match expected

O0: 
At Time: 9999
Available Main Memory: 130
Current Devices: 16
Process running on CPU:
Job ID  Waiting Time    Time Left
------- ------------    ---------
-1      2               26
Hold Queue 1:
Job ID  Run Time
------  --------

Hold Queue 2:
Job ID  Run Time
------  --------

Ready Queue:
Job ID  Run Time        Waiting Time
------- --------        -------------
Wait Queue:
Job ID  Run Time        Waiting Time
------  ---------       ------------
Completed Jobs:
Job ID  Arrival Time    Finish Time     Turnaround Time
------- ------------    -----------     ---------------
3       17              18              1
6       23              24              1
4       25              26              1
System Turnaround Time: 1


O1:
At Time: 9999
Available Main Memory: 170
Current Devices: 12
Process running on CPU:
Job ID  Waiting Time    Time Left
------- ------------    ---------
-1      3               18
Hold Queue 1:
Job ID  Run Time
------  --------

Hold Queue 2:
Job ID  Run Time
------  --------

Ready Queue:
Job ID  Run Time        Waiting Time
------- --------        -------------
Wait Queue:
Job ID  Run Time        Waiting Time
------  ---------       ------------
Completed Jobs:
Job ID  Arrival Time    Finish Time     Turnaround Time
------- ------------    -----------     ---------------
1       17              18              1
System Turnaround Time: 1


O2:
At Time: 9999
Available Main Memory: 170
Current Devices: 23
Process running on CPU:
Job ID  Waiting Time    Time Left
------- ------------    ---------
-1      2               26
Hold Queue 1:
Job ID  Run Time
------  --------

Hold Queue 2:
Job ID  Run Time
------  --------

Ready Queue:
Job ID  Run Time        Waiting Time
------- --------        -------------
Wait Queue:
Job ID  Run Time        Waiting Time
------  ---------       ------------
Completed Jobs:
Job ID  Arrival Time    Finish Time     Turnaround Time
------- ------------    -----------     ---------------
3       17              18              1
1       21              22              1
4       25              26              1
System Turnaround Time: 1





