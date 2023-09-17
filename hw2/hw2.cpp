/*
* Title: Trees
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 2
* Description: main
*/
// hw2.cpp
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "NgramTree.h"
int main(int argc, char** argv) {       //command line arguments: input.txt 4  add them on dijkstra like ./a.out input.txt 4
    NgramTree tree;
    string fileName(argv[1]);
    int n = atoi(argv[2]);
    /*cout<< fileName << " " << n << endl; */ //both are correct

    //check for isFull and isComplete       YES YES, NO NO, YES YES, YES NO
    /*NgramTree tree2;
    tree2.addNgram("amp");
    cout << n << "-gram tree is complete: " << (tree2.isComplete() ? "Yes" : "No") << endl;
    cout << n << "-gram tree is full: " << (tree2.isFull() ? "Yes" : "No") << endl;
    tree2.addNgram("maw");
    cout << n << "-gram tree is complete: " << (tree2.isComplete() ? "Yes" : "No") << endl;
    cout << n << "-gram tree is full: " << (tree2.isFull() ? "Yes" : "No") << endl;
    tree2.addNgram("aab");
    cout << n << "-gram tree is complete: " << (tree2.isComplete() ? "Yes" : "No") << endl;
    cout << n << "-gram tree is full: " << (tree2.isFull() ? "Yes" : "No") << endl;
    tree2.addNgram("aaa");
    cout << n << "-gram tree is complete: " << (tree2.isComplete() ? "Yes" : "No") << endl;
    cout << n << "-gram tree is full: " << (tree2.isFull() ? "Yes" : "No") << endl; */
    //tree.addNgram("abc"); //generateTree with n = 4 must be called first          THIS CAUSES PROBLEMS IF LENGTH != N
    tree.generateTree(fileName, n);
    cout << "\nTotal " << n << "-gram count: " << tree.getTotalNgramCount() << endl;
    cout << tree << endl;
    cout << n << "-gram tree is complete: " << (tree.isComplete() ? "Yes" : "No") << endl;
    cout << n << "-gram tree is full: " << (tree.isFull() ? "Yes" : "No") << endl;
    // Before insertion of new n-grams
    cout << "\nTotal " << n << "-gram count: " << tree.getTotalNgramCount() << endl;
    tree.addNgram("samp");                  //WHAT IF N != 4    it still inserts in alpabetical order
    tree.addNgram("samp");
    tree.addNgram("zinc");
    tree.addNgram("aatt");
    //tree.addNgram("a bc");
    cout << "\nTotal " << n << "-gram count: " << tree.getTotalNgramCount() << endl;
    cout << tree << endl;
    cout << n << "-gram tree is complete: " << (tree.isComplete() ? "Yes" : "No") << endl;
    cout << n << "-gram tree is full: " << (tree.isFull() ? "Yes" : "No") << endl;
    /*tree.addNgram("abcdefs");
    tree.addNgram("ab");
    cout << "\nTotal " << n << "-gram count: " << tree.getTotalNgramCount() << endl;
    cout << "\nAfter deleting" << endl;
    tree.deleteNgram("zinc");
    tree.deleteNgram("samp");
    cout << "\nTotal " << n << "-gram count: " << tree.getTotalNgramCount() << endl;
    cout << tree << endl;
    cout << n << "-gram tree is complete: " << (tree.isComplete() ? "Yes" : "No") << endl;
    cout << n << "-gram tree is full: " << (tree.isFull() ? "Yes" : "No") << endl; */
    return 0;
}

