#include <iostream>
#include <fstream>
#include <iomanip> //used to format a nice output table
#include "queue.hpp"
using namespace std;

//function prototypes
int readFile(ifstream &infile, PCB array[]);
bool checkMenu(int input);
void calcAvg(queue done);
void printStats(queue done);
void FCFS(PCB array[], int numProcess);
void SJF(PCB array[], int numProcess);
void PP(PCB array[], int numProcess);
void RR(PCB array[], int numProcess, int quantum);

//function to read file
int readFile(ifstream &infile, PCB array[]) {
    //file contains 4 values in each line (process ID, arrival time, CPU burst time, and priority (0-99))
    int ID, arrival, burst, priority;
    PCB temp;
    int size = 0;

    //initialize all other variables
    temp.completed = 0; 
    temp.numSwitches = 0;
    temp.leave = 0;
    temp.response = -1;
    temp.turnaround = 0;
    temp.wait = 0;

    while (infile >> ID) {
        infile.ignore();
        infile >> arrival;
        infile.ignore();
        infile >> burst;
        infile.ignore();
        infile >> priority;
        infile.ignore();
        temp.ID = ID;
        temp.arrived = arrival;
        temp.burstTime = burst;
        temp.priority = priority;
        //cout << temp.ID << endl;
        //cout << temp.burstTime << endl;
        array[size] = temp;
        ++size;
        //cout << size << endl;
    }

    return size;
}

//check if userInput was valid
bool checkMenu(int input) {
    if (input > 0 && input <= 5) {
        return true;
    }
    cout << "Invalid input.\n";
    return false;
}

//calculates averages of stats
void calcAvg(queue done) {
    float avgRes = 0, avgBurst = 0, avgWait = 0, avgTurn = 0, totalSwitches = 0;
    int size = done.sizeOfQueue();
    PCB current;
    for (int i = 0; i < size; ++i) {
        current = done.pop();
        avgRes += current.response;
        avgBurst += current.burstTime;
        avgWait += current.wait;
        avgTurn += current.turnaround;
        totalSwitches += current.numSwitches;
    }
    avgRes /= size;
    avgBurst /= size;
    avgWait /= size;
    avgTurn /= size;

    cout << "Average CPU burst time: " << avgBurst << " ms\n";
    cout << "Average response time: " << avgRes << " ms\n";
    cout << "Average wait time: " << avgWait << " ms\n";
    cout << "Average turnaround time: " << avgTurn << " ms\n";
    cout << "Total number of context switches: " << totalSwitches << endl;
}

//prints finished array and all stats of each process
void printStats(queue done) {
    PCB printProc;
    //print headers
    cout << setw(4) << "PID" << setw(4) << " | Arrival" << setw(3) << " | CPU Burst" << setw(3) << " | Priority" << setw(3) << " | Finished" << 
    setw(3) << " | Response(ms)" << setw(3) << " | Waiting(ms)" << setw(3) << " | TurnAround(ms)" << setw(3) << " | Context Switches \n";
    for (int i = 0; i < done.sizeOfQueue(); ++i) {
        printProc = done.pop();
        cout << setw(3) << printProc.ID << setw(3) << "|" << setw(5) << printProc.arrived << setw(5) << "|" << setw(6) << printProc.burstTime <<
        setw(6) << "|" << setw(5) << printProc.priority << setw(6) << "|" << setw(5) << printProc.leave << setw(6) << "|" << setw(7) << printProc.response << 
        setw(8) << "|" << setw(7) << printProc.wait << setw(7) << "|" << setw(9) << printProc.turnaround << setw(8) << "|" << setw(8) << printProc.numSwitches << endl;
        done.push(printProc);
    }
    calcAvg(done);
}

//function to apply FCFS algorithm
void FCFS (PCB array[], int numProcess) {
    float time = 0; //current time of scheduling system
    queue readyFCFS; //inserts processes in queue when they come in
    //PCB finished[200]; //inserts processes that are finished (will be used to print out results)
    //int finishSize = 0;
    queue finished;
    int checkProcess = 0; //checks the process in the array if it is entering the system
    PCB arrivedProcess;
    PCB runProcess;
    runProcess.ID = -1; //to note that the runProcess is empty/CPU is idle

    while (finished.sizeOfQueue() != numProcess) { //finished.sizeOfQueue() != numProcess
        cout << "Current time: " << time << endl;

        //check if the next process is entering 
        arrivedProcess = array[checkProcess];
        if (checkProcess != numProcess && arrivedProcess.arrived == time) {
            readyFCFS.push(arrivedProcess);
            ++checkProcess;
            cout << "Process arriving: " << arrivedProcess.ID << endl;
        }

        //check if the ready queue is empty or a process is ready to use the CPU
        if (runProcess.ID == -1) {
            if(!readyFCFS.isEmpty()) {
                runProcess = readyFCFS.pop();
                runProcess.response = time - runProcess.arrived;
            }
            else {
                cout << "CPU idle...\n";
                ++time;
                continue;
            }
        }

        //run process
        cout << "Process running: " << runProcess.ID << endl;
        runProcess.completed += 1;
        ++time;
        //bool complete = runProcess.completed == runProcess.burstTime;
        //cout << complete << endl;
        //cout << runProcess.completed << endl;
        if (runProcess.completed == runProcess.burstTime) {
            runProcess.leave = time;
            cout << "Leave time: " << time << endl;
            runProcess.wait = runProcess.wait + runProcess.response;
            //cout << "Wait time: " << runProcess.wait << endl;
            runProcess.turnaround = runProcess.wait + runProcess.burstTime;
            //cout << "Total time spent: " << runProcess.turnaround << endl;
            //finished[finishSize] = runProcess;
            //finishSize += 1;
            finished.push(runProcess);
            runProcess.ID = -1;
        }
    }

    //print results of FCFS algorithm
    cout << "*****************************************\n";
    cout << "*******FCFS Stats for each process*******\n";
    cout << "*****************************************\n";
    printStats(finished);
}

