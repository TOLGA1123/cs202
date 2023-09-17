/*
* Title: Heaps and AVL Tree
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 3
* Description: heap sort
*/
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "heap.h"
#include <math.h>
using namespace std;
//global heapSort takes array   heapRebuild(arr[], i, n)
//main read file and create array to pass heapSort
//no of comparisons = n + (n*logn)
//n insertion since it inserts all members to heap initially
//n*logn popMaximum comparisons + n*logn insertion comparisons      //each insertion and deletion approx. height of heap comparison made(logn)
//heap building is O(n*logn) instead of O(n) here since I have to use the heap data structure unlike slides
int getCompTheoretical(const int n){
    int total = 0;
    for(int i = 2; i <= n; i++){        //for heap construction
        total += ceil(log2(i));
    }
    for(int i = 1; i <= n; i++){        //for heap reBuild
        total += ceil(log2(i));
    }
    return total;
}
//heap h?, in slides it doesnt use extra heap
void heapSort(int * arr, int n){        //O(nlogn) ???
    Heap h;
    for(int i = 0; i < n; i++){     //O(n) * O(logn)
        h.insert(arr[i]);
    }
    for(int last = n - 1; last >= 0; last--){   //O(n) * O(logn)
        arr[last] = h.popMaximum();
    }
    cout << "Number of data n: " << n << endl;
    cout << "Number of comparisons in heapsort: " << h.getCompCount() << endl;
    cout << "Theoretical value of comparisons during heapsort: " << getCompTheoretical(n) << endl;
}
void displayArray(int* arr, int n){
    for(int i = 0; i < n; i++){
        cout << arr[i] << endl;
    }
}
int main(int argc, const char * argv[]) {
    string inputFileName(argv[1]);
    string outputFileName(argv[2]);
    const int MAX_ARRAY = 100000;              //idk about this
    /*int arr[] = {3,2,4,1,7,5,8,1,9,11,2,4};
    cout << "array before heapSort" << endl;
    for(int i = 0; i < 12; i++){
        cout << arr[i] << " ";
    }
    heapSort(arr, 12);
    cout << "\narray after heapSort" << endl;
    for(int i = 0; i < 12; i++){
        cout << arr[i] << " ";
    }*/
    ifstream inputFile(inputFileName.c_str());
    ofstream outputFile(outputFileName.c_str());
    string text;
    int n = 0;
    int* arr = new int[MAX_ARRAY];
    while(getline(inputFile, text)){
        //cout << text << endl;
        int item = atoi(text.c_str());
        arr[n] = item;
        n++;
    }
    inputFile.close();
    //displayArray(arr, n);
    cout << "For input file " << inputFileName << endl;
    heapSort(arr, n);
    for(int i = 0; i < n; i++){
        outputFile << arr[i] << endl;
    }
    outputFile.close();
    delete [] arr;
    return 0;
}
