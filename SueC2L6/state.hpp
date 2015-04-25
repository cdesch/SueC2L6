//
// Created by cj on 4/2/15.
//

#ifndef SUEC2A4_STATE_HPP
#define SUEC2A4_STATE_HPP

#include <string>
#include <iostream>
#include "tree.hpp"
#include "person.hpp"

using namespace std;

//start

class Person; //Forward Declartion of Person class
class State{

protected:
    string stateAbbreviation;
    Tree<Person>* people;

public:
    
    State(){
        this->stateAbbreviation = "";
        this->people = new Tree<Person>();
    }

    State(string abbreviation){
        this->stateAbbreviation = abbreviation;
        this->people = new Tree<Person>();
    }

    ~State(){
        this->people->deleteWithoutData();
        delete this->people;
        this->people = NULL;
    };

    //Setters & Getters
    void setState(string abbreviation){
        this->stateAbbreviation = abbreviation;
    }

    string getState() const{
        return this->stateAbbreviation;
    }

    void addPerson(Person* person){
        this->people->insert(person);
    }

    Tree<Person>* getPeople(){
        return this->people;
    }
    
    string getPrintData(){
        return this->stateAbbreviation;
    }

    void printInfo(){
        cout << this->stateAbbreviation << endl;
    }

    bool operator==(const State& object){
        if(this->getState() == object.getState()){
            return true;
        }else{
            return false;
        }
    }

    bool operator!=(const State& object){
        if(this->getState() == object.getState()){
            return false;
        }else{
            return true;
        }
    }

    bool operator>(const State& object){
        //if(this->getState().compare(object.getState()) < 0) {
        if(this->getState() > object.getState()){
            return true;
        }else{
            return false;
        }
    }

    bool operator<(const State& object){
        //if(this->getState().compare(object.getState()) > 0) {
        if(this->getState() < object.getState()){
            return true;
        }else{
            return false;
        }
    }

};

#endif //SUEC2A4_STATE_HPP
