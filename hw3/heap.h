/*
* Title: Heaps and AVL Tree
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 3
* Description: heap header
*/
#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <string>
#include <limits.h>
using namespace std;
const int MAX_HEAP = 100000;       //maybe change this 1 million gives stack overflow
    class Heap{
        public:
        Heap(); //default constructor
        //copy constructor and destructor are supplied by the compiler
        bool isEmpty() const;
        void insert(const int a);
        int popMaximum();
        int maximum();
        int getCompCount();
        protected:
        void heapRebuild(int root);
        private:
            int size;
            int compCount;      //only array item comparisons
            int items[MAX_HEAP];
    };








#endif // HEAP_H
