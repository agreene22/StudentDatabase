#include "Faculty.h"


Faculty::Faculty(){
  m_ID = 0;
  m_name = "";
  m_level = "";
  m_department = "";
  m_advisees = new DoublyLinkedList<int>;//does this pointer arithmetic work out?
}

Faculty::Faculty(int id, string name, string level, string dept, DoublyLinkedList<int>* advisees){
  m_ID = id;
  m_name = name;
  m_level = level;
  m_department = dept;
  m_advisees = advisees;//are we going to pass in a linkedList?
}

Faculty::~Faculty(){
  delete m_advisees;
}

string Faculty::getDepartment(){
  return m_department;
}

void Faculty::addAdvisee(Student* s){
  m_advisees->insertBack(s->getID());
}

DoublyLinkedList<int>* Faculty::getAdvisees(){
  return m_advisees;
}

void Faculty::printAdvisees(){
  m_advisees->printList();
}

void Faculty::removeAdvisee(int studentID){
  m_advisees->remove(studentID);
}
