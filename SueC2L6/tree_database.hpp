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
                state = this->states->insert(state)->getData(); //add it to the list BUT if there is already a state of the same name in it, return that state instead

                Person* person = new Person(ssnString, firstName, lastName, birthdate, state);
                state->addPerson(person);
                this->people->insert(person);

                //person->printInfo();
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
    /*

    Person* findPerson(string firstName, string lastName){
        Person* newPerson = new Person(firstName, lastName);
        return this->findPerson(newPerson);
    }*/


    /*
    Person* findPerson(string ssn){
        Person* newPerson = new Person(ssn);
        return this->findPerson(newPerson);
    }*/
    /*

    Person* findPerson(Person* person){
        ListNode<Person>* newPersonNode = new ListNode<Person>(person);
        ListNode<Person>* personNode = this->people->find(newPersonNode);
        if(personNode){
            return personNode->getData();
        }else{
            return NULL;
        }
    }*/

    /*

    void findOldest(string stateAbrev){
        State* newState = new State(stateAbrev);
        ListNode<State>* newStateNode = new ListNode<State>(newState);
        ListNode<State>* stateNode = this->states->find(newStateNode);
        if(stateNode){
            State *headState = stateNode->getData();
            List<Person>* peopleInState = headState->getPeople();
            cout << "State: " << headState->getState() << endl;
            ListNode<Person>* currentPerson = peopleInState->getHead();
            Person* oldest = currentPerson->getData();
            while(currentPerson){
                //cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
                cout << "    - " ;
                if(currentPerson->getNext() != NULL){
                    if(*currentPerson->getData()->getBirthday() < *oldest->getBirthday()){
                        oldest = currentPerson->getData();
                    }
                }
                currentPerson->getData()->printInfoInline();
                currentPerson = currentPerson->getNext();
            }

            cout << "The oldest person in " << stateAbrev << " is  ";
            oldest->printInfoInline();
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }

    }
*/
    /*
    void findYoungest(string stateAbrev){
        State* newState = new State(stateAbrev);
        ListNode<State>* newStateNode = new ListNode<State>(newState);
        ListNode<State>* stateNode = this->states->find(newStateNode);

        if(stateNode){
            State *headState = stateNode->getData();
            List<Person>* peopleInState = headState->getPeople();
            cout << "State: " << headState->getState() << endl;
            ListNode<Person>* currentPerson = peopleInState->getHead();
            Person* youngest = currentPerson->getData();
            while(currentPerson){
                //cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
                cout << "    - " ;
                if(currentPerson->getNext() != NULL){
                    if(*currentPerson->getData()->getBirthday() > *youngest->getBirthday()){
                        youngest = currentPerson->getData();
                    }
                }
                currentPerson->getData()->printInfoInline();
                currentPerson = currentPerson->getNext();
            }

            cout << "The youngest person in " << stateAbrev << " is  ";
            youngest->printInfoInline();
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }
     */
/*
    State* findState(string stateAbreviation){
        State* newState = new State(stateAbreviation);
        ListNode<State>* newStateNode = new ListNode<State>(newState);
        ListNode<State>* stateNode = this->states->find(newStateNode);
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
            cout << " -- " << oldStateString << " is not in the list of states" << endl;
        }else if (newState == NULL){
            cout << " -- " << newStateString << " is not in the list of states" << endl;
        }else if (*person->getState() != *oldState){
            cout << " -- " << person->getFirstName() << " " << person->getLastName() << " does not live in " << oldState->getState() << endl;
        }
        else{

            //setting the person's state to the new state
            person->setState(newState);
            //remove the person from the old states linked list but preserve the person data
            oldState->getPeople()->findAndDeleteNode(person, true);
            //add the person to the new states data
            newState->getPeople()->addNode(person);
            newState->getPeople()->sort();


        }

    }



    //FIXME: and make me effecient
    void movePerson(Person* person, string oldStateString, string newStateString){
        this->movePerson(person->getSsn(),   oldStateString,  newStateString);
    }

    void mergeStates(string stateString1, string stateString2, string newStateString){

        State* state1 = this->findState(stateString1);
        State* state2 = this->findState(stateString2);
        State* newState = this->findState(newStateString);
        if(state1 == NULL){
            cout << " -- " << stateString1 << " is not in the list of states" << endl;
        }else if (state2 == NULL){
            cout << " -- " << stateString2 << " is not in the list of states" << endl;
        }else if (newState != NULL){
            cout << " -- " << newStateString << " is already a state and cannot be created." << endl;
        }else{


            while(state1->getPeople()->getSize() > 0){
                Person* person = state1->getPeople()->findNodeAtIndex(0)->getData();
                this->movePerson(person, stateString1, stateString2);
            }

            state2->setState(newStateString);
            this->states->findAndDeleteNode(state1);
            state2->getPeople()->sort();

        }

    }
    */


};

#endif //SUEC2A4_TREE_DATABASE_HPP
