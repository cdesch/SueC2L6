//
//  main.cpp
//  SueC2L6
//
//  Created by cj on 4/22/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//

#include <iostream>
#include "date.hpp"
#include "person.hpp"
#include "state.hpp"
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include "tree_database.hpp"
#include "tree.hpp"
#include "treeNode.hpp"

//TODO: error "find larry brown"
using namespace std;

enum COMMAND { EXIT_PROGRAM, READ, STATES, LIST, OLDEST, YOUNGEST, FIND, MOVE, MERGE, ERROR};
void testDateClass(){
    Date* date = new Date(2015,4,2);
    assert(date->getYear() == 2015);
    assert(date->getMonth() == 4);
    assert(date->getDay() == 2);
}

void testDateComparisonOperators(){
    
    Date* date1 = new Date("02021965");
    Date* date2 = new Date("24101947");
    Date* date3 = new Date("16061930");
    Date* date4 = new Date("13021922");
    
    assert(*date1 > *date2);
    assert(*date2 < *date1);
    assert(!(*date3 > *date2));
    assert(*date4 < *date1);
    
}

void testPersonClass(){
    Date* date = new Date(2015,4,2);
    State* state = new State("NY");
    Person* person = new Person("00000000", "MyFirstName", "MyLastName", date, state);
    
    assert(person->getSsn() == "00000000" );
    assert(person->getFirstName() == "MyFirstName" );
    assert(person->getLastName() == "MyLastName" );
    
    Person* person1 = new Person("00000001", "MyFirstName", "MyLastName", date, state);
    Person* person2 = new Person("00000002", "MyFirstName", "MyLastName", date, state);
    Person* person3 = new Person("00000003", "MyFirstName", "MyLastName", date, state);
    Person* person4 = new Person("00000004", "MyFirstName", "MyLastName", date, state);
    
    assert(*person1 < *person2);
    assert(*person2 > *person1);
    assert(!(*person2 < *person1));
    assert(*person4 > *person2);
    assert(!(*person1 > *person4));
    assert(*person1 < *person3);
    
}

void testStateClass(){
    
    State* newyork = new State("NY");
    State* newyork1 = new State("NY");
    State* newjersey = new State("NJ");
    
    assert( *newyork == *newyork1);
    assert( *newyork != *newjersey);
    
    string NY = "NY";
    string NJ = "NJ";
    assert(NY > NJ);
    assert( *newyork > *newjersey);
    assert( *newjersey < *newyork);
    assert(!(*newjersey > *newyork));
    assert(!(*newyork < *newjersey));
}



void testTreeNodes(string databaseLocation){
    
    TreeDatabase*  database = new TreeDatabase();
    ///database->readfile(databaseLocation);

    Date* date = new Date(2015,4,2);
    State* state = new State("NY");
    State* state8 = new State("OR");
    State* state1 = new State("NJ");
    State* state2 = new State("AL");
    State* state3 = new State("HI");
    State* state4 = new State("DC");
    State* state6 = new State("NY");
    State* state7 = new State("NY");
    State* state9 = new State("NH");
    

    database->getStates()->insert(state);
    assert(*database->getStates()->insert(state8)->getData() == *state8);
    database->getStates()->insert(state1);
    database->getStates()->insert(state2);
    database->getStates()->insert(state3);
    database->getStates()->insert(state4);
    assert(*database->getStates()->insert(state6)->getData() == *state);
    assert(*database->getStates()->insert(state7)->getData() == *state);
    State * aState = database->getStates()->insert(state9)->getData();
    aState->printInfo();
    //cout << "here" << endl;
    
    database->listStates();
    assert(*database->getStates()->insert(state9)->getData() == *state9);
    assert(database->getStates()->getSize() == 7);
    assert(*database->getStates()->find(state2)->getData() == *state2 );
    assert(*database->getStates()->find(state8)->getData() == *state8 );
    
    //database->listStates();
    
    Person* person = new Person("00100000", "NY MyFirstName1", "NY MyLastName1", date, state);
    Person* person1 = new Person("00030001", "NY MyFirstName2", "NY MyLastName2", date, state);
    Person* person2 = new Person("010000002", "NJ MyFirstName3", "NJ MyLastName3", date, state1);
    Person* person3 = new Person("00000103", "NJ MyFirstName4", "NJ MyLastName4", date, state1);
    Person* person4 = new Person("00100004", "MyFirstName5", "MyLastName5", date, state2);
    
    database->getPeople()->insert(person);
    database->getPeople()->insert(person1);
    database->getPeople()->insert(person2);
    database->getPeople()->insert(person3);
    database->getPeople()->insert(person4);

    assert(database->getPeople()->getSize() == 5);
    assert(*database->getPeople()->find(person1)->getData() == *person1 );
    //database->listPeople();
    
}

