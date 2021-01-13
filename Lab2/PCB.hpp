#include <iostream>
#include <string>
using namespace std;

struct PCB {
    //process ID data
    int ID;
    //process control data
    float arrived;
    int priority;
    float burstTime;
    float turnaround;
    float wait;
    float response;
    int numSwitches;
    float completed; //how long process has run so far
    float leave;
};

struct Node {
    PCB process;
    Node *nextptr;
};
