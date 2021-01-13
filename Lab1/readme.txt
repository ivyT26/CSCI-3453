*******************************************************
*  Name      :  Ivy Truong         
*  Student ID:  108972556               
*  Class     :  CSCI 3453          
*  Due Date  :  October 7, 2020
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

The program creates a shell called myshell that can execute
4 different types of commands. The goal of this program is to
execute the user inputted commands using fork() and exec() 
system calls. 

*******************************************************
*  Source files
*******************************************************

Name:  shell.cpp
   Main program.  This is the driver program that creates a shell
for the user to use in order to execute shell commands. The
user will be able to execute 4 different types of commands: 
commands with no arguments such as ls, commands with arguments such as
ls -l, commands that redirect the output to a file, and commands that
take an input from a file and execute a command using the input.
This program will parse through the user command for error checking
and putting it in a variable of the matching type in order to 
run the exec() system calls. To execute the commands, the program will
fork the main process and execute the command given the main command
and arguments if the command has any. The execvp() commmand is used to 
execute all types of commands except the cd command. The cd command is 
executed in the parent process using chdir() so that the change is reflected
in the parent process if the user wanted to execute other commands not in
the main directory of the program running.
   
   
*******************************************************
*  Status of program
*******************************************************

   The program partially runs.

   The parts that run successfully are options 1, 2, and 5. The program
is able to execute commands with no arguments, commands with arguments,
and exit the shell sucessfully. The program is able to execute any commands
that follow under options 3 and 4 partially due to the fact that exec() will 
read the redirection synbols ('<' and '>') as files. The dup() and dup2() commands
were used to execute those commands correctly. Commands with arguments using option
3 (such as ls -fx > file.txt) will not work. Commands under option 4 will work, but 
fall into an infinite loop sometimes. 
   
   The program was developed and tested on Ubuntu environment and Notepad++.  
   It was compiled, run, and tested on Ubuntu environment and csegrid.ucdenver.pvt.