void testListPeopleInState(string databaseLocation){
    TreeDatabase*  database = new TreeDatabase();
    database->readfile(databaseLocation);

    database->getStates()->print();
    assert(database->getStates()->getSize() == 51);
    database->listPeopleInState("NY");
    database->listPeopleInState("NJ");
    database->listPeopleInState("DC");
    database->listPeopleInState("OR");

    database->findOldest("NY");
    database->findOldest("OR");
    database->findYoungest("NY");
    database->findYoungest("OR");
    
}

void testMergePeopleInState(string databaseLocation){
    TreeDatabase*  database = new TreeDatabase();
    database->readfile(databaseLocation);
    database->listPeopleInState("NY");
    database->listPeopleInState("NJ");
    database->mergeStates("NY", "NJ");
    database->listPeopleInState("NJ");
    database->listPeopleInState("NY");
    
}

void testRemoveNode(string databaseLocation){
    TreeDatabase*  database = new TreeDatabase();
    database->readfile(databaseLocation);
    database->listPeopleInState("NY");
    
    Date* date = new Date(2015,4,2);
    State* ny  = database->findState("NY");
    Person* newPerson = new Person("00100000", "NY MyFirstName1", "NY MyLastName1", date, ny);
    
    database->getPeople()->insert(newPerson);
    ny->getPeople()->insert(newPerson);
    
    database->listPeopleInState("NY");
    cout << endl;
    //ny->getPeople()->printUnsorted();
    
    TreeNode<Person>* newPersonNode = ny->getPeople()->find(newPerson);
    assert(ny->getPeople()->remove(newPersonNode));
    assert(!ny->getPeople()->remove(newPersonNode));
    cout << endl;
    //ny->getPeople()->printUnsorted();
    database->listPeopleInState("NY");
    
    Person* anotherPerson = database->findPerson("609690069"); //SSN: 609690069  First Name: Gallipoli  Last Name: DeMilt  Birthdate (DDMMYYYY): 10011925 State: NY
    TreeNode<Person>* anotherPersonNode = ny->getPeople()->find(anotherPerson);
    assert(ny->getPeople()->remove(anotherPersonNode));
    assert(!ny->getPeople()->remove(anotherPersonNode));

    database->listPeopleInState("NY");

}

void testMove(string databaseLocation){

    TreeDatabase*  database = new TreeDatabase();
    database->readfile(databaseLocation);

    //112200747
    database->listPeopleInState("OK");
    database->listPeopleInState("NY");
    //database->getStates()->printTree();
    //database->listStates();
    cout <<  "MOVE" << endl;
    database->movePerson("112200747", "OK","NY");
    cout <<  "MOVE ENDED" << endl;
    database->listPeopleInState("OK");
    database->listPeopleInState("NY");
    database->listPeopleInState("SD");
    database->listPeopleInState("NC");
    database->movePerson("122460462", "SD","NY");
    database->movePerson("123040628", "NC","NY");
    cout << "Move ended" << endl;
    database->listPeopleInState("NY");
    database->listPeopleInState("SD");
    database->listPeopleInState("NC");

}

void testHeightFunction(string databaseLocation){
    TreeDatabase*  database = new TreeDatabase();
    ///database->readfile(databaseLocation);

    State* state = new State("NY");
    State* state8 = new State("OR");
    State* state1 = new State("NJ");
    State* state2 = new State("AL");
    State* state3 = new State("HI");
    State* state4 = new State("DC");
    State* state6 = new State("NY");
    State* state7 = new State("NY");
    State* state9 = new State("NH");
    
    
    database->getStates()->insert(state);
    assert(database->getStates()->heightOfTree() == 1);
    
    database->getStates()->printTree();
    
    assert(*database->getStates()->insert(state8)->getData() == *state8);
    assert(database->getStates()->heightOfTree() == 2);
    database->getStates()->printTree();
    database->getStates()->insert(state1);
    assert(database->getStates()->heightOfTree() == 2);
        database->getStates()->printTree();
    database->getStates()->insert(state2);
    assert(database->getStates()->heightOfTree() == 3);
        database->getStates()->printTree();
    database->getStates()->insert(state3);
    assert(database->getStates()->heightOfTree() == 4);
        database->getStates()->printTree();
    database->getStates()->insert(state4);
    assert(*database->getStates()->insert(state6)->getData() == *state);
    assert(*database->getStates()->insert(state7)->getData() == *state);
    database->getStates()->insert(state9);
    cout << database->getStates()->heightOfTree() << endl;
        database->getStates()->printTree();
    
}

void testFind(string databaseLocation){
    TreeDatabase*  database = new TreeDatabase();
    database->readfile(databaseLocation);
    cout << "read database" << endl;
    
    Person* person = database->findPerson("161760131");
    assert(person);
    //person->printInfo();
    
    Person* person1 = database->findPerson("152720564");
    assert(person1);
    //person1->printInfo();
    
    Person* person2 = database->findPerson("163290682");
    assert(person2);
    //person2->printInfo();
    
}



