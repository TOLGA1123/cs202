/*
* Title: Sorting and Algorithm Efficiency
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 1
* Description: Sorting source
*/
#include <iostream>
#include "sorting.h"
#include <stdio.h>
#include <chrono>
#include <time.h>
#include<cstdlib>
#include <iomanip>
#include <cmath>
using namespace std;

    void bubbleSort(int *arr, const int size, int &compCount, int &moveCount){
        bool sorted = false;    //false when swaps occur
        for(int pass = 1; (pass < size) && !sorted; pass++){
            sorted = true;
            for(int index = 0; index < size - pass; index++){
                int nextIndex = index + 1;
                if(arr[index] > arr[nextIndex]){
                    swap(arr[index], arr[nextIndex]);
                    moveCount += 3;
                    sorted = false;
                }
                compCount++;        //only count array entry comparisons
            }
        }

    }
    void mergeSort(int *arr, const int size, int &compCount, int &moveCount){
        mergeSort(arr, 0, size - 1, compCount, moveCount);
    }
    void mergeSort(int *arr, int first, int last, int &compCount, int &moveCount){
        if(first < last){
            int mid = (first + last) / 2;   //index of midpoint
            //sort left half
            mergeSort(arr, first, mid, compCount, moveCount);
            //sort right half
            mergeSort(arr, mid + 1, last, compCount, moveCount);
            //merge the two halves
            merge(arr, first, mid, last, compCount, moveCount);
        }
    }
    void merge(int *arr, int first, int mid, int last, int &compCount, int &moveCount){
        int* tempArr = new int[last + 1];      //temporary array
        int first1 = first;         //beginning of first subarray
        int last1 = mid;            //end of first subarray
        int first2 = mid + 1;       //beginning of second subarray
        int last2 = last;           //end of second subarray
        int index = first1;         //next available location in tempArray
        for(; (first1 <= last1) && (first2 <= last2); index++){
            if(arr[first1] < arr[first2]){
                tempArr[index] = arr[first1];
                first1++;
            }
            else{
                tempArr[index] = arr[first2];
                first2++;
            }
            compCount++;            //only count array entry comparisons
            moveCount++;
        }
        //finish nonempty subarrays, if necessary
        for(; first1 <= last1; ++first1, index++){
            tempArr[index] = arr[first1];
            moveCount++;
        }
        for(; first2 <= last2; ++first2, index++){
            tempArr[index] = arr[first2];
            moveCount++;
        }
        //copy the result back into the original array
        for(index = first; index <= last; index++){
            arr[index] = tempArr[index];
            moveCount++;
        }
        delete [] tempArr;

    }
    //swap function ( 3 moves )
    void swap(int &x, int &y){
        int temp = x;
        x = y;
        y = temp;
    }
    void partition(int *arr, int first, int last, int& pivotIndex, int &compCount, int &moveCount){
        //choosePivot(arr, first, last);
        int pivot = arr[first];
        moveCount++;
        int lastS1 = first;             //index of last item in S1
        int firstUnknown = first + 1;   //index of first item in unknown
        for(; firstUnknown <= last; firstUnknown++){
            if(arr[firstUnknown] < pivot){          //item belongs to S1
                lastS1++;
                swap(arr[firstUnknown], arr[lastS1]);
                moveCount += 3;
            }
            //else item belongs to S2
             compCount++;
        }
        //place pivot in proper position
        swap(arr[first], arr[lastS1]);
        moveCount += 3;
        pivotIndex = lastS1;
    }
    void quickSort(int *arr, const int size, int& compCount, int& moveCount){
        quickSort(arr, 0, size - 1, compCount, moveCount);
    }
    void quickSort(int *arr, int first, int last, int& compCount, int& moveCount) {
        while (first < last) {                              //modified to avoid stack overflow after input size > 28000
            int pivotIndex;
            partition(arr, first, last, pivotIndex, compCount, moveCount);
            // Tail recursion elimination
            if (pivotIndex - first < last - pivotIndex) {
            quickSort(arr, first, pivotIndex - 1, compCount, moveCount);
            first = pivotIndex + 1;
            }   else {
            quickSort(arr, pivotIndex + 1, last, compCount, moveCount);
            last = pivotIndex - 1;
            }
        }
    }

    void displayArray(const int* arr, const int size){
        cout << "[";
        if(size > 0){
            for(int i = 0; i < size - 1; i++){
                cout << arr[i] << " ";
            }
            cout << arr[size - 1];
        }
        cout << "]" << endl;
    }
    void createAscendingArrays(int*& arr1, int*& arr2, int*& arr3, const int size){
        arr1[0] = 0;
        arr2[0] = 0;
        arr3[0] = 0;
        for(int i = 1; i < size; i++){
            int random = rand() % 10;                                 //array with ascending random integers range 0-?      change mod if necessary
            arr1[i] = arr1[i-1] + random;
            arr2[i] = arr2[i-1] + random;
            arr3[i] = arr3[i-1] + random;
        }
    }
    void createDescendingArrays(int*& arr1, int*& arr2, int*& arr3, const int size){
        arr1[size-1] = 0;
        arr2[size-1] = 0;
        arr3[size-1] = 0;
        for(int i = size - 1; i > 0; i--){
            int random = rand() % 10;                                 //array with descending random integers range ?-0     change mod if necessary
            arr1[i-1] = arr1[i] + random;
            arr2[i-1] = arr2[i] + random;
            arr3[i-1] = arr3[i] + random;
        }

    }
    void createRandomArrays(int*& arr1, int*& arr2, int*& arr3, const int size){
        int lower = 0;
        int upper = size;
        for(int i = 0; i < size; i++){
            int random = (rand() % (upper - lower + 1)) + lower;        //random integer within range 0 - size
            arr1[i] = random;                                           //rand creates same sequence of random numbers every run
            arr2[i] = random;
            arr3[i] = random;
        }
    }
    void performanceAnalysis(){
        int arraySizes[] = {4000, 8000, 12000, 16000, 20000, 24000, 28000, 32000, 36000, 40000};
        std::chrono::time_point<std::chrono::system_clock> startTime;
        std::chrono::duration<double, milli> elapsedTime;
        //store elapsed times, compCount, moveCount for bubble sort
        double elapsedTimesRandom1[10];        int compCountRandom1[10];       int moveCountRandom1[10];            //moveCount and compCount are int variables
        double elapsedTimesAscending1[10];     int compCountAscending1[10];    int moveCountAscending1[10];         //so making long long int are useless anyway moveCountDescending1[9]
        double elapsedTimesDescending1[10];    int compCountDescending1[10];    int moveCountDescending1[10];       //exceeds integer limit
        //store elapsed times, compCount, moveCount for merge sort
        double elapsedTimesRandom2[10];        int compCountRandom2[10];       int moveCountRandom2[10];
        double elapsedTimesAscending2[10];     int compCountAscending2[10];    int moveCountAscending2[10];
        double elapsedTimesDescending2[10];    int compCountDescending2[10];   int moveCountDescending2[10];
        //store elapsed times, compCount, moveCount for quick sort
        double elapsedTimesRandom3[10];        int compCountRandom3[10];       int moveCountRandom3[10];
        double elapsedTimesAscending3[10];     int compCountAscending3[10];    int moveCountAscending3[10];
        double elapsedTimesDescending3[10];    int compCountDescending3[10];   int moveCountDescending3[10];
            for(int j = 0; j < 10; j++){
                    //random array bubble sort
                int *arr1 = new int[arraySizes[j]];
                int *arr2 = new int[arraySizes[j]];
                int *arr3 = new int[arraySizes[j]];
                int compCount, moveCount = 0;
                createRandomArrays(arr1, arr2, arr3, arraySizes[j]);
                startTime = std::chrono::system_clock::now();
                bubbleSort(arr1, arraySizes[j], compCount, moveCount);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                elapsedTimesRandom1[j] = elapsedTime.count();
                compCountRandom1[j] = compCount;
                moveCountRandom1[j] = moveCount;
                    //random array merge sort
                compCount = 0; moveCount = 0;
                startTime = std::chrono::system_clock::now();
                mergeSort(arr2, arraySizes[j], compCount, moveCount);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                elapsedTimesRandom2[j] = elapsedTime.count();
                compCountRandom2[j] = compCount;
                moveCountRandom2[j] = moveCount;
                    //random array quick sort
                compCount = 0; moveCount = 0;
                startTime = std::chrono::system_clock::now();
                quickSort(arr3, arraySizes[j], compCount, moveCount);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                elapsedTimesRandom3[j] = elapsedTime.count();
                compCountRandom3[j] = compCount;
                moveCountRandom3[j] = moveCount;
                    //ascending array bubble sort
                compCount = 0; moveCount = 0;
                createAscendingArrays(arr1, arr2, arr3, arraySizes[j]);
                startTime = std::chrono::system_clock::now();
                bubbleSort(arr1, arraySizes[j], compCount, moveCount);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                elapsedTimesAscending1[j] = elapsedTime.count();
                compCountAscending1[j] = compCount;
                moveCountAscending1[j] = moveCount;
                    //ascending array merge sort
                compCount = 0; moveCount = 0;
                startTime = std::chrono::system_clock::now();
                mergeSort(arr2, arraySizes[j], compCount, moveCount);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                elapsedTimesAscending2[j] = elapsedTime.count();
                compCountAscending2[j] = compCount;
                moveCountAscending2[j] = moveCount;
                    //ascending array quick sort
                compCount = 0; moveCount = 0;
                startTime = std::chrono::system_clock::now();
                quickSort(arr3, arraySizes[j], compCount, moveCount);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                elapsedTimesAscending3[j] = elapsedTime.count();
                compCountAscending3[j] = compCount;
                moveCountAscending3[j] = moveCount;
                    //descending array bubble sort
                compCount = 0; moveCount = 0;
                createDescendingArrays(arr1, arr2, arr3, arraySizes[j]);
                startTime = std::chrono::system_clock::now();
                bubbleSort(arr1, arraySizes[j], compCount, moveCount);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                elapsedTimesDescending1[j] = elapsedTime.count();
                compCountDescending1[j] = compCount;
                moveCountDescending1[j] = moveCount;
                    //descending array merge sort
                compCount = 0; moveCount = 0;
                startTime = std::chrono::system_clock::now();
                mergeSort(arr2, arraySizes[j], compCount, moveCount);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                elapsedTimesDescending2[j] = elapsedTime.count();
                compCountDescending2[j] = compCount;
                moveCountDescending2[j] = moveCount;
                    //descending array quick sort
                compCount = 0; moveCount = 0;
                startTime = std::chrono::system_clock::now();
                quickSort(arr3, arraySizes[j], compCount, moveCount);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                elapsedTimesDescending3[j] = elapsedTime.count();
                compCountDescending3[j] = compCount;
                moveCountDescending3[j] = moveCount;
                delete[] arr1; delete[] arr2; delete[] arr3;
            }
            cout << "RANDOM ARRAYS" << endl;
            cout << "-----------------------------------------------------" << endl;
            cout << "Analysis of Bubble Sort" << endl;
            cout << std::setw(5) << "Array Size" << std::setw(15) << " Elapsed time" << std::setw(16) << " compCount" << std::setw(16) << " moveCount" << endl;
            for(int i = 0; i < 10; i++){
                cout << std::setw(5) << arraySizes[i] << std::setw(15) << elapsedTimesRandom1[i] << " ms" << std::setw(16) << compCountRandom1[i] << std::setw(16) << moveCountRandom1[i] << endl;
            }
            cout << "-----------------------------------------------------" << endl;
            cout << "Analysis of Merge Sort" << endl;
            cout << std::setw(5) << "Array Size" << std::setw(15) << " Elapsed time" << std::setw(16) << " compCount" << std::setw(16) << " moveCount" << endl;
            for(int i = 0; i < 10; i++){
                cout << std::setw(5) << arraySizes[i] << std::setw(15) << elapsedTimesRandom2[i] << " ms" << std::setw(16) << compCountRandom2[i] << std::setw(16) << moveCountRandom2[i] << endl;
            }
            cout << "-----------------------------------------------------" << endl;
            cout << "Analysis of Quick Sort" << endl;
            cout << std::setw(5) << "Array Size" << std::setw(15) << " Elapsed time" << std::setw(16) << " compCount" << std::setw(16) << " moveCount" << endl;
            for(int i = 0; i < 10; i++){
                cout << std::setw(5) << arraySizes[i] << std::setw(15) << elapsedTimesRandom3[i] << " ms" << std::setw(16) << compCountRandom3[i] << std::setw(16) << moveCountRandom3[i] << endl;
            }
            cout << "ASCENDING ARRAYS" << endl;
            cout << "-----------------------------------------------------" << endl;
            cout << "Analysis of Bubble Sort" << endl;
            cout << std::setw(5) << "Array Size" << std::setw(15) << " Elapsed time" << std::setw(16) << " compCount" << std::setw(16) << " moveCount" << endl;
            for(int i = 0; i < 10; i++){
                cout << std::setw(5) << arraySizes[i] << std::setw(15) << elapsedTimesAscending1[i] << " ms" << std::setw(16) << compCountAscending1[i] << std::setw(16) << moveCountAscending1[i] << endl;
            }
            cout << "-----------------------------------------------------" << endl;
            cout << "Analysis of Merge Sort" << endl;
            cout << std::setw(5) << "Array Size" << std::setw(15) << " Elapsed time" << std::setw(16) << " compCount" << std::setw(16) << " moveCount" << endl;
            for(int i = 0; i < 10; i++){
                cout << std::setw(5) << arraySizes[i] << std::setw(15) << elapsedTimesAscending2[i] << " ms" << std::setw(16) << compCountAscending2[i] << std::setw(16) << moveCountAscending2[i] << endl;
            }
            cout << "-----------------------------------------------------" << endl;
            cout << "Analysis of Quick Sort" << endl;
            cout << std::setw(5) << "Array Size" << std::setw(15) << " Elapsed time" << std::setw(16) << " compCount" << std::setw(16) << " moveCount" << endl;
            for(int i = 0; i < 10; i++){
                cout << std::setw(5) << arraySizes[i] << std::setw(15) << elapsedTimesAscending3[i] << " ms" << std::setw(16) << compCountAscending3[i] << std::setw(16) << moveCountAscending3[i] << endl;
            }
            cout << "DESCENDING ARRAYS" << endl;
            cout << "-----------------------------------------------------" << endl;
            cout << "Analysis of Bubble Sort" << endl;
            cout << std::setw(5) << "Array Size" << std::setw(15) << " Elapsed time" << std::setw(16) << " compCount" << std::setw(16) << " moveCount" << endl;
            for(int i = 0; i < 10; i++){
                cout << std::setw(5) << arraySizes[i] << std::setw(15) << elapsedTimesDescending1[i] << " ms" << std::setw(16) << compCountDescending1[i] << std::setw(16) << moveCountDescending1[i] << endl;
            }
            cout << "-----------------------------------------------------" << endl;
            cout << "Analysis of Merge Sort" << endl;
            cout << std::setw(5) << "Array Size" << std::setw(15) << " Elapsed time" << std::setw(16) << " compCount" << std::setw(16) << " moveCount" << endl;
            for(int i = 0; i < 10; i++){
               cout << std::setw(5) << arraySizes[i] << std::setw(15) << elapsedTimesDescending2[i] << " ms" << std::setw(16) << compCountDescending2[i] << std::setw(16) << moveCountDescending2[i] << endl;
            }
            cout << "-----------------------------------------------------" << endl;
            cout << "Analysis of Quick Sort" << endl;
            cout << std::setw(5) << "Array Size" << std::setw(15) << " Elapsed time" << std::setw(16) << " compCount" << std::setw(16) << " moveCount" << endl;
            for(int i = 0; i < 10; i++){
                cout << std::setw(5) << arraySizes[i] << std::setw(15) << elapsedTimesDescending3[i] << " ms" << std::setw(16) << compCountDescending3[i] << std::setw(16) << moveCountDescending3[i] << endl;
            }
    }
