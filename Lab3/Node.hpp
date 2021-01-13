#include <iostream>
using namespace std;

struct Node {
    string pageRef;
    Node *prevptr;
    Node *nextptr;
};