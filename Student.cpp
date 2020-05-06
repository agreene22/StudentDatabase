#include "Student.h"

using namespace std;

Student::Student(){
  m_ID = 0;
  m_name = "";
  m_level = "";
  m_major = "";
  m_GPA = 4.0;//I wish
  m_advisor = 0;
  m_isStudent = true;
}

Student::Student(int id, string name, string level, string major, double gpa, int advisor){
  m_ID = id;
  m_name = name;
  m_level = level;
  m_major = major;
  m_GPA = gpa;
  m_advisor = advisor;
  m_isStudent = true;
}

Student::~Student(){

}

string Student::getMajor(){
  return m_major;
}

double Student::getGPA(){
  return m_GPA;
}

int Student::getAdvisor(){
  return m_advisor;
}

void Student::setAdvisor(int advisorID){ // should we do this or take in the advisor and then do getID and set it to that number
  m_advisor = advisorID;
}

bool operator==(Student& studentOne, Student& studentTwo){
  return (studentOne.getID() == studentTwo.getID());
}

bool operator<(Student& studentOne, Student& studentTwo){
  return (studentOne.getID() < studentTwo.getID());
}

bool operator>(Student& studentOne, Student& studentTwo){
  return (studentOne.getID() > studentTwo.getID());
}
