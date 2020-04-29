#include "Student.h"

using namespace std;

Student::Student(){
  m_ID = 0;
  m_name = "";
  m_level = "";
  m_major = "";
  m_GPA = 4.0;//I wish
  m_advisor = 0;
}

Student::Student(int id, string name, string level, string major, double gpa, int advisor){
  m_ID = id;
  m_name = name;
  m_level = level;
  m_major = major;
  m_GPA = gpa;
  m_advisor = advisor;
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

void Student::setAdvisor(int advisorID){
  m_advisor = advisorID;
}
