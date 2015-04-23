//
// Created by cj on 4/11/15.
//

#ifndef SUEC2A4_TREENODE_HPP
#define SUEC2A4_TREENODE_HPP

#include <string>
using namespace std;

template<class Element>
class TreeNode{
protected:
    Element* data;
    TreeNode<Element>* left;
    TreeNode<Element>* right;

public:

    TreeNode(){
        this->data = NULL;
        this->left = NULL;
        this->right = NULL;

    }

    TreeNode(Element* data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;

    }

    TreeNode(Element* data, TreeNode<Element>* left,TreeNode<Element>* right ){
        this->data = data;
        this->left = left;
        this->right = right;
    }

    ~TreeNode(){

    }


    //Deletes node and data
    void deleteWithData(){

        if(this->data){
            delete this->data;
            this->data = NULL;
        }

    }

    void deleteCascading(bool preserveData){
        this->deleteNode(preserveData);
        if(this->left){
            this->left->deleteCascading(preserveData);
            delete this->left;
            this->left = NULL;
        }

        if(this->right){
            this->right->deleteCascading(preserveData);
            delete this->right;
            this->right = NULL;
        }
    }

    void deleteNode(bool preserveData){

        if(preserveData){
            this->deleteWithoutData();
        }else{
            this->deleteWithData();
        }
    }

    //deletes node and preserves data
    void deleteWithoutData(){
        this->data = NULL;
    }

    void setLeft(TreeNode<Element>* left){
        this->left = left;
    }

    void setRight(TreeNode<Element>* right){
        this->right = right;
    }
    void setData(Element* data){
        this->data = data;
    }

    TreeNode<Element>* getLeft(){
        return this->left;
    }

    TreeNode<Element>* getRight(){
        return this->right;
    }

    Element* getData(){
        return this->data;
    }

};

#endif //SUEC2A4_TREENODE_HPP
