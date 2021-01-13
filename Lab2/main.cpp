#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "functions.hpp"
using namespace std;

//To Dos: make working queue
    //implement FCFS, SJF, PP, and RR (q = 4, 16, 64)
    //display results in nice Ganett Chart

int main(int argc, char *argv[]) {
    //if programmer wants to usemenu option, comment out arguments in main
    //source: https://stackoverflow.com/questions/2797813/how-to-convert-a-command-line-argument-to-int

    //cout << "Number of arguments: " << argc << endl;
    // for (int k = 0; k < argc; ++k) {
    //     cout << argv[k] << endl;
    // }

    int userNum, userQuant;

    //grabs input for algorithm option, comment out if using menu
    //(1 = FCFS, 2 = SJF, 3 = PP, 4 = RR)
    if (argc >= 3) {
        char *val1;
        long convNum = strtol(argv[2], &val1, 10);

        userNum = convNum;
        cout << "Option chosen: " << userNum << endl; 

        if (userNum == 4 && argc < 4) {
            cout << "Not enough arguments in order to run RR.\n";
            return 0;
        }
    }

    //grabs input for time quantum if the scheduling algorithm is RR, comment out if using menu
    if (argc == 4) {
        char *val;
        long convChar = strtol(argv[3], &val, 10);

        userQuant = convChar;
        cout << "Time quantum: " << userQuant << endl;
    }

    string fileName;
    int userInput;
    ifstream infile;
    PCB readProcess[200];
    int numProcesses;
    bool check = false;

    //check arguments, comment out if you want to use menu
    infile.open(argv[1]);
    if (!infile) {
        cout << "Cannot open file.\n";
        return 0;
    }

    if (userNum < 1 || userNum > 4) {
        cout << "Invalid input.\n";
        return 0;
    }

    //menu to choose which algorithm to run, uncomment to use
    // cout << "Welcome to the CPU scheduling system!\n";
    // cout << "Type in a file to read.\n";
    // getline(cin, fileName);
    // infile.open(fileName);
    // if (!infile) {
    //     cout << "Cannot open file.\n";
    //     return 0;
    // }
    numProcesses = readFile(infile, readProcess);

    //uncomment this part if you want to use menu
    // while (check == false) {
    //     cout << "CPU algorithms: \n";
    //     cout << "1. FCFS\n2. SJF\n3. PP\n4. RR\n5. Exit System\n";
    //     cout << "Choose a scheduling algorithm to run.\n";
    //     cin >> userInput;
    //     if (cin.fail()) {
    //         cout << "Not an integer input.\n";
    //         cin.clear();
    //         cin.ignore();
    //     }
    //     else {
    //         check = checkMenu(userInput);
    //     }
    // }

    if (userNum == 1) {
        //FCFS algorithm
        cout << "FCFS algorithm running...\n";
        FCFS(readProcess, numProcesses);
    }
    else if (userNum == 2) {
        //SJF algorithm
        cout << "SJF algorithm running...\n";
        SJF(readProcess, numProcesses);
    } 
    else if (userNum == 3) {
        //PP algorithm
        cout << "PP algorithm running...\n";
        PP(readProcess, numProcesses);
    }
    else if (userNum == 4) {
        //RR algorithm
        int quantum;
        // cout << "Type in a time quantum size.\n";
        // cin >> quantum;
        cout << "RR algorithm running...\n";
        RR(readProcess, numProcesses, userQuant);
    }
    return 0;
}