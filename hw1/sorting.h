/*
* Title: Sorting and Algorithm Efficiency
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 1
* Description: Sorting header
*/
#ifndef SORTING_H
#define SORTING_H
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include<cstdlib>
#include <iomanip>
#include <cmath>
using namespace std;
    void bubbleSort(int *arr, const int size, int &compCount, int &moveCount);
    void mergeSort(int *arr, const int size, int &compCount, int &moveCount);
    void quickSort(int *arr, const int size, int &compCount, int &moveCount);

    //Helper functions
    void swap(int &x, int&y);
    void mergeSort(int *arr, int first, int last, int &compCount, int &moveCount);      //overloaded mergeSort function
    void merge(int *arr, int first, int mid, int last, int &compCount, int &moveCount);
    //void choosePivot(int *arr, int first, int last);                                    //choose the first element as pivot always --> this function not needed
    void partition(int *arr, int first, int last, int &pivotIndex, int &compCount, int &moveCount);
    void quickSort(int *arr, int first, int last, int &compCount, int &moveCount);      //overloaded quickSort function
    void displayArray(const int *arr, const int size);                                  //prints array
    void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, const int size);        //creates 3 identical random arrays
    void createAscendingArrays(int *&arr1, int *&arr2, int *&arr3, const int size);     //creates 3 identical ascending arrays
    void createDescendingArrays(int *&arr1, int *&arr2, int *&arr3, const int size);    //creates 3 identical descending arrays
    void performanceAnalysis();                                                         //outputs elapsed times, moveCounts, compCounts
#endif // SORTING_H