//function to apply SJF algorithm
void SJF(PCB array[], int numProcess) {
    float time1 = 0; //current time of the scheduler
    queue readySJF; //keeps ready processes in queue
    queue finishedSJF; //keeps track of which processes are finished
    int check = 0; //checks the current process coming in next
    PCB running; //keeps track of the current running process/process using CPU
    running.ID = -1;
    //PCB done[1000];
    //int actualSize = 0; //how many processes are stored in done array
    PCB arrived; //checks the arrived process if it is ready to be put into ready queue

    while (finishedSJF.sizeOfQueue() != numProcess) {
        cout << "Current time: " << time1 << endl;

        //checks for incoming processes
        arrived = array[check];
        if (check != numProcess && arrived.arrived == time1) {
            cout << "Process entering: " << arrived.ID << endl;
            readySJF.push(arrived);
            ++check;
        }

        //checks for if there are no running processes, find the process in ready queue with the shortest burst time
        if (running.ID == -1) {
            if (readySJF.isEmpty()) {
                cout << "CPU idle...\n";
                ++time1;
                continue;
            }
            else { 
                cout << "Finding process...\n";
                //finds the process with the shortest CPU burst time in ready queue
                PCB currentProc, temp;
                running.burstTime = 1000;
                int size = readySJF.sizeOfQueue();
                for (int i = 0; i < size; ++i) {
                    currentProc = readySJF.pop();
                    if (currentProc.burstTime < running.burstTime) {
                        temp = running;
                        running = currentProc;
                        currentProc = temp;
                        if (currentProc.ID != -1) {
                            readySJF.push(currentProc);
                        }
                    }
                    else {
                        readySJF.push(currentProc);
                    }
                }
                //calculate response time here
                running.response = time1 - running.arrived;
            }
        }

        cout << "Current process running: " << running.ID << endl;
        running.completed += 1;
        ++time1;

        //check if the current running process is finished
        if (running.completed == running.burstTime) {
            cout << "Left: " << time1 << endl;
            running.leave = time1;
            running.wait += running.response;
            running.turnaround = running.wait + running.burstTime;
            finishedSJF.sortQueue(running);
            running.ID = -1;
        }

    }

    //print results of SJF algorithm
    cout << "******************************************\n";
    cout << "********SJF Stats for each process********\n";
    cout << "******************************************\n";
    printStats(finishedSJF);
}

//function to apply PP algorithm
void PP(PCB array[], int numProcess) {
    float time2 = 0;
    queue readyPP;
    queue finishedPP;
    PCB incoming, run;
    int check = 0;
    run.ID = -1;
    bool cSwitch = false; //if a context switch occurs skip running in CPU

    while (finishedPP.sizeOfQueue() != numProcess) {
        cSwitch = false;
        cout << "Current time: " << time2 << endl;

        //checks for incoming processes
        incoming = array[check];
        if (check != numProcess && incoming.arrived == time2) {
            cout << "Process entering: " << incoming.ID << endl;
            //checks priority of incoming process and makes sure the process with the highest priority is running
            if (run.ID != -1 && incoming.priority < run.priority) {
                //include context switch times here since incoming and running processes have to swap
                cout << "Context switch, CPU is idle for 0.5 ms.\n";
                time2 += 0.5; //this is when the CPU is idle
                //cout << "Current time: " << time2 << endl;
                incoming.response = time2 - incoming.arrived;
                run.numSwitches += 1;
                PCB temp;
                temp = run;
                run = incoming;
                incoming = temp;
                cSwitch = true;
                //cout << "Current time: " << time2 << endl;
            }
            readyPP.push(incoming);
            ++check;
        }

        //checks if there are no currently running processes but the queue is not empty
        if (run.ID == -1) {
            if (readyPP.isEmpty()) {
                cout << "CPU idle...\n";
                time2 += 0.5;
                continue;
            }
            else {
                cout << "Finding process...\n";
                //find process with highest priority in queue
                PCB currProc, temp;
                run.priority = 100; //default, range of priority is 0-99
                int size = readyPP.sizeOfQueue();
                for (int i = 0; i < size; ++i) {
                    currProc = readyPP.pop();
                    if (currProc.priority < run.priority) {
                        temp = run;
                        run = currProc;
                        currProc = temp;
                        if (currProc.ID != -1) {
                            readyPP.push(currProc);
                        }
                    }
                    else {
                        readyPP.push(currProc);
                    }
                }
                //calculate response time for processes that were not preempted
                if (run.response == -1) {
                    run.response = time2 - run.arrived;
                }
            }
        }

        //calculates wait time for processes that were preempted (this will include context switch time too)
        PCB waitProc;
        int size1 = readyPP.sizeOfQueue();
        for (int j = 0; j < size1; ++j) {
            waitProc = readyPP.pop();
            if (waitProc.response >= 0) {
                waitProc.wait += 0.5;
            }
            readyPP.push(waitProc);
        }

        if (cSwitch == true) {
            continue; //continue to next iteration in while loop
        }

        //check if currently running process is done
        cout << "Current process running: " << run.ID << endl;
        run.completed += 0.5;
        time2 += 0.5;

        if (run.completed == run.burstTime) {
            cout << "Left: " << time2 << endl;
            run.leave = time2;
            run.wait += run.response;
            run.turnaround = run.wait + run.burstTime;
            finishedPP.sortQueue(run);
            run.ID = -1;
        }
    }

    //print out results
    cout << "***************************************\n";
    cout << "*******PP Stats for each process*******\n";
    cout << "***************************************\n";
    printStats(finishedPP);
}

