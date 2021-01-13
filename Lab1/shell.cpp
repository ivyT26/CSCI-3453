#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;

bool checkInput(int service);

//sources
//https://www.cyberciti.biz/faq/unix-linux-shell-find-out-posixcommand-exists-or-not/
//https://www.man7.org/linux/man-pages/man3/exec.3.html
//https://www.geeksforgeeks.org/difference-fork-exec/
//https://www.geeksforgeeks.org/dup-dup2-linux-system-call/
//https://www.youtube.com/watch?v=EqndHT606Tw

int main() {
    int pid;
	int service;
	bool check;
	string command;
	string path_file;
	char* args[100] = {NULL};
	int fd, oldfd; //file descriptor for file the user wants to direct output/input
	
	do {
		do {
			cout << "Welcome to myshell!\n";
			cout << "Choose your service.\n";
			cout << "1.Command with no arguments\n2.Command with arguments\n3.Put output to a file\n";
			cout << "4.Get input from a file\n5.Exit Shell\n";
			cin >> service;
			
			check = checkInput(service);
			if (check == true) {
				cin.clear();
				cin.ignore();
			}
		} while (check == true);
		
		//cout << "Parent process\n";
		// chdir(".."); //need to implement this if the user command has cd
		// system("pwd");
		// system("ls");
		
		if (service != 5) {
			cout << "Type in a command you want to run.\n";
			cin.ignore();
			getline(cin, command);
			cout << "Inputted command: " << command << endl;	
		}
		else {
			continue;
		}
		
		//parsing command
		int count = 0;
		//if it is service 3 or 4, add these arguments
		//used so that the '<' and '>' operators are treated as operations than arguments
		// if (service == 3 or service == 4) {
			// args[count] = "sh";
			// count++;
			// args[count] = "-c";
			// count++;
		// }
		
		stringstream newStr(command);
		string temp;
		newStr >> temp;
		args[count] = (char*)temp.c_str();
		cout << temp << endl;
		
		//execute cd command immediately in parent process so change is reflected
		if (temp == "cd") {
			newStr >> path_file;
			chdir(path_file.c_str());
			system("pwd");
			continue;
		}
		
		int filePos = -1; //keeps track of where the file is while parsing command
		while(newStr >> path_file) {
			if (path_file == ">") {
				newStr >> path_file;
				cout << path_file << endl;
				//O_RDWR means read or write to file
				//O_CREAT means create the file if it doesn't exist
				fd = open(path_file.c_str(), O_RDWR | O_CREAT);
			}
			else {
				++count;
				cout << count << endl;
				cout << path_file << endl;
				args[count] = (char*)path_file.c_str();
			}
		}
		
		//string greater = ">";
		//string less = "<";
		//error checking for commands with multiple arguments (options 2, 3, 4)
		// if (service >= 2 and service <= 4) {
			// if (count == 0) {
				// cout << "Not enough arguments to execute command\n";
				// break;
			// }
		// }
		
		//parse command, check if it exists (using execlp())
			//if it is cd, then execute it in the parent process using chdir()
			//error checking may be difficult, exec() cannot execute type -P command or whereis command
		//do type -P command to get path of command if it exists
		//certain commands like cd are shell builtin, so they won't have a path
		pid = fork();
		
		if (pid < 0) {
			cout << "Fork failed.\n";
		}
		else if (pid == 0) {
			// if (service == 1)  {
				// error = execlp(temp.c_str(), temp.c_str(), NULL);
			// }
			// else if (service == 5) {
				// cout << "Exiting shell...\n";
			// }
			// else {
				// error = execlp(temp.c_str(), temp.c_str(), args, NULL);
				// cout << error << endl;
			// }
			//execlp("/bin/sh","cd","..",NULL);
			//cout << "error\n";
			//chdir("..");
			//execlp("/bin/pwd","pwd",NULL);
			//execlp("/bin/whereis", "whereis", "-b", command.c_str(), NULL);
			// if (execvp(args.at(0), args) < 0) {
				// cout << "Cannot execute command\n";
			// }
			
			
			if (service == 3) {
				//commented lines were used to test how to execute commands redirecting file to output
					//parsing command above does not work (which is weird bc the parsing worked for option 2 
					//but not option 3)
				//char* newList[10] = {"\0"};
				//newList[0] = (char*)temp.c_str();
				//newList[1] = (char*)"-l";
				oldfd = dup(1); //save STDOUT file descriptor
				dup2(fd, 1); //replaces file descriptor with temporary file to redirect output
				execvp(args[0], args); //execute command like in option 1 or 2
			}
			else if (service == 4) { //code does same thing but in reverse to take input from file
				oldfd = dup(0);
				dup2(fd, 0);
				execvp(args[0], args);
			}
			else if (execvp(args[0], args) < 0){ //executes any command under option 1 or 2 and prints out error message if command does not work
				cout << "Cannot execute command\n";
			}
			//cout << "Child process.\n";
			exit(0);
		}
		else {
			wait(NULL);
			/*if (service == 3 or service == 4){
				//resets file descriptors
				dup2(STDOUT,1);
				dup2(STDIN, 0);
			}*/
			//resetting argument array
			for (int i = 0; i < 100; ++i) {
				args[i] = NULL;
			}
			cout << "Child complete.\n";
		}
	} while (service != 5);

	
    return 0;
}

bool checkInput(int service) {
	if (service >= 1 && service <= 5) {
		return false;
	}
	cout << "Wrong input, please try again.\n";
	return true;
}
