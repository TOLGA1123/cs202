/*
* Title: Heaps and AVL Tree
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 3
* Description: heap source
*/
#include "heap.h"
#include <iostream>
#include <string>
using namespace std;

    Heap::Heap(){
        this->size = 0;
        this->compCount = 0;
    }
    bool Heap::isEmpty() const{
        return (this->size == 0);
    }
    void Heap::insert(const int a)
    //Inserts the new item after the last item in the heap
    //and trickles it up to its proper position. The heap is
    //full when it contains MAX_HEAP items.
    {
        if(size > MAX_HEAP){
            cout << "Insertion failed, heap is full." << endl;
            return;
        }
        //place the new item at the end of the heap
        items[size] = a;
        //trickle new item up to its proper position
        int place = size;
        int parent = (place - 1) / 2;
        while((parent >= 0) && (items[place] > items[parent])){
            //swap items[place] and items[parent]
            int temp = items[parent];
            items[parent] = items[place];
            items[place] = temp;
            place = parent;
            parent = (place - 1) / 2;
            ++compCount;
        }
        ++size;
    }
    int Heap::maximum(){
        if(isEmpty()){
            cout << "Heap is empty." << endl;
            return -1;
        }
        return items[0];
    }
    int Heap::popMaximum()
    //Swaps the last item in the heap with the root
    //and trickles it down to proper position
    {
        if(isEmpty()){
            cout << "Deletion failed, heap is empty." << endl;
            return -1;
        }
        int max = maximum();
        items[0] = items[--size];
        heapRebuild(0);
        return max;
    }
    void Heap::heapRebuild(int root){
    //if the root is not a leaf and the root's search key is
    //less than the larger of the search keys in the root's children
        int child = 2 * root + 1; //index of root's left child, if any
        if(child < size){
        //root is not a leaf, so it has a left child at child
            int rightChild = child + 1; //index of right child, if any
        //if root has a right child, find larger child
            if((rightChild < size) && (items[rightChild] > items[child])){
                child = rightChild;
                ++compCount;
            }
            //if the root's value is smaller than the value in the larger child, swap values
            if(items[root] < items[child]){
                ++compCount;
                int temp = items[root];
                items[root] = items[child];
                items[child] = temp;
                //transform the new subtree into a heap
                heapRebuild(child);
            }
        }
        //if root is a leaf, do nothing
    }
    int Heap::getCompCount(){
        return compCount;
    }
