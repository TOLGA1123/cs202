/*
* Title: Trees
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 2
* Description: NgramTree source
*/
#include "NgramTree.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

    TreeNode::TreeNode(){
        this->item = "";
        this->count = 0;
        this->leftChildPtr = nullptr;
        this->rightChildPtr = nullptr;
    }
    TreeNode::TreeNode(const string item, TreeNode* left, TreeNode* right){
        this->item = item;
        this->count = 1;
        this->leftChildPtr = left;
        this->rightChildPtr = right;
    }
    NgramTree::NgramTree(){
        root = nullptr;
    }
    NgramTree::~NgramTree(){
        destroyTree(root);
    }
    void NgramTree::addNgram(const string& ngram ){         //ignore capitalizations and blank characters           //assumes ngram is correct (for n = 4, only 4 word strings passed
        /*//handle blank characters first                   //for calls other than generateTree function)           //blank characters already handled in generateTree
        string str;
        for(int i = 0; i < ngram.length(); i++){
            if(ngram[i] != " "){
                str += ngram[i];
            }
        }
        //handle capitalizations by converting all to lowercase
        for(int i = 0; i < str.length(); i++){
            str[i] = tolower(str[i]);
        }
        ngram = str; */        //cannot change ngram const
        //TreeNode* node = new TreeNode();            //this causes memory leak       if it exists this node should be deleted
        //this check ensures no ngram added with length different than n, generateTree must be called first to have a nonempty tree
        //this check might not be perfect since n cannot be passed this function
        if(root != nullptr && root->item.length() != ngram.length()){
            cout << "Cannot add \""<<   ngram << "\" since it has different length than n" << endl;
            return;
        }
        TreeNode* node = nullptr;
        bool exist = retrieveItem(root, ngram, node);           //retrieveItem function assign the node variable to actual node in tree
        if(exist){
            node->count++;
        }
        else{                                                   //if it does not exist, node should still be nullptr
            insertItem(root, ngram);
        }
    }
    void NgramTree::insertItem(TreeNode *& treePtr, const string& newItem){
        if(treePtr == nullptr){
            //position of insertion found; insert after leaf
            treePtr = new TreeNode(newItem, nullptr, nullptr);
            //this part should be in the if
            if(treePtr == nullptr){
            cout << "Insertion failed" << endl;     //unsuccessful allocation
            }
        }
        else if(newItem.compare(treePtr->item) < 0){    //search for left subtree
            insertItem(treePtr->leftChildPtr, newItem);
        }
        else{                                           //search for right subtree
            insertItem(treePtr->rightChildPtr, newItem);
        }
    }
    bool NgramTree::retrieveItem(TreeNode * treePtr, string ngram, TreeNode *& treeItem){
        if(treePtr == nullptr){
            return false;
        }
        else if(ngram.compare(treePtr->item) == 0){
            treeItem = treePtr;
            return true;
        }
        else if(ngram.compare(treePtr->item) < 0){
            return retrieveItem(treePtr->leftChildPtr, ngram, treeItem);
        }
        else{
            return retrieveItem(treePtr->rightChildPtr, ngram, treeItem);
        }
    }
    void NgramTree::destroyTree(TreeNode *& treePtr){
        if(treePtr != nullptr){
            destroyTree(treePtr->leftChildPtr);
            destroyTree(treePtr->rightChildPtr);
            delete treePtr;
            treePtr = nullptr;
        }
    }
    void NgramTree::generateTree( const string& fileName, const int n ){
        string word;
        ifstream inputFile;
        inputFile.open(fileName.c_str());
        while(inputFile >> word){                   // >> already separate words if encounter with space, tabs,
            int length = word.length();
            if((int) length >= n){
                for(int i = 0; i <= (int) length - n; i++){      // cast (int) for warning
                    string ngram = word.substr(i,n);
                    //cout << ngram << endl;
                    addNgram(ngram);
                }
            }
        }
        inputFile.close();
    }
    int NgramTree::getTotalNgramCount() const{
        int totalNgrams = 0;
        countNgramHelper(root, totalNgrams);
        return totalNgrams;
    }
    //preorder traversal to count Ngrams in tree
    void NgramTree::countNgramHelper(TreeNode* treePtr, int& total)const{
        if(treePtr != nullptr){
            //total += treePtr->count;      //count total ngrams (including duplicates)
            total ++;       //only count unique ngrams --> in pdf
            countNgramHelper(treePtr->leftChildPtr, total);
            countNgramHelper(treePtr->rightChildPtr, total);
        }
    }
    bool NgramTree::isComplete() const{
        int noOfNodes = countNodes(root);
        int index = 0;
        return isCompleteHelper(root, index, noOfNodes);
    }
    bool NgramTree::isFull() const{
        return isFullHelper(root);
    }
    bool NgramTree::isFullHelper(TreeNode* treePtr) const{
        //if empty tree
        if(treePtr == nullptr){
            return true;
        }
        //if leaf node
        if(treePtr->leftChildPtr == nullptr && treePtr->rightChildPtr == nullptr){
            return true;
        }
        //if node has left and right child check if left and right subtrees are full recursively
        if(treePtr->leftChildPtr != nullptr && treePtr->rightChildPtr != nullptr){
                bool leftFull = isFullHelper(treePtr->leftChildPtr);
                bool rightFull = isFullHelper(treePtr->rightChildPtr);
                return (leftFull && rightFull);
        }
        //else it is not full //only 1 child etc.
        return false;
    }
    //helper function to count number of nodes in the tree
    int NgramTree::countNodes(TreeNode* treePtr)const{
        if(treePtr == nullptr){
            return 0;
        }
        int noOfNodes = 1 + countNodes(treePtr->leftChildPtr) + countNodes(treePtr->rightChildPtr);
        return noOfNodes;       //might be something wrong here
    }
    //index nodes left to right each level in BST, if index >= noOfNodes in tree on the node, it is not complete
    bool NgramTree::isCompleteHelper(TreeNode* treePtr, int index, int noOfNodes) const{
        //empty tree
        if(treePtr == nullptr){
            return true;
        }
        if(index >= noOfNodes){
            return false;
        }
        //else do recursion on left and right subtree
        bool leftComplete = isCompleteHelper(treePtr->leftChildPtr, 2 * index + 1, noOfNodes);
        bool rightComplete = isCompleteHelper(treePtr->rightChildPtr, 2 * index + 2, noOfNodes);
        return (leftComplete && rightComplete);
    }
    //prints each Ngram alphabetical order, uses inorder traversal
    ostream& operator<<(ostream& out, const NgramTree& tree) {
    tree.printInorder(tree.root, out);
    return out;
    }
    void NgramTree::printInorder(TreeNode * treePtr, ostream& out) const{
        if(treePtr != nullptr){
            printInorder(treePtr->leftChildPtr, out);
            out << "\"" << treePtr->item << "\" " << "appears " << treePtr->count << " time(s)" << endl;
            printInorder(treePtr->rightChildPtr, out);
        }
    }
    void NgramTree::deleteItem(TreeNode *& treePtr, const string& itemToDelete){
        if(treePtr == nullptr){                 //empty tree
            cout << "Delete failed " << endl;
        }
        else if(itemToDelete.compare(treePtr->item) == 0){
            deleteNodeItem(treePtr);
        }
        else if(itemToDelete.compare(treePtr->item) < 0){
            deleteItem(treePtr->leftChildPtr, itemToDelete);
        }
        else{
            deleteItem(treePtr->rightChildPtr, itemToDelete);
        }
    }
    void NgramTree::deleteNodeItem(TreeNode *& nodePtr){
        TreeNode *delPtr;
        string replacementItem;
        int replacementCount;
        //test for a leaf
        if((nodePtr->leftChildPtr == nullptr) && (nodePtr->rightChildPtr == nullptr)){
            delete nodePtr;
            nodePtr = nullptr;
        }
        //test for no left child
        else if(nodePtr->leftChildPtr == nullptr){
            delPtr = nodePtr;
            nodePtr = nodePtr->rightChildPtr;
            delPtr->rightChildPtr = nullptr;
            delete delPtr;
        }
        //test for no right child
        else if(nodePtr->rightChildPtr == nullptr){
            delPtr = nullptr;
            nodePtr = nodePtr->leftChildPtr;
            delPtr->leftChildPtr = nullptr;
            delete delPtr;
        }
        //two children
        else{
            processLeftMost(nodePtr->rightChildPtr, replacementItem, replacementCount);
            nodePtr->item = replacementItem;
            nodePtr->count = replacementCount;
        }
    }
    void NgramTree::processLeftMost(TreeNode *& nodePtr, string& treeItem, int& count){
        if(nodePtr->leftChildPtr == nullptr){
            treeItem = nodePtr->item;
            count = nodePtr->count;
            TreeNode *delPtr = nodePtr;
            nodePtr = nodePtr->rightChildPtr;
            delPtr->rightChildPtr = nullptr;
            delete delPtr;
        }
        else{
            processLeftMost(nodePtr->leftChildPtr, treeItem, count);
        }
    }
    void NgramTree::deleteNgram(const string& ngram){
        TreeNode* node = nullptr;
        bool exist = retrieveItem(root, ngram, node);           //retrieveItem function assign the node variable to actual node in tree
        if(exist){
            deleteItem(root, ngram);
        }
        else{
            cout<< "Item is not in the tree" << endl;
        }
    }
    void NgramTree::copyTree(TreeNode* treePtr, TreeNode *& newTreePtr)const{
        //preorder traversal
        if(treePtr != nullptr){
            //copy node
            newTreePtr = new TreeNode(treePtr->item, nullptr, nullptr);
            if(newTreePtr == nullptr){
                cout<< "Cannot allocate memory" << endl;
            }
            copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
            copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
        }
        else{
            newTreePtr = nullptr; //copy empty tree
        }
    }
    bool NgramTree::isEmpty() const{
        return (root == nullptr);
    }
