#include "Person.h"

Person::Person(){
  m_ID = 0;
  m_name = "";
  m_level = "";
  m_isStudent = false;
}

Person::Person(int id, string name, string level){
  m_ID = id;
  m_name = name;
  m_level = level;
  m_isStudent = false;
}

Person::~Person(){

}

int Person::getID(){
  return m_ID;
}

string Person::getName(){
  return m_name;
}

string Person::getLevel(){
  return m_level;
}

bool Person::isStudent(){
  return m_isStudent;
}
