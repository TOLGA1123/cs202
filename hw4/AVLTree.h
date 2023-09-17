/*
* Title: Balanced Search Trees
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 4
* Description: AVLTree header
*/
#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <math.h>
using namespace std;
    class TreeNode{
        private:            //deletion not implemented so no need for balance factor variables
        TreeNode();
        TreeNode(const string item, TreeNode* left = nullptr, TreeNode* right = nullptr);
        string word;
        int frequency;
        TreeNode* rightChildPtr;
        TreeNode* leftChildPtr;
        friend class AVLTree;
    };
    class AVLTree{
        public:
            AVLTree();          //+
            ~AVLTree();         //+
            void addWord(const string& word);           //+
            void generateTree(const string& fileName);  //+
            void printHeight(ofstream& fileName);       //+
            void printTotalWordCount(ofstream& fileName);
            void printWordFrequencies(ofstream& fileName);
            void printMostFrequent(ofstream& fileName);
            void printLeastFrequent(ofstream& fileName);
            void printStandartDeviation(ofstream& fileName);

            void destroyTree(TreeNode *& treePtr);          //+
            TreeNode* insertItem(TreeNode *& treePtr, const string& newItem);       //+?        maybe change this
            bool retrieveItem(TreeNode * treePtr, string word, TreeNode *& treeItem);   //+
            bool isEmpty() const;                           //+
            TreeNode* rotateLeft(TreeNode*& treePtr);            //+
            TreeNode* rotateRight(TreeNode*& treePtr);           //+
            int getHeight(TreeNode* treePtr);               //+
            int getBalance(TreeNode* treePtr);              //+
            int getTotalWordCount(TreeNode* treePtr);
            void printWordFrequenciesHelper(TreeNode* treePtr, ofstream& fileName);
            TreeNode* getMostFrequent(TreeNode* treePtr);
            TreeNode* getLeastFrequent(TreeNode* treePtr);
            int getTotalFrequencies(TreeNode* treePtr);
            int getSquareSum(TreeNode* treePtr, int mean);
            string printItemsWithSameFrequency(TreeNode* treePtr, const int frequncy);
        private:
        TreeNode* root;
    };

#endif // NGRAMTREE_H
