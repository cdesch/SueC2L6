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
    
    
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    string testDatabaseLocation = "/Users/cj/Desktop/dbfile1.txt";
    testTreeNodes(testDatabaseLocation);
    testListPeopleInState(testDatabaseLocation);
    
    return 0;
}
