#include <iostream>
#include "PCB.hpp"
using namespace std; 

class queue
{
private:
    Node* head;
    int size;
public:
    queue();
    ~queue();
    void push(PCB process);
    PCB pop();
    bool isEmpty();
    int sizeOfQueue();
    void sortQueue(PCB finishedProc); //sort results of queue so it is in order by PID
};

queue::queue()
{
    head = new Node();
    //below 'initializes' all PCB variables
    head->process.priority = -1; //head that keeps track of queue, priority is -1 to indicate it is the head
    head->process.ID = -1; //this is the head
    head->process.arrived = 0;
    head->process.burstTime = 0;
    head->process.completed = 0;
    head->process.leave = 0;
    head->process.numSwitches = 0;
    head->process.response = -1;
    head->process.turnaround = 0;
    head->process.wait = 0;
    //head->nextptr = nullptr; //points to NULL bc there is no process to point to next
    size = 0;
    //cout << "Process ID: " << head->process.ID << endl;
}

void queue::push(PCB process) { //push process to the back of queue
    Node* tempNode = new Node;
    Node* tracker = new Node;

    tempNode->process = process;
    //cout << "Process ID: " << tempNode->process.ID << endl;
    tempNode->nextptr = nullptr;

    tracker = head;
    while (tracker->nextptr != nullptr) {
        //cout << "Current Process: " << tracker->process.ID << endl;
        tracker = tracker->nextptr;
    }
    tracker->nextptr = tempNode;
    size += 1;
}

PCB queue::pop() { //pop process that is in the front of the queue
    Node* front = new Node;
    front = head->nextptr;
    PCB leave;

    head->nextptr = front->nextptr; //point to the next process in line after first process in line
    front->nextptr = nullptr; //'removes' first process in line from queue
    size -= 1; 

    leave = front->process;
    //cout << leave.ID << endl;
    //cout << leave.completed << endl;
    delete front; //safely remove process from ready queue and it will be running or done executing 

    return leave;
}

bool queue::isEmpty() {
    if (size == 0) {
        return true;
    }
    return false;
}

int queue::sizeOfQueue() {
    return size;
}

void queue::sortQueue(PCB finishedProc) {
    Node* newProc = new Node();
    newProc->process = finishedProc;
    newProc->nextptr = nullptr;

    Node* previous = new Node();
    Node* current = new Node();

    previous = head;
    current = head->nextptr;

    while (current != nullptr) {
        if (newProc->process.ID < current->process.ID) {
            previous->nextptr = newProc;
            newProc->nextptr = current;
            size += 1;
            return;
        }
        previous = current;
        current = current->nextptr;
    }

    if (current == nullptr) {
        push(finishedProc);
    }
}

queue::~queue()
{
    //if size != 0, then remove all processes from queue until it is empty, then delete the queue
}
