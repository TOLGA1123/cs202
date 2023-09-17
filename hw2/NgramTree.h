/*
* Title: Trees
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 2
* Description: NgramTree header
*/
#ifndef NGRAMTREE_H
#define NGRAMTREE_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;
    class TreeNode{
    private:
        TreeNode();
        TreeNode(const string item, TreeNode* left = nullptr, TreeNode* right = nullptr);
        string item;
        int count;
        TreeNode* rightChildPtr;
        TreeNode* leftChildPtr;
        friend class NgramTree;
    };
    class NgramTree {
    public:
    NgramTree();
    ~NgramTree();
    void addNgram( const string& ngram );
    int getTotalNgramCount() const;
    bool isComplete() const;
    bool isFull() const;
    void generateTree( const string& fileName, const int n );


    void deleteNgram(const string& ngram);
    void destroyTree(TreeNode *& treePtr);
    void insertItem(TreeNode *& treePtr, const string& newItem);
    bool retrieveItem(TreeNode * treePtr, string ngram, TreeNode *& treeItem);
    void deleteItem(TreeNode *& treePtr, const string& itemToDelete);
    void deleteNodeItem(TreeNode *& nodePtr);
    void processLeftMost(TreeNode *& nodePtr, string& treeItem, int& count);
    void countNgramHelper(TreeNode * treePtr,int &total) const;
    bool isFullHelper(TreeNode* treePtr) const;
    bool isCompleteHelper(TreeNode* treePtr, int index, int noOfNodes) const;
    int countNodes(TreeNode * treePtr) const;
    void printInorder(TreeNode * treePtr, ostream& out) const;
    bool isEmpty() const;

    void copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const;         //not used for copy constructor and assignment operator overload
    private:
    TreeNode* root;
    friend ostream& operator<<(ostream& out, const NgramTree& tree);
};
#endif // NGRAMTREE_H
