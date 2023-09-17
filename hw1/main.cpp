/*
* Title: Sorting and Algorithm Efficiency
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 1
* Description: main
*/
#include <iostream>
#include "sorting.h"
using namespace std;
int main(){
    const int size = 16;
    int arr1[size] = {10,5,9,16,17,7,4,12,19,1,15,18,3,11,13,6};
    cout << "Initial array: " << endl;
    displayArray(arr1, size);
    int compCount1 = 0;
    int moveCount1 = 0;
    bubbleSort(arr1, size, compCount1, moveCount1);
    cout << "BUBBLE SORT" << endl;
    cout << "Number of key comparisons: " << compCount1 << endl;
    cout << "Number of data moves: " << moveCount1 << endl;
    cout << "Array after bubble sort: " << endl;
    displayArray(arr1, size);
    cout << endl;
    int arr2[size] = {10,5,9,16,17,7,4,12,19,1,15,18,3,11,13,6};
    cout << "Initial array: " << endl;
    displayArray(arr2, size);
    int compCount2 = 0;
    int moveCount2 = 0;
    mergeSort(arr2, size, compCount2, moveCount2);
    cout << "MERGE SORT" << endl;
    cout << "Number of key comparisons: " << compCount2 << endl;
    cout << "Number of data moves: " << moveCount2 << endl;
    cout << "Array after merge sort: " << endl;
    displayArray(arr2, size);
    cout << endl;
    int arr3[size] = {10,5,9,16,17,7,4,12,19,1,15,18,3,11,13,6};
    cout << "Initial array: " << endl;
    displayArray(arr3, size);
    int compCount3 = 0;
    int moveCount3 = 0;
    quickSort(arr3, size, compCount3, moveCount3);
    cout << "QUICK SORT" << endl;
    cout << "Number of key comparisons: " << compCount3 << endl;
    cout << "Number of data moves: " << moveCount3 << endl;
    cout << "Array after quick sort: " << endl;
    displayArray(arr3, size);
    cout << endl;
    performanceAnalysis();

}
