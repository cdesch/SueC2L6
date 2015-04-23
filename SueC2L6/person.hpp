//
// Created by cj on 4/2/15.
//

#ifndef SUEC2A4_PERSON_HPP
#define SUEC2A4_PERSON_HPP

#include "date.hpp"
#include "state.hpp"

//**************************
//  Class Person
//**************************
class Person {

private:
    string lastName;
    string firstName;
    string ssn;
    Date* birthday;
    State* state;

public:
    //Constructor
    Person(); //Default Constructor
    Person(string ssn, string firstName, string lastName, Date* birthday, State* state);
    Person(string ssn, string firstName, string lastName, string birthday, State* state);
    Person(string ssn);
    Person(string firstName, string lastName);
    ~Person(); //Deconstructor

    //Member Functions//
    void printName();
    void printInfo(); //Print Name (first and last), SSN, Birthdate
    void printInfoInline();
    long age();     //Calculate the age of the person based on the birthdate

    //Setters and Getters

    //GETTERS//
    string getSsn() const;
    string getFirstName() const;
    string getLastName() const;
    Date* getBirthday() const;
    State* getState();

    //SETTERS//
    void setSsn(string ssn);
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setBirthday(Date *birthday);      //Overloaded!!
    void setBirthday(string birthday);    //Overloaded!!
    void setState(State* state);


    bool operator==(const Person& object){
        if((this->getLastName() == object.getLastName() && this->getFirstName() == object.getFirstName()) || this->getSsn() == object.getSsn()){
            return true;
        }else{
            return false;
        }
    }

    bool operator!=(const Person& object){
        if((this->getLastName() == object.getLastName() && this->getFirstName() == object.getFirstName()) || this->getSsn() == object.getSsn()) {
            return false;
        }else{
            return true;
        }
    }

    bool operator>(const Person& object){
        if(this->getSsn() > object.getSsn()) {
            return true;
        }else{
            return false;
        }
    }

    bool operator<(const Person& object){
        if(this->getSsn() < object.getSsn()) {
            return true;
        }else{
            return false;
        }
    }

};
//Default Constructor
Person::Person(){
    delete this->birthday;
    this->birthday = NULL;
    //delete this->state; //Dont need to delete. The Database Object will take care of that
    this->state = NULL;
}

//Constructor with params
Person::Person(string ssn, string firstName, string lastName, Date* birthday, State* state){
    this->ssn = ssn;
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = birthday;
    this->state = state;
}

Person::Person(string ssn, string firstName, string lastName, string birthday, State* state){
    this->ssn = ssn;
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = new Date(birthday);
    this->state =  state;
}

Person::Person(string ssn){
    this->ssn = ssn;
    this->firstName = "John121";
    this->lastName = "Deere121";
    this->birthday = new Date("02021965");
    this->state =  new State("RANDOM");
}

Person::Person( string firstName, string lastName){
    this->ssn = "000000000";
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = new Date("02021965");
    this->state =  new State("RANDOM");
}

//Deconstructor
Person::~Person(){
}

//Member Functions//
//Prints full name
void Person::printName(){
    printf("%s %s \n", firstName.c_str(), lastName.c_str());
}

void Person::printInfo(){
    
    printf("SSN: %s ", ssn.c_str());
    printf(" First Name: %s ", firstName.c_str());
    printf(" Last Name: %s ", lastName.c_str());
    printf(" Birthdate (DDMMYYYY): ");
    birthday->printInfoInline();
    printf(" State: %s\n", this->getState()->getState().c_str());
    /*
    printf("SSN: %s \n", ssn.c_str());
    printf("First Name: %s \n", firstName.c_str());
    printf("Last Name: %s \n", lastName.c_str());
    printf("Birthdate (DDMMYYYY): ");
    birthday->printInfo();
    printf("State: %s\n", this->getState()->getState().c_str());
     */
}

void Person::printInfoInline(){
    printf("SSN: %s ", ssn.c_str());
    printf(" First Name: %s ", firstName.c_str());
    printf(" Last Name: %s ", lastName.c_str());
    printf(" Birthdate (DDMMYYYY): ");
    birthday->printInfoInline();
    printf(" State: %s\n", this->getState()->getState().c_str());
}

long Person::age(){
    //This function computes the age to the nearest year.
    int age;
    age = 2014 - int(birthday->getYear());
    return age;
}

//Getters//
string Person::getSsn() const{
    return this->ssn; //Type of long
}
string Person::getFirstName() const{
    return this->firstName;
}
string Person::getLastName() const{
    return this->lastName;
}
Date* Person::getBirthday() const{
    return this->birthday;
}

State* Person::getState() {
    return this->state;
}

//Setters//
void Person::setSsn(string ssn){
    this->ssn = ssn;
}
void Person::setFirstName(string firstName){
    this->firstName = firstName;
}
void Person::setLastName(string lastName){
    this->lastName = lastName;
}

//Overloading -- two different means to the same end.
void Person::setBirthday(Date* birthdate){
    this->birthday = birthdate;
}
void Person::setBirthday(string b){
    this->birthday = new Date(b);
}
void Person::setState(State* state){
    this->state = state;
}

#endif //SUEC2A4_PERSON_HPP
