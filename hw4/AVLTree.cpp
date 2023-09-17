/*
* Title: Balanced Search Trees
* Author: Tolga Han Arslan
* ID: 22003061
* Section: 1
* Assignment: 4
* Description: AVLTree source
*/
#include "AVLTree.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <math.h>
using namespace std;
    TreeNode::TreeNode(){
        this->word = "";
        this->frequency = 0;
        this->leftChildPtr = nullptr;
        this->rightChildPtr = nullptr;
    }
    TreeNode::TreeNode(const string word, TreeNode* left, TreeNode* right){
        this->word = word;
        this->frequency = 1;
        this->leftChildPtr = left;
        this->rightChildPtr = right;
    }
    AVLTree::AVLTree(){
        this->root = nullptr;
    }
    AVLTree::~AVLTree(){
        destroyTree(root);
    }
    void AVLTree::addWord(const string& word){
        TreeNode* node = nullptr;
        bool exist = retrieveItem(root, word, node);           //retrieveItem function assign the node variable to actual node in tree
        if(exist){
            node->frequency++;
        }
        else{                                                   //if it does not exist, node should still be nullptr
            this->root = insertItem(root, word);              // assign root here, otherwise it only inserts first word from the file
        }
    }
    TreeNode* AVLTree::insertItem(TreeNode *& treePtr, const string& newItem){   //insert new item + check for balance
        //first insert the item like a regular binary search tree
        if(treePtr == nullptr){
            //position of insertion found; insert after leaf
            treePtr = new TreeNode(newItem, nullptr, nullptr);
            //this part should be in the if
            if(treePtr == nullptr){
            cout << "Insertion failed" << endl;     //unsuccessful allocation
            }
            return treePtr;
        }
        else if(newItem < treePtr->word){    //search for left subtree
            treePtr->leftChildPtr = insertItem(treePtr->leftChildPtr, newItem);
        }
        else{                                           //search for right subtree
            treePtr->rightChildPtr = insertItem(treePtr->rightChildPtr, newItem);
        }
        //then check for balance at the insertion node and above path to the root
        int balance = getBalance(treePtr);      //left child height - right child height
                                //something might be wrong here
            //4 cases
            //Insertion into left subtree of left child of node n ---> single right rotation
            if(balance > 1 && newItem < treePtr->leftChildPtr->word){
                return rotateRight(treePtr);
            }
            //Insertion into right subtree of right child of node n ---> single left rotation
            if(balance < -1 && newItem > treePtr->rightChildPtr->word){
                return rotateLeft(treePtr);
            }
            //Insertion into right subtree of left child of node n ---> double left + right rotation
            if(balance > 1 && newItem > treePtr->leftChildPtr->word){
                treePtr->leftChildPtr = rotateLeft(treePtr->leftChildPtr);
                return rotateRight(treePtr);
            }
            //Insertion into left subtree of right child of node n ---> double right + left rotation
            if(balance < -1 && newItem < treePtr->rightChildPtr->word){
                treePtr->rightChildPtr = rotateRight(treePtr->rightChildPtr);
                return rotateLeft(treePtr);
            }
        return treePtr;
    }
    void AVLTree::destroyTree(TreeNode *& treePtr){
        if(treePtr != nullptr){
            destroyTree(treePtr->leftChildPtr);
            destroyTree(treePtr->rightChildPtr);
            delete treePtr;
            treePtr = nullptr;
        }
    }
    int AVLTree::getHeight(TreeNode* treePtr){
        if(treePtr == nullptr){
            return 0;
        }
        else{
            int leftHeight = getHeight(treePtr->leftChildPtr);
            int rightHeight = getHeight(treePtr->rightChildPtr);
            if(leftHeight > rightHeight){
                return leftHeight + 1;
            }
            else{
                return rightHeight + 1;
            }
        }
    }
    bool AVLTree::isEmpty() const{
        return (root == nullptr);
    }
    TreeNode* AVLTree::rotateLeft(TreeNode *& treePtr){
        //k1 is the treePtr         (k1, k2, a, b, c in the slides)
        TreeNode* k2 = treePtr->rightChildPtr;
        TreeNode* b = k2->leftChildPtr;
        k2->leftChildPtr = treePtr;
        treePtr->rightChildPtr = b;
        return k2;
    }
    TreeNode* AVLTree::rotateRight(TreeNode *& treePtr){
        //k2 is the treePtr (k1, k2, a, b, c in the slides)
        TreeNode* k1 = treePtr->leftChildPtr;
        TreeNode* b = k1->rightChildPtr;
        k1->rightChildPtr = treePtr;
        treePtr->leftChildPtr = b;
        return k1;
    }
    bool AVLTree::retrieveItem(TreeNode* treePtr, string word, TreeNode *& treeItem){
        if(treePtr == nullptr){
            return false;
        }
        else if(word == treePtr->word){
            treeItem = treePtr;
            return true;
        }
        else if(word < treePtr->word){
            return retrieveItem(treePtr->leftChildPtr, word, treeItem);
        }
        else{
            return retrieveItem(treePtr->rightChildPtr, word, treeItem);
        }
    }
    int AVLTree::getBalance(TreeNode* treePtr){
        if(treePtr == nullptr){
            return 0;
        }
        return getHeight(treePtr->leftChildPtr) - getHeight(treePtr->rightChildPtr);
    }
    void AVLTree::generateTree(const string& fileName) {
        string word, line;
        ifstream inputFile;
        inputFile.open(fileName.c_str());
        while (getline(inputFile, line)) {
            // Handle capital letters on the line
            for (int i = 0; i < (int) line.length(); i++) {
                if (isupper(line[i])) {
                    line[i] = tolower(line[i]);
                }
            }
            // Handle punctuations on the line
            for (int i = 0; i < (int) line.length(); i++) {             //something wrong in here node "the" with 4259 and 1 frequency exist if ispunct used
                if (!isalpha(line[i]) && !isdigit(line[i])) {     //maybe use !isalpha() to disregard numerical characters as well instead of ispunct
                    line[i] = ' ';
                }
            }
            // Process each word in the line
            istringstream iss(line);
            while (iss >> word) {
                addWord(word);
            }
        }
        inputFile.close();
    }
    void AVLTree::printHeight(ofstream& fileName){
        fileName << "Tree Height: " << this->getHeight(root) << endl;
    }
    void AVLTree::printTotalWordCount(ofstream& fileName){
        fileName << "Total Word Count: " << this->getTotalWordCount(root) << endl;
    }
    int AVLTree::getTotalWordCount(TreeNode* treePtr){
        if(treePtr == nullptr){
            return 0;
        }
        return 1 + getTotalWordCount(treePtr->rightChildPtr) + getTotalWordCount(treePtr->leftChildPtr);
    }
    void AVLTree::printWordFrequencies(ofstream& fileName){
        //uses inorder traversal to print frequencies of words in alphabetical order
        this->printWordFrequenciesHelper(root, fileName);
    }
    void AVLTree::printWordFrequenciesHelper(TreeNode* treePtr, ofstream& fileName){
        if(treePtr != nullptr){
            printWordFrequenciesHelper(treePtr->leftChildPtr, fileName);
            fileName << treePtr->word << ": " << treePtr->frequency << endl;
            printWordFrequenciesHelper(treePtr->rightChildPtr, fileName);
        }
    }
    void AVLTree::printMostFrequent(ofstream& fileName){
        TreeNode* mostFrequent = getMostFrequent(root);
        //in case of there are more than one most frequent(item with same frequency)
        int mostFrequency = mostFrequent->frequency;
        fileName << "Most frequent: " << printItemsWithSameFrequency(root, mostFrequency);
    }
    TreeNode* AVLTree::getMostFrequent(TreeNode* treePtr){
        if(treePtr == nullptr){
            return nullptr;
        }
        TreeNode* most = treePtr;
        TreeNode* left = getMostFrequent(treePtr->leftChildPtr);
        TreeNode* right = getMostFrequent(treePtr->rightChildPtr);
        // Compare the left child's frequency with the current most frequent node
        if (left != nullptr && left->frequency > most->frequency) {
            most = left;
        }

        // Compare the right child's frequency with the current most frequent node
        if (right != nullptr && right->frequency > most->frequency) {
            most = right;
        }
    return most;
    }
    void AVLTree::printLeastFrequent(ofstream& fileName){
        TreeNode* leastFrequent = getLeastFrequent(root);
        //in case of there are more than one most frequent(item with same frequency)
        int leastFrequency = leastFrequent->frequency;
        fileName << "Least frequent: " << printItemsWithSameFrequency(root, leastFrequency);
    }
    TreeNode* AVLTree::getLeastFrequent(TreeNode* treePtr){
        if(treePtr == nullptr){
            return nullptr;
        }
        TreeNode* least = treePtr;
        TreeNode* left = getLeastFrequent(treePtr->leftChildPtr);
        TreeNode* right = getLeastFrequent(treePtr->rightChildPtr);
        // Compare the left child's frequency with the current most frequent node
        if (left != nullptr && left->frequency < least->frequency) {
            least = left;
        }

        // Compare the right child's frequency with the current most frequent node
        if (right != nullptr && right->frequency < least->frequency) {
            least = right;
        }
    return least;
    }
    void AVLTree::printStandartDeviation(ofstream& fileName){
        double squareSum, standartDeviation, mean;
        int totalFrequencies = getTotalFrequencies(root);
        int wordCount = getTotalWordCount(root);
        if(wordCount == 0){
            fileName << "AVL tree is empty, cannot calculate standard deviation" << endl;
            return;
        }
        mean = (double) totalFrequencies / wordCount;
        squareSum = getSquareSum(root, mean);       // sum of (x - mean)^2
        standartDeviation = sqrt(squareSum / wordCount);
        fileName << "Standard Deviation: " << standartDeviation << endl;

    }
    int AVLTree::getTotalFrequencies(TreeNode* treePtr){
        if(treePtr == nullptr){
            return 0;
        }
        return treePtr->frequency + getTotalFrequencies(treePtr->leftChildPtr) + getTotalFrequencies(treePtr->rightChildPtr);
    }
    int AVLTree::getSquareSum(TreeNode* treePtr, int mean){
        if(treePtr == nullptr){
            return 0;
        }
        return pow((treePtr->frequency - mean), 2) + getSquareSum(treePtr->leftChildPtr, mean) + getSquareSum(treePtr->rightChildPtr, mean);
    }
    string AVLTree::printItemsWithSameFrequency(TreeNode* treePtr, const int frequency){
        string items = "";
        //inorder traversal
        if(treePtr != nullptr){
            items += printItemsWithSameFrequency(treePtr->leftChildPtr, frequency);
            if(treePtr->frequency == frequency){
                items += treePtr->word;
                items += " ";
                items += to_string(treePtr->frequency);
                items += "\n";
            }
            items += printItemsWithSameFrequency(treePtr->rightChildPtr, frequency);
        }
        return items;
    }
