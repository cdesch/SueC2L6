//
// Created by cj on 4/12/15.
//

#ifndef SUEC2A4_TREE_DATABASE_HPP
#define SUEC2A4_TREE_DATABASE_HPP


#include "date.hpp"
#include "person.hpp"
#include "state.hpp"
#include <fstream>
#include <sstream>
#include "tree.hpp"
#include "treeNode.hpp"


class TreeDatabase{

protected:
    Tree<Person>* people;
    Tree<State>* states;

public:

    int numberOfRecordsCounted = 0;
    TreeDatabase(){
        this->people = new Tree<Person>();
        this->states = new Tree<State>();
        this->states->setEnforceUniqueItems(true);
    }

    ~TreeDatabase(){

        delete this->people;
        delete this->states;

    }

    void readfile(string filename){
        this->numberOfRecordsCounted = 1;

        ifstream infile(filename); //Open the file
        string str; // Declares a string and is used for temporary storage
        if (infile.is_open()){
            while (getline(infile,str)){
                string dateString;
                string ssnString;
                string firstName;
                string lastName;
                string stateString;

                string token;
                stringstream stringStream(str);

                //Get Birthday
                if (getline(stringStream, token, ' ')){
                    dateString = token;
                }
                //Get SSN
                if (getline(stringStream, token, ' ')){
                    ssnString = token;
                }
                //Get First Name
                if (getline(stringStream, token, ' ')){
                    firstName = token;
                }
                //Get Last Name
                if (getline(stringStream, token, ' ')){
                    lastName = token;
                }
                //Get State
                if (getline(stringStream, token, ' ')){
                    stateString = token;
                }
                //cout << "Birthdate: " << dateString << " ssn: " << ssnString << " firstname: " << firstName << " lastname: " << lastName << " state: " << stateString << endl;
                Date* birthdate = new Date(dateString); //Creates a new date object

                State* state = new State(stateString); //creating a new state
                //cout << stateString << endl;
                state = this->states->insert(state)->getData(); //add it to the list BUT if there is already a state of the same name in it, return that state instead

                Person* person = new Person(ssnString, firstName, lastName, birthdate, state);
                state->addPerson(person);
                this->people->insert(person);

                this->numberOfRecordsCounted ++;

            }
            infile.close();
        }
        else{
            cout << "Error: Unable to open file" << endl;
        }
    }

    Tree<Person>* getPeople(){
        return this->people;
    }

    Tree<State>* getStates(){
        return this->states;
    }

    void listStates(){
        this->states->print();
    }
    
    void listPeople(){
        this->people->print();
    }

