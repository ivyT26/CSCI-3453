//implementations of page replacement algorithms
#include <iostream>
#include <fstream>
#include <iomanip> //used to round page fault rates to 3 decimal places
#include "list.hpp"
using namespace std;

//function prototypes
int readFile(ifstream &infile, string refString[]);
int FIFO(int frames, string ref[], int sizeString, float rates[]);
int LRU(int frames, string ref[], int sizeString, float rates[]);
int optimal(int frames, string ref[], int sizeString, float rates[]);

//reading file of page references
int readFile(ifstream &infile, string refString[]) {
    string input;
    int size = 0;
    while (infile >> input) {
        refString[size] = input;
        infile.ignore();
        ++size;
    }
    return size;
}

//FIFO
int FIFO(int frames, string ref[], int sizeString, float rates[]) {
    //create a list to store references that are ready in memory
    list memoryRef;
    //keep track of page faults
    int faults = 0;
    //keep track of the page fault rates every 2000 pages referenced
    //float rates[5] = {0};
    //counter to parse through rates array
    int position = 0;

    //loop until program finishes reading reference string
    //have counter to keep track of the page currently referenced
    for (int counter = 0; counter < sizeString; ++counter) {
        //checking if current page reference is in the list
        if (memoryRef.findRef(ref[counter]) == false) { //if not in memory
            if (memoryRef.sizeOfList() == frames) { //if list is full, need to replace
                //pop page reference in the front of the list
                memoryRef.popFront();
                //add new page reference to the list
                memoryRef.push(ref[counter]);
            }
            else if (memoryRef.sizeOfList() == 0 || memoryRef.sizeOfList() <= frames) { //if list is not full or empty, can add page reference to list
                memoryRef.push(ref[counter]);
            }
            //add page fault
            faults += 1;
        }
        else {
            //page reference exists, program can reference page and continue to next part in loop
        }

        //calculate page fault rates here
        int nextRate = counter + 1;
        if (nextRate % 2000 == 0) {
            rates[position] = float(faults) / nextRate;
            position += 1;
        }
    }

    //total number of page faults (move to main.cpp)
    //cout << "Total faults: ";
    cout << "FIFO           ";
    cout << faults << "                  ";
    //fault rates
    //cout << "Fault rates:\n";
    for (int i = 0; i < 5; ++i) {
        //cout << (i+1)*2000 << " page faults: " << setprecision(3) << rates[i] << endl;
        cout << fixed << setprecision(3) << rates[i] << "     ";
    }
    cout << endl;

    return faults;
}

//LRU
int LRU(int frames, string ref[], int sizeString, float rates[]) {
    //list to store references that are stored in memory (if in memory, then the page can be referenced)
    //this list will be used to keep track of which pages were used the least recently as well
    list memoryRef;
    //keep track of page faults
    int faults = 0;
    //keep track of page fault rates
    //float rates[5] = {0}; 
    //counter to parse through rates array
    int position = 0;

    //loop until program finishes reading reference string
    for (int counter = 0; counter < sizeString; ++counter) {
        //checking if current page reference is in the list
        if (memoryRef.findRef(ref[counter]) == false) { //if not in memory
            if (memoryRef.sizeOfList() == frames) { //if list is full, need to replace
                //pop page reference in the front of the list
                memoryRef.popFront();
                //add new page reference to the list
                memoryRef.push(ref[counter]);
            }
            else if (memoryRef.sizeOfList() == 0 || memoryRef.sizeOfList() <= frames) { //if list is not full or empty, can add page reference to list
                memoryRef.push(ref[counter]);
            }
            //add page fault
            faults += 1;
        }
        else {
            //page reference exists, program will move the recently used page to the bottom of the list
            memoryRef.remove(ref[counter]);
            memoryRef.push(ref[counter]);
        }

        //calculate page fault rates here
        int nextRate = counter + 1;
        if (nextRate % 2000 == 0) {
            rates[position] = float(faults) / nextRate;
            position += 1;
        }
    }

    //total number of page faults (move to main.cpp)
    //cout << "Total faults: ";
    cout << "LRU            ";
    cout << faults << "                  ";
    //fault rates
    //cout << "Fault rates:\n";
    for (int i = 0; i < 5; ++i) {
        //cout << (i+1)*2000 << " page faults: " << setprecision(3) << rates[i] << endl;
        cout << fixed << setprecision(3) << rates[i] << "     ";
    }
    cout << endl;

    return faults;
}

//Optimal
int optimal(int frames, string ref[], int sizeString, float rates[]) {
    //list to show references of pages in memory
    list memoryRef;
    //keep track of page faults
    int faults = 0;
    //keep track of page fault rates
    //float rates[5] = {0}; 
    //counter to parse through rates array
    int position = 0;
    //keep track of page with latest future reference
    string latePage = "";
    //keep track of when the latest future reference is
    int lateRef = 0;

    //loop until program finishes reading reference string
    for (int counter = 0; counter < sizeString; ++counter) {
        //checking if current page reference is in the list
        if (memoryRef.findRef(ref[counter]) == false) { //if not in memory
            if (memoryRef.sizeOfList() == frames) { //if list is full, need to replace
                memoryRef.remove(memoryRef.latestRef(counter, ref, sizeString));
                memoryRef.push(ref[counter]);
            }
            else if (memoryRef.sizeOfList() == 0 || memoryRef.sizeOfList() <= frames) { //if list is not full or empty, can add page reference to list
                memoryRef.push(ref[counter]);
            }
            //add page fault
            faults += 1;
        }
        else {
            //page reference exists, program will continue
            //do not do continue here, it will skip calculations below
        }

        //calculate page fault rates here
        //does not get all calculations.... something wrong with the counter?
        int nextRate = counter + 1;
        if (nextRate % 2000 == 0) {
            rates[position] = float(faults) / nextRate;
            position += 1;
        }
        //below used for debugging smaller program
        // if (nextRate % 3 == 0) {
        //     rates[position] = float(faults) / nextRate;
        //     position += 1;
        // }
    }

    //total number of page faults (move to main.cpp)
    //cout << "Total faults: ";
    cout << "Optimal        ";
    cout << faults << "                  ";
    //fault rates
    //cout << "Fault rates:\n";
    for (int i = 0; i < 5; ++i) {
        //cout << (i+1)*2000 << " page faults: " << setprecision(3) << rates[i] << endl;
        cout << fixed << setprecision(3) << rates[i] << "     ";
    }
    cout << endl;

    return faults;
}

//**don't forget to do the report!