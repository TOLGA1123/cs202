/*
* Title: Balanced Search Trees
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 4
* Description: main
*/
// main.cpp
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "AVLTree.h"
#include <fstream>
int main(int argc, char** argv) {
    AVLTree tree;
    string fileName(argv[1]);
    tree.generateTree(fileName);
    ofstream frequency("wordfreqs");
    ofstream statistics("statistics");
    //writing frequency file
    tree.printWordFrequencies(frequency);
    //writing statistics file
    tree.printTotalWordCount(statistics);
    tree.printHeight(statistics);
    tree.printMostFrequent(statistics);
    tree.printLeastFrequent(statistics);
    tree.printStandartDeviation(statistics);
    frequency.close();
    statistics.close();
return 0;
}
