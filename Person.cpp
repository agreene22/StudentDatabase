#include "Person.h"

Person::Person(int id, string name, string level){
  m_ID = id;
  m_name = name;
  m_level = level;
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
