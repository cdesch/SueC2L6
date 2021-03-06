//
// Created by cj on 4/11/15.
//

#ifndef SUEC2A4_TREE_HPP
#define SUEC2A4_TREE_HPP


#include "treeNode.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>

using namespace std;

template<class Element>
class Tree {

protected:

    TreeNode<Element> *root;
    long size;
    bool enforceUniqueItems;

public:
    Tree() {
        this->root = NULL;
        this->size = 0;
        this->enforceUniqueItems = false;
    };

    Tree(TreeNode<Element> *root) {
        this->root = root;
        this->size = this->findSize(root);
        this->enforceUniqueItems = false;
    }

    Tree(TreeNode<Element> *root, int size) {
        this->root = root;
        this->size = size;
        this->enforceUniqueItems = false;
    }

    ~Tree() {
    }
    
    long heightOfTree(){
        return heightOfTree(this->root);
    }
    
    long heightOfTree(TreeNode<Element> *node){
        //If there is no element, return 0
        if(!node){
            return 0;
        }else{
            //find high of the left and right subtrees
            long leftHeight = heightOfTree(node->getLeft());
            long rightHeight = heightOfTree(node->getRight());
            
            return (leftHeight > rightHeight) ? (leftHeight+1) : (rightHeight + 1);
            /*
             //Equivalent to the line above
            if(leftHeight > rightHeight){
                return leftHeight + 1;
            }else{
                return rightHeight + 1;
            }*/
        }
    }
    
    void printTree(){
        long height = this->heightOfTree();
        cout << "Tree: "<< endl;
        for(long i = 1; i <= height; i++){
            printLevel(this->root, i);
            cout << endl;
        }
    }
    
    void printLevel(TreeNode<Element> *node, long level){
        if(!node){
            return;
        }
        if (level == 1){
            cout << node->getData()->getPrintData() << " ";
        }else if(level > 1){
            printLevel(node->getLeft(), level - 1);
            printLevel(node->getRight(), level - 1);
        }
    }
                      

    long findSize(TreeNode<Element> *node){

        long leftChildren = 0;
        long rightChildren = 0;
        if (node->getLeft() != NULL){
            leftChildren = findSize(node->getLeft());
        }
        if (node->getRight() != NULL){
            rightChildren = findSize(node->getRight());
        }

        return 1 + rightChildren + leftChildren;
    }

    void deleteWithData() {
        if (this->root) {
            delete this->root;
            this->root = NULL;
            this->size = 0;
        }
    }

    void deleteWithoutData() {
        if (this->root) {
            this->root->deleteWithoutData();
            delete this->root;
            this->root = NULL;
            this->size = 0;
        }
    }

    TreeNode<Element> *find(Element* data){
        TreeNode<Element>* node = this->find(this->root, data);
        if(node){
            return node;
        }else{
            return NULL;
        }
    }
    
    TreeNode<Element> *find(TreeNode<Element> *node, Element *data) {
        
        if (!node) {
            return node;
        }
        
        if (*node->getData() == *data) {
            return node;
        }
        
        if (*node->getData() > *data) {
            return find(node->getLeft(), data);
        } else {
            return find(node->getRight(), data);
        }
    }

    TreeNode<Element> * insert(Element *data) {
        if (this->enforceUniqueItems) {
            TreeNode<Element> * aNode = this->find(data);

            if(aNode){
                return aNode;
            }
        }
        
        this->insert(this->root, data);
        return this->find(data);
    }

    TreeNode<Element> * insert(TreeNode<Element> *node, Element *data) {

        if(!this->root){
            this->root = new TreeNode<Element>(data);
            this->size ++;
            return this->root;
        }
        
        if (!node) {
            TreeNode<Element> * newNode = new TreeNode<Element>(data);
            this->size ++;
            return newNode;
        }else if (*node->getData() >= *data) {
            node->setLeft(insert(node->getLeft(), data));
        } else {
            node->setRight(insert(node->getRight(), data));
        }
        return node;
    }
    
    void print(){
        this->print(this->root);
    }
    
    void print(TreeNode<Element>*node){
        if(node == NULL){
            return;
        }
        
        print(node->getLeft());
        node->getData()->printInfo();
        print(node->getRight());
    }
    
    void printUnsorted(){
        this->printUnsorted(this->root);
    }
    
    void printUnsorted(TreeNode<Element>*node){
        if(node == NULL){
            return;
        }
        node->getData()->printInfo();
        printUnsorted(node->getLeft());
        printUnsorted(node->getRight());
    }

    //Setters and Getters
    void setRoot(TreeNode<Element> *node) {
        this->root = node;
    }

    TreeNode<Element> *getRoot() {
        return this->root;
    }

    void setEnforceUniqueItems(bool enforcement) {
        this->enforceUniqueItems = enforcement;
    }

    bool getEnforceUniqueItems() {
        return this->enforceUniqueItems;
    }

    long getSize() const {
        return this->size;
    }
   
    bool remove(TreeNode<Element> *node){
        return this->remove(node, false);
    }
    
    bool remove(TreeNode<Element> *node, bool preserveData){
        if(this->root == NULL){
            return false;
        }else{
            //Is the node we want to delete the root node
            if(*this->root->getData() == *node->getData()){
                TreeNode<Element> * tempNode = new TreeNode<Element>();
                tempNode->setLeft(this->root);
                TreeNode<Element> * removedNode = this->root->remove(node, tempNode);
                this->root = tempNode->getLeft();
                if(removedNode != NULL){
                    if(!preserveData){
                        delete removedNode->getData();
                    }
                    delete removedNode;
                    this->size --;
                    return true;
                }else{
                    return false;
                }
                
            }else{
                TreeNode<Element> * nodeToRemove = this->root->remove(node, NULL);
                if(nodeToRemove != NULL){
                    if(!preserveData){
                        delete nodeToRemove->getData();
                    }
                    delete nodeToRemove;
                    this->size --;
                    return true;
                }else{
                    return false;
                }
                
            }
        }
        
    }
  
};

#endif //SUEC2A4_TREE_HPP
