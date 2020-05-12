/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Person implementation file which defines methods and member variables
 */

#include "Person.h"

// default constructor
Person::Person(){
  m_ID = 0;
  m_name = "";
  m_level = "";
  m_isStudent = false;
}

// overloaded constructor
Person::Person(int id, string name, string level){
  m_ID = id;
  m_name = name;
  m_level = level;
  m_isStudent = false;
}

// Accessor which returns integer representing ID
int Person::getID(){
  return m_ID;
}

// Accessor which returns string representing name
string Person::getName(){
  return m_name;
}

// Accessor which returns string representing level
string Person::getLevel(){
  return m_level;
}

// Returns a boolean representing if the person is a student
bool Person::isStudent(){
  return m_isStudent;
}
