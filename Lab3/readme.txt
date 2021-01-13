*******************************************************
*  Name      :  Ivy Truong        
*  Student ID:  108972556               
*  Class     :  CSCI 3453           
*  Due Date  :  December 7, 2020
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

The program simulates 3 page replacement algorithms (FIFO, 
LRU, and optimal) for a file with 10000 page references.This
program will test all the algorithms given the frame size 
the user inputs to the program. The before the program runs,
the user has to input 3 arguments when calling the program:
the frame size, the input file, and an output file. The program
will print to the output file the frame size inputted by the 
user, and these statistics for each of the page replacement
algorithms: total number of page faults and the page fault
rates after 2000, 4000, 6000, 8000, and 10000 page references.

*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   This is the main program. This program will obtain the inputs from
the user to call the functions in functions.hpp to read the file and
call each of the page replacement algorithms. The main program will take
the results from each algorithm and store those results into the output
file that the user inputted. 

Name:  Node.hpp
   Contains the definition of the Node used to hold a doubly linked list. 

Name: list.hpp
   Defines and implements the list class for implementing a doubly linked 
list. This class can push an element to the list, remove an element from the
front of the list, remove an element in the middle of the list, check if an
element exists in the list, check if the list is empty, return the size of the
list, and has a special function used in the optimal page replacement algorithm
that will figure out the latest future reference of the page that is in the list.

Name: functions.hpp
   Contains the functions that will read the input file and simulate the
page replacement algorithms (FIFO, LRU, and optimal).

   
*******************************************************
*  Status of program
*******************************************************

   The program runs successfully.  

   The sample output for these programs are labelled output(Frame Size).txt.
For example, the results of the algorithm using a frame size of 128 would have
an output file name of output128.txt.
   
   The program was developed and tested on Visual Studios Code g++.  It was 
   compiled, run, and tested on csegrid.ucdenver.pvt.

