//main program that will run the menu and page replacement algorithms
#include <iostream>
#include <string>
#include <fstream>
#include "functions.hpp"
//#include "stack.hpp"
using namespace std;

int main(int argc, char *argv[]) {

    ifstream infile;
    string file, file1;
    int frames;
    ofstream outfile;
    float rates[5] = {0};
    int faultsList[3] = {0};

    //used code from Lab 2 to implement obtaining inputs when program is called rather than using a menu
    if (argc == 4) {
        char* val1;
        long convNum = strtol(argv[1], &val1, 10); //get frame size

        frames = convNum;

        file = argv[2];
        file1 = argv[3];

        //cout << file << " " << file1 << endl;
    }
    else {
        cout << "Too many arguments or not enough arguments.\n";
    }

    // list test;

    // for (int i = 0; i < 5; ++i) {
    //     test.push(to_string(i));
    // }

    // test.remove("3");
    // test.remove("1");

    // for (int i = 0; i < 5; ++i) {
    //     cout << test.popFront() << endl;
    // }

    // cout << "Type input file.\n";
    // cin >> file;
    // cout << "Type number of frames.\n";
    // cin >> frames;

    string refString[10000]; //max number of page references

    int numRef = 0;
    infile.open(file);
    numRef = readFile(infile, refString);
    infile.close();

    outfile.open(file1);

    //format printing stats out here andoutput to a file
    outfile << "Page Replacement Algorithm Simulation\n";
    outfile << "------------frame size = " << frames << " -----------------\n";
    outfile << "                                     Page Fault Rates\n";
    outfile << "Algorithm     Total Page Faults      2000      4000      6000      8000      10000\n";

    cout << "Page Replacement Algorithm Simulation\n";
    cout << "------------frame size = " << frames << " -----------------\n";
    cout << "                                     Page Fault Rates\n";
    cout << "Algorithm     Total Page Faults      2000      4000      6000      8000      10000\n";

    faultsList[0] = FIFO(frames, refString, numRef, rates);

    outfile << "FIFO           ";
    outfile << faultsList[0] << "                  ";
    //fault rates
    for (int i = 0; i < 5; ++i) {
        //cout << (i+1)*2000 << " page faults: " << setprecision(3) << rates[i] << endl;
        outfile << fixed << setprecision(3) << rates[i] << "     ";
    }
    outfile << endl;

    faultsList[1] = LRU(frames, refString, numRef, rates);

    outfile << "LRU            ";
    outfile << faultsList[1] << "                  ";
    //fault rates
    for (int i = 0; i < 5; ++i) {
        //cout << (i+1)*2000 << " page faults: " << setprecision(3) << rates[i] << endl;
        outfile << fixed << setprecision(3) << rates[i] << "     ";
    }
    outfile << endl;

    faultsList[2] = optimal(frames, refString, numRef, rates);

    outfile << "Optimal        ";
    outfile << faultsList[2] << "                  ";
    //fault rates
    //cout << "Fault rates:\n";
    for (int i = 0; i < 5; ++i) {
        //cout << (i+1)*2000 << " page faults: " << setprecision(3) << rates[i] << endl;
        outfile << fixed << setprecision(3) << rates[i] << "     ";
    }
    outfile << endl;

    outfile.close();

    return 0;
}