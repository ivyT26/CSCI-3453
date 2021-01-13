*******************************************************
*  Name      :  Ivy Truong        
*  Student ID:  108972556               
*  Class     :  CSCI 3453           
*  Due Date  :  Nov. 4, 2020
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

The program will read in a file that contains information about 
n processes. The file will have the process ID, the arrival time,
CPU burst time, and priority level. The main purpose of this 
program is to execute the processes that follow a specfic
CPU scheduling algorithm (FCFS, SJF, PP or RR).


*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program. Before running the program the user must input 3 arguments:
program name, file name, and scheduling algorithm (1 = FCFS, 2 = SJF, 3 = PP, 4 = RR). 
For RR, 4 arguments need to be inputted, where the last argument is the time quantum.
If you want to use the menu option, the programmer can uncomment the code in main.
The menu option will maintain the user interface/main menu of the program that 
will read in the user's input for the file name and the user's option for the 
CPU scheduling algorithm. Menu has checking implementation for choosing option.

Name:  functions.hpp
   Defines and contains the functions that reads in the file, controls the process
of the different CPU scheduling algorithms, and functions that print
out the desired results. The CPU scheduling algorithms are FCFS, SJF, PP,
and RR. If the user chooses RR, they will have to input a set time quantum
before the algorithm can run.

Name: PCB.hpp
   Defines the PCB structure that will hold the information about the 
processes. Information that the structure holds are the process ID, 
arrival time, priority level, CPU burst time, turnaround time, wait time, 
response time, total number of context switches, leave time, and the
amount of time the process has completed (used while the program runs the 
algorithm). This file also defines the structure of the Node which will be 
implemented in the queue class. 

Name: queue.hpp
   Contains the functionality of the queue class. This class has two private
variables Node* head and int size, where the head is where the queue is stored and
the size notes the size of the queue. The queue structure is simulated using a linked 
list implementation. Functions used within the class are push (push process to the end
of the queue), pop (removes the processes at the beginning of the queue), isEmpty 
(checks if the queue is empty), sizeOfQueue (returns the length of the queue), and
sortQueue (sorts the queue by PID). 
   
   
*******************************************************
*  Status of program
*******************************************************

   The program runs successfully.  
   
   The program was developed and tested on Visual Studios Code g++.  It was 
   compiled, run, and tested on csegrid.ucdenver.pvt.

