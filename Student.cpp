/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Student.cpp file to define methods
 */

#include "Student.h"

using namespace std;

// default constructor
Student::Student(){
  m_ID = 0; // initialize variables to default values
  m_name = "";
  m_level = "";
  m_major = "";
  m_GPA = 4.0;
  m_advisor = 0;
  m_isStudent = true;
}

// overloaded constructors
Student::Student(int id, string name, string level, string major, double gpa, int advisor){
  m_ID = id; // initialize variables to overloaded values
  m_name = name;
  m_level = level;
  m_major = major;
  m_GPA = gpa;
  m_advisor = advisor;
  m_isStudent = true;
}

Student::Student(int id, string name, string level){
  m_ID = id;
  m_name = name;
  m_level = level;
  m_major = "";
  m_GPA = 0.0;
  m_advisor = 0;
  m_isStudent = true;
}

// Accessor method to return string for major
string Student::getMajor(){
  return m_major;
}

// Accessor method to return double representing GPA
double Student::getGPA(){
  return m_GPA;
}

// Accessor method to return integer representing Advisor ID number
int Student::getAdvisor(){
  return m_advisor;
}

// Mutator method to assign the student an advisor
void Student::setAdvisor(int advisorID){ // takes in an integer
  m_advisor = advisorID;
}

// operator overloaders
bool operator==(Student& studentOne, Student& studentTwo){
  return (studentOne.getID() == studentTwo.getID());
}

bool operator<(Student& studentOne, Student& studentTwo){
  return (studentOne.getID() < studentTwo.getID());
}

bool operator>(Student& studentOne, Student& studentTwo){
  return (studentOne.getID() > studentTwo.getID());
}
