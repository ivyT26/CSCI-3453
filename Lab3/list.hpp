//implementation of queue to know which pages to replace in FIFO
//implementation of stack to know which page to replace in LRU

#include <iostream>
#include <vector>
#include "Node.hpp"
using namespace std; 

class list
{
private:
    Node* head;
    int size;
public:
    list();
    ~list();
    void push(string page); //push to the end of the list
    string popFront(); //remove page reference in the front (for FIFO)
    bool remove(string page); //remove page reference in the middle of the list (for LRU)
    bool findRef(string page); //find if a page reference exists in the list
    bool isEmpty(); //check if list is empty
    int sizeOfList();
    string latestRef(int count, string strRef[], int sizeRef);
};

list::list()
{
    head = new Node;
    head->pageRef = "";
    head->prevptr = nullptr;
    head->nextptr = nullptr;
    size = 0;
}

void list::push(string page) { //push page reference to the back of queue if it hasn't been in the frames list
    Node* tempNode = new Node;
    Node* tracker = new Node;

    tempNode->pageRef = page;
    tempNode->prevptr = nullptr;
    tempNode->nextptr = nullptr;

    tracker = head;
    while (tracker->nextptr != nullptr) {
        tracker = tracker->nextptr;
    }
    tracker->nextptr = tempNode;
    tempNode->prevptr = tracker;
    size += 1;
}

string list::popFront() { //pop page that is in the front of the queue (the first reference in the frames list is popped)
    Node* front = new Node;
    front = head->nextptr;
    string leave;

    head->nextptr = front->nextptr; //point to the next page in line after first page in line
    if (front->nextptr != nullptr) {
        front->nextptr->prevptr = head; //reconnect doubly linked list if there is still values at the end of the list
    }
    front->prevptr = nullptr; 
    front->nextptr = nullptr; //'removes' first page reference in line from queue
    size -= 1; 

    leave = front->pageRef;
    delete front; //safely remove process from queue that keeps track of the page references 
    
    return leave;
}

bool list::remove(string page) {
    Node* tracker = new Node;

    tracker = head;

    while (tracker->pageRef != page) {
        if (tracker->nextptr != nullptr) { //continue going to the next reference in the list if it is not the end
            tracker = tracker->nextptr;
        }
        else {
            break;
        }
    }

    if (tracker->pageRef == page && page != "") {
        //connect doubly linked list for removing page reference
        tracker->prevptr->nextptr = tracker->nextptr;
        if (tracker->nextptr != nullptr) { //only do if there are values at the end of the list
            tracker->nextptr->prevptr = tracker->prevptr;
        }
        //'remove' page reference
        tracker->prevptr = nullptr;
        tracker->nextptr = nullptr;
        delete tracker;
        size -= 1;
        return true;
    }
    else {
        return false; //cannot remove page because it does not exist
    }
}

bool list::findRef(string page) {
    Node* tracker = new Node;

    tracker = head->nextptr;

    if (size == 0) {
        return false; //if list is empty, can't find the page
    }

    for (int i = 0; i < size; ++i) {
        if (tracker->pageRef == page) {
            return true;
        }
        tracker = tracker->nextptr;
    }
    return false;
}

//additional function for optimal algorithm that searches for the latest future reference of a page
string list::latestRef(int count, string strRef[], int sizeRef) {
    Node* tracker = new Node;
    tracker = head->nextptr;

    int latestTime = 0;
    string latestPage = "";

    bool leave = false;

    while (tracker != nullptr) { //loops through page references in memory
        for (int i = count+1; i < sizeRef; ++i) { //loops through reference string
            if (tracker->pageRef == strRef[i]) { //if the page reference is equal to the future page
                if (i > latestTime) { //if the position(time) in the reference string is greater than the current greatest position(time)
                    latestPage = tracker->pageRef;
                    latestTime = i;
                }
                break;
            }
            else if (i == sizeRef - 1 && tracker->pageRef != strRef[i]) {
                latestPage = tracker->pageRef;
                latestTime = sizeRef;
                leave = true;
                break;
            }
        }
        if (leave == false) {
            tracker = tracker->nextptr;
        }
        else {
            break;
        }
    }
    return latestPage;
}

bool list::isEmpty() {
    if (size == 0) {
        return true;
    }
    return false;
}

int list::sizeOfList() {
    return size;
}

list::~list()
{
    //if size != 0, then remove all processes from queue until it is empty, then delete the queue
}

