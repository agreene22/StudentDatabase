/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Faculty implementation file which inherits Person and declares methods and member variables
 */
#include "Faculty.h"

// defualt constructor
Faculty::Faculty(){
  m_ID = 0; // initialize variables to default values
  m_name = "";
  m_level = "";
  m_department = "";
  m_advisees = new DoublyLinkedList<int>;
  m_isStudent = false;
}

// overloaded constructors
Faculty::Faculty(int id, string name, string level, string dept, DoublyLinkedList<int>* advisees){
  m_ID = id;
  m_name = name;
  m_level = level;
  m_department = dept;
  m_advisees = advisees;
  m_isStudent = false;
}

Faculty::Faculty(int id, string name, string level){
  m_ID = id;
  m_name = name;
  m_level = level;
  m_department = "";
  m_advisees = new DoublyLinkedList<int>;
  m_isStudent = false;
}

Faculty::Faculty(int id, string name, string level, string dept){
  m_ID = id;
  m_name = name;
  m_level = level;
  m_department = dept;
  m_advisees = new DoublyLinkedList<int>;
  m_isStudent = false;
}

// destructor
Faculty::~Faculty(){
  delete m_advisees;
}

// Accessor returns string representing department
string Faculty::getDepartment(){
  return m_department;
}

// Takes in an integer representing student ID and adds it to linked list of advisees
void Faculty::addAdvisee(int studentID){
  m_advisees->insertBack(studentID);
}

// Returns Linked List pointer of advisees
DoublyLinkedList<int>* Faculty::getAdvisees(){
  return m_advisees;
}

// Displays list of advisees to user
void Faculty::printAdvisees(){
  m_advisees->printList();
}

// Removes an advisee given student ID from linked list
void Faculty::removeAdvisee(int studentID){
  m_advisees->remove(studentID);
}

// overloaded operators
bool operator==(Faculty& facultyOne, Faculty& facultyTwo){
  return (facultyOne.getID() == facultyTwo.getID());
}

bool operator<(Faculty& facultyOne, Faculty& facultyTwo){
  return (facultyOne.getID() < facultyTwo.getID());
}

bool operator>(Faculty& facultyOne, Faculty& facultyTwo){
  return (facultyOne.getID() > facultyTwo.getID());
}