vector<string> parseCommandString(string commandString){
    vector <string> arguments;
    
    string token;
    stringstream stringStream(commandString);
    
    while(getline(stringStream, token, ' ')){
        arguments.push_back(token);
    }
    
    if(arguments.size() == 0){
        arguments.push_back("ERROR");
    }
    return arguments;
}


COMMAND commandDetector(string s){
    
    
    //cout <<  s <<" is an operator "<<  endl;
    
    if(s == "exit" ){
        return EXIT_PROGRAM;
    }else if(s == "read" ){
        return READ;
    }else if(s == "states" ){
        return STATES;
    }else if(s == "list" ){
        return LIST;
    }else if (s == "oldest" ){
        return OLDEST;
    }else if (s == "youngest"){
        return YOUNGEST;
    }else if (s == "oldest" ){
        return OLDEST;
    }else if (s == "youngest") {
        return YOUNGEST;
    }else if (s == "find" ){
        return FIND;
    }else if (s == "move") {
        return MOVE;
    }else if (s == "merge") {
        return MERGE;
    }else{
        //cout << "Error" << endl;
        return ERROR;
    }
    
}


void commandLineInterpreter(){
    
    cout << "Enter a command:" << endl;
    int command = 100;
    string commandString;
    TreeDatabase* database;
    do{
        
        cout << "> ";
        std::getline(std::cin, commandString);
        vector<string> arguments = parseCommandString(commandString);
        COMMAND comm = commandDetector(arguments[0]);
        
        if(database == NULL && !(comm != READ || comm != EXIT_PROGRAM)){
            cout << "Error: There must be a data present prior to running commands against the database." << endl;
        }else{
            switch (comm){
                case READ:
                    cout << "READING" << endl;
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguements." << endl;
                        cout << "E.g. read /home/www/labs/152/dbfile1.txt" << endl;
                    }else{
                        database = new TreeDatabase();
                        database->readfile(arguments[1]);
                        cout << "Reading Complete" << endl;
                    }
                    
                    break;
                case STATES:
                    
                    cout << "States" << endl;
                    if(arguments.size()>=2 ){
                        cout << "Error: Illegal number of arguments. This command takes one arguement." << endl;
                        cout << "E.g. states" << endl;
                    }else{
                        database->listStates();
                    }
                    
                    break;
                case LIST:
                    
                    cout << "List" << endl;
                    
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. list FL" << endl;
                    }else{
                        database->listPeopleInState(arguments[1]);
                    }
                    
                    break;
                case OLDEST:
                    
                    cout << "OLDEST" << endl;
                    
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. oldest NY" << endl;
                    }else{
                        database->findOldest(arguments[1]);
                    }
                    
                    break;
                case YOUNGEST:
                    cout << "YOUNGEST" << endl;
                    
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. youngest NY" << endl;
                    }else{
                        database->findYoungest(arguments[1]);
                    }
                    
                    break;
                    
                case FIND:
                    cout << "FIND" << endl;
                    
                    if(arguments.size() != 3){
                        cout << "Error: Illegal number of arguments. This command takes three arguement." << endl;
                        cout << "E.g. find Larry Brown" << endl;
                    }else{
                        Person* person = database->findPerson(arguments[1], arguments[2]);
                        if(person){
                            cout << "  FOUND: " ;
                            person->printInfoInline();
                        }else{
                            cout << " -- " << arguments[1] << " " <<  arguments[2] << " is not in the list of people" << endl;
                        }
                    }
                    
                    break;
                    
                case MOVE:
                    
                    cout << "MOVE" << endl;
                    //FIXME: Insert in social security order
                    if(arguments.size() != 4){
                        cout << "Error: Illegal number of arguments. This command takes four arguement." << endl;
                        cout << "E.g. move 108690448 KS MD" << endl;
                    }else{
                        database->movePerson(arguments[1], arguments[2], arguments[3]);
                    }
                    
                    break;
                    
                case MERGE:
                    cout << "merge" << endl;
                    
                    if(arguments.size() != 3){
                        cout << "Error: Illegal number of arguments. This command takes three arguement." << endl;
                        cout << "E.g. merge NC SC" << endl;
                    }else{
                        database->mergeStates(arguments[1], arguments[2]);
                    }
                    break;
                case EXIT_PROGRAM:
                    command = 0;
                    cout << "EXITING" << endl;
                    break;
                    
                case ERROR:
                    cout<< "Error: Illegal Syntax in command" << endl;
                    
                    
                default:
                    cout<< "Error: Illegal Syntax in command" << endl;
            }
        }
        
    }while(command != 0);
    cout << "Final EXIT" << endl;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    string testDatabaseLocation = "/Users/cj/Desktop/dbfile1.txt";
    //testTreeNodes(testDatabaseLocation);
    //testListPeopleInState(testDatabaseLocation);
    //testMergePeopleInState(testDatabaseLocation);
    //testRemoveNode(testDatabaseLocation);
    //testFind(testDatabaseLocation);
    testMove(testDatabaseLocation);
    //testHeightFunction(testDatabaseLocation);
    //commandLineInterpreter();
    
    return 0;
}
