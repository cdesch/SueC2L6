//
// Created by cj on 4/11/15.
//

#ifndef SUEC2A4_TREE_HPP
#define SUEC2A4_TREE_HPP




#include "treeNode.hpp"
#include <iostream>

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

    long findSize(TreeNode<Element> *root){

        long leftChildren = 0;
        long rightChildren = 0;
        if (root->getLeft() != NULL){
            leftChildren = findSize(root->getLeft());
        }
        if (root->getRight() != NULL){
            rightChildren = findSize(root->getRight());
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
/*
    /////FIXME REMOVE
    Element *addNode(Element *data) {
        TreeNode<Element> *newNode = new TreeNode<Element>(data);
        TreeNode<Element> *returnedNode = this->addNode(newNode);
        return returnedNode->getData();
    }

     /////FIXME REMOVE
    TreeNode<Element> *addNode(TreeNode<Element> *node) {

        //If every node must be unique, lets check for that. If we find a duplicate node, return that node, if not return the inserted node.
        //In other words, to avoid duplicates, lets return an existing node or the new node.
        if (this->enforceUniqueItems) {
            TreeNode<Element> *myNode = this->isNodeInDataStructure(node);
            if (myNode) return myNode;
        }


        //TODO: Implement
        this->size++;
        return node;
    }
 */

    TreeNode<Element> *find(Element* data){
        TreeNode<Element>* node = this->find(this->root, data);
        if(node){
            return node;
        }else{
            return NULL;
        }
    }
    
    
    TreeNode<Element> *find(TreeNode<Element> *node, Element *data) {
        if (node == NULL) {
            return node;
        }
        if (*node->getData() == *data) {
            return node;
        }

        //FIXEME -- Test
        if (*node->getData() > *data) {
            return find(node->getLeft(), data);
        } else {
            return find(node->getRight(), data);
        }
    }

    //FIXME Return element inserted or null
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

        if(this->root == NULL){
            this->root = new TreeNode<Element>(data);
            this->size ++;
            return this->root;
        }
        
   
        
        if (node == NULL) {
            TreeNode<Element> * newNode = new TreeNode<Element>(data);
            this->size ++;
            return newNode;
        }

        else if (*node->getData() > *data) {
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

    TreeNode<Element> *getNode(int index) {
        //check if index it out of bounds
        if (index >= this->size || index < 0) {
            cout << "ERROR: Index is out of bounds" << endl;
            return NULL;
        }

        //TODO: determine if it is needed
        //it will never run this line
        return NULL;
    }

    long getSize() const {
        return this->size;
    }


    TreeNode<Element> *isNodeInDataStructure(TreeNode<Element> *node) {

        //TODO: implement

        //If the node is not found, return NULL.
        return NULL;
    }

    TreeNode<Element> *find(TreeNode<Element> *node) {
        return this->isNodeInDataStructure(node);
    }

    /*
    ListNode<Element>* findNodeAtIndex(int index){
        if(index < 0 || index >= this->size){
            cout << "ERROR: Index is out of bounds" << endl;
            return NULL;
        }
        int currentIndex = 0;

        ListNode<Element>* myCurrentNode = this->root;
        //FIXME: Can this be cleaned up?
        while(myCurrentNode){
            if(currentIndex == index){
                return myCurrentNode;
            }
            if(myCurrentNode->getNext() == NULL){
                return myCurrentNode;
            }else{
                currentIndex ++;
                myCurrentNode = myCurrentNode->getNext();
            }
        }
        return myCurrentNode;
    }
     */


    Element *findData(Element *data) {

        //TODO: implement
        //If the node is not found, return NULL.
        return NULL;
    }

    //Helper function for finding and deleting data
    void findAndDeleteNode(Element *data) {
        this->findAndDeleteNode(data, false);
    }

    //will find the ListNode but preserve the data in it but delete the node
    void findAndDeleteNode(Element *data, bool preserveData) {

    
        TreeNode<Element> *node = this->find(data);
        this->deleteNode(node, preserveData);
    }


    void deleteNode(TreeNode<Element> *node) {
        this->deleteNode(node, false);
    }

    void deleteNode(TreeNode<Element> *node, bool preserveData) {

        if (node == NULL) {
            cout << "Warning: Node can not equal null when deleting a listNode" << endl;
            return;
        }

        //use case if there is no elements in the list
        if (this->size == 0) {
            cout << "Warning: cannot remove node from empty list " << endl;
            return;
        }

        //use case if there is only one element in the list
        if (this->size == 1) {
            TreeNode<Element> *headNode = this->getRoot();
            if (*node->getData() == *node->getData()) {
                this->root->deleteNode(preserveData);
                delete this->root;
                this->root = NULL;

                this->size = 0;
                return;
            } else {
                cout << "Warning: nodes do match and cannot be removed" << endl;
                return;
            }
        }
/*
        //TODO: implement
        //Check if the node being removed is the first element
        if(*node->getData() == *this->head->getData()){
            
            ListNode<Element>* temp = this->head->getNext();
            this->head->deleteNode(preserveData);
            delete this->head;
            this->head = temp;
            this->size--;
            return;
        }
*/
    }
    
    bool remove(TreeNode<Element> *node){
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
                    delete removedNode;
                    this->size --;
                    return true;
                }else{
                    return false;
                }
                
            }else{
                TreeNode<Element> * nodeToRemove = this->root->remove(node, NULL);
                if(nodeToRemove != NULL){
                    //Fixme: preserve data
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