//function to apply RR algorithm
void RR(PCB array[], int numProcess, int quantum) {
    float time3 = 0;
    queue readyRR;
    queue finishedRR;
    PCB next, runNow;
    int check = 0;
    runNow.ID = -1;
    float limit = 0; //variable used to keep track of how long the process has used the CPU and does not exceed time quantum
    bool swapProc = false;

    while (finishedRR.sizeOfQueue() != numProcess) {
        //preliminary check for processes that come after a context switch or if it is the first process
        if (check == 0 || swapProc == true) {
            cout << "Current time: " << time3 << endl;
            next = array[check];
            if (check != numProcess && next.arrived == time3) {
                readyRR.push(next);
                ++check;
                cout << "Process arriving: " << next.ID << endl;
            }
            swapProc = false;
        }

        //checks if there are any processes running, pops next process in ready queue if there is no running process
        if (runNow.ID == -1) {
            if (readyRR.isEmpty()) {
                cout << "CPU idle...\n";
                time3 += 0.5;
                continue;
            }
            else {
                runNow = readyRR.pop();
                if (runNow.response < 0) {
                    runNow.response = time3 - runNow.arrived;
                }
            }
        }

        //calculate wait time for processes that have been preempted
        PCB waiting;
        int size2 = readyRR.sizeOfQueue();
        for (int j = 0; j < size2; ++j) {
            waiting = readyRR.pop();
            if (waiting.response >= 0) {
                waiting.wait += 0.5;
            }
            readyRR.push(waiting);
        }

        //calculate running process
        cout << "Current running process: " << runNow.ID << endl;
        runNow.completed += 0.5;
        limit += 0.5;
        time3 += 0.5;

        cout << "Current time: " << time3 << endl;

        //check if a process comes at the same time as when the current running process is preempted, push the incoming process first
            //before pushing current running process into queue
        next = array[check];
        if (next.arrived == time3) {
            readyRR.push(next);
            ++check;
            cout << "Process arriving: " << next.ID << endl;
        }

        if (runNow.completed == runNow.burstTime) {
            cout << "Left: " << time3 << endl; 
            runNow.leave = time3;
            runNow.wait += runNow.response;
            runNow.turnaround = runNow.wait + runNow.burstTime;
            finishedRR.sortQueue(runNow);
            runNow.ID = -1;
            limit = 0; //reset limit in CPU usage for next process
        }
        else if (limit == quantum) {
            if (readyRR.isEmpty()) { //if there are no processes in ready queue, the current running process can continue
                limit = 0;
                continue;
            }
            else {
                cout << "Context switch in progress, CPU idle for 0.5 ms\n";
                runNow.numSwitches += 1;
                readyRR.push(runNow);
                //calculate context switch waiting time for all processes in ready queue
                int size3 = readyRR.sizeOfQueue();
                for (int j = 0; j < size3; ++j) {
                    waiting = readyRR.pop();
                    if (waiting.response >= 0) {
                        waiting.wait += 0.5;
                    }
                    readyRR.push(waiting);
                }
                runNow = readyRR.pop();
                time3 += 0.5; //increment time to accomodate for context switch
                swapProc = true;
                //cout << "Current time: " << time3 << endl; //need to fix*** to accomodate for processes that come in after context switch
                limit = 0; //reset limit for new process using CPU
                //calculate response time if process's first time using CPU
                if (runNow.response < 0) {
                    runNow.response = time3 - runNow.arrived;
                }
            }
        }
    }

    //print out results 
    cout << "***************************************\n";
    cout << "*******RR Stats for each process*******\n";
    cout << "************** q = " << quantum << " ******************\n";
    cout << "***************************************\n";
    printStats(finishedRR);
}