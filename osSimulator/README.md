# OS-Term-Project

By: Grace O'Leary

Design and implement a program that simulates the job scheduling, CPU scheduling, and deadlock avoidance of an operating system.

## Directions to build and run this program:

To BUILD: 

In the osSimulator directory:   g++ -g *.cpp -o build/osSimulator.out"

To RUN:

build/osSimulator.out input.txt

## Inputs - input.txt file

**i0: 

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


**i1: 

C 1 M=200 S=12 Q=4
A 2 J=1 M=20 S=5 R=10 P=1
A 3 J=2 M=30 S=7 R=10 P=2
D 4
D 5
Q 6 J=2 D=5
D 7
D 8
D 9999


**i2:

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
**Note that actual outputs do not match expected, see report for full output

**O0: 

At Time: 9999

Available Main Memory: 130

Current Devices: 16

Process running on CPU: Job ID = -1, Waiting Time = 2, Time left = 26

Completed Jobs:
Job ID = 3, Arrival Time = 17, Finish Time = 18, Turnaround Time = 1
Job ID = 6, Arrival Time = 23, Finish Time = 24, Turnaround Time = 1
Job ID = 4, Arrival Time = 25, Finish Time = 26, Turnaround Time = 1

System Turnaround Time: 1


**O1:

At Time: 9999

Available Main Memory: 170

Current Devices: 12

Process running on CPU: Job ID = -1, Waiting Time = 3, Time left = 18

Completed Jobs:
Job ID = 3, Arrival Time = 17, Finish Time = 18, Turnaround Time = 1

System Turnaround Time: 1


**O2:

At Time: 9999

Available Main Memory: 170

Current Devices: 23

Process running on CPU: Job ID = -1, Waiting Time = 2, Time left = 26

Completed Jobs: 
Job ID = 3, Arrival Time = 17, Finish Time = 18, Turnaround Time = 1
Job ID = 1, Arrival Time = 21, Finish Time = 22, Turnaround Time = 1
Job ID = 4, Arrival Time = 25, Finish Time = 26, Turnaround Time = 1

System Turnaround Time: 1