    void listPeopleInState(string stateAbrev){

        State* newState = new State(stateAbrev);
        State* state = this->states->find(newState)->getData();
        if(state){
            cout << "State: " << state->getState() << " # of people: " <<  state->getPeople()->getSize() << endl;
            state->getPeople()->print();

        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }

    Person* findPerson(string firstName, string lastName){
        Person* newPerson = new Person(firstName, lastName);
        return this->findPerson( newPerson);
    }

    Person* findPerson(string ssn){
        Person* newPerson = new Person(ssn); //Uses Null Object Pattern
        return this->findPersonSSNRec(this->people->getRoot(), newPerson);
    }
    
    Person *findPersonSSNRec(TreeNode<Person>*node, Person* person){
        if(node == NULL){
            return NULL;
        }
        if(node->getData()->getSsn() == person->getSsn()){
            return node->getData();
        }
        Person* leftSide = findPersonSSNRec(node->getLeft(), person);
        Person* rightSide = findPersonSSNRec(node->getRight(), person);
        
        if(leftSide){
            return leftSide;
        }else if(rightSide){
            return rightSide;
        }else{
            return NULL;
        }
    }

    Person* findPerson(Person* person){
        TreeNode<Person> *personNode = this->people->find(person);
        if(personNode){
            return personNode->getData();
        }else{
            return NULL;
        }
    }

    void findOldest(string stateAbrev){
        State* newState = new State(stateAbrev);
        State* stateObject = this->states->find(newState)->getData();
        if(stateObject){
            TreeNode<Person>*personNode = stateObject->getPeople()->getRoot();
            
            Person* oldest = findOldestRec(personNode);
            cout << "The oldest person in " << stateAbrev << " is  ";
            oldest->printInfo();
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }
    
    Person* findOldestRec(TreeNode<Person>* node){
        
        if(node == NULL){
            return new Person("00000000", new Date(2015,4,22));
        }
        Person* leftSide = findOldestRec(node->getLeft());
        Person* rightSide = findOldestRec(node->getRight());
        if(*node->getData()->getBirthday() < *leftSide->getBirthday() &&
           *node->getData()->getBirthday() < *rightSide->getBirthday() ){
            return node->getData();
        }else{
            if(* leftSide->getBirthday() < *rightSide->getBirthday()){
                return leftSide;
            }else{
                return rightSide;
            }
        }
        
    }

    
    void findYoungest(string stateAbrev){
        State* newState = new State(stateAbrev);
        State* stateObject = this->states->find(newState)->getData();
        if(stateObject){
            TreeNode<Person>*personNode = stateObject->getPeople()->getRoot();

            Person* youngest = findYoungestRec(personNode);
            cout << "The youngest person in " << stateAbrev << " is  ";
            youngest->printInfo();
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }

    Person* findYoungestRec(TreeNode<Person>* node){

        if(node == NULL){
            return new Person("00000000", new Date(1800,1,1));
        }
        Person* leftSide = findYoungestRec(node->getLeft());
        Person* rightSide = findYoungestRec(node->getRight());
        if(*node->getData()->getBirthday() > *leftSide->getBirthday() &&
           *node->getData()->getBirthday() > *rightSide->getBirthday() ){
            return node->getData();
        }else{
            if(* leftSide->getBirthday() > *rightSide->getBirthday()){
                return leftSide;
            }else{
                return rightSide;
            }
        }
        
    }
    
    State* findState(string stateAbreviation){
        State* newState = new State(stateAbreviation);
        TreeNode<State>*stateNode = this->states->find(newState);
        if(stateNode){
            return stateNode->getData();
        }else{
            return NULL;
        }
    }
    //move ssn oldstate newstate
    void movePerson(string ssn, string oldStateString, string newStateString){
        Person* person = this->findPerson(ssn);
        State* oldState = this->findState(oldStateString);
        State* newState = this->findState(newStateString);
        if(person == NULL){
            cout << " -- " << ssn << " is not in the list of people" << endl;
        }else if (oldState == NULL){
            cout << " -- " << oldStateString << " is not in the list of states (old state)" << endl;
        }else if (newState == NULL){
            cout << " -- " << newStateString << " is not in the list of states (new state)" << endl;
        }else if (*person->getState() != *oldState){
            cout << " -- " << person->getFirstName() << " " << person->getLastName() << " does not live in " << oldState->getState() << endl;
        }
        else{

            //setting the person's state to the new state
            person->setState(newState);
            //remove the person from the old states linked list but preserve the person data
            TreeNode<Person>* personNode = oldState->getPeople()->find(person);
            oldState->getPeople()->remove(personNode, true);
            //add the person to the new states data
            newState->getPeople()->insert(person);
        }
    }
    
    void movePerson(Person* person, string oldStateString, string newStateString){
        this->movePerson(person->getSsn(),   oldStateString,  newStateString);
    }
    
    void mergeStates(string stateString1, string stateString2){
        State* state1 = this->findState(stateString1);
        State* state2 = this->findState(stateString2);
        if(state1 == NULL){
            cout << " -- " << stateString1 << " is not in the list of states" << endl;
        }else if (state2 == NULL){
            cout << " -- " << stateString2 << " is not in the list of states" << endl;
        }else{
            mergeIntoState(state1->getPeople()->getRoot(), state2);
        }
    }

    void mergeIntoState(TreeNode<Person>*node, State* newState){
        if(node == NULL){
            return;
        }
        newState->getPeople()->insert(node->getData());
        mergeIntoState(node->getLeft(), newState);
        mergeIntoState(node->getRight(),newState);
    }

};

#endif //SUEC2A4_TREE_DATABASE_HPP
