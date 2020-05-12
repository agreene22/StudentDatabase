/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Student header file which inherits Person and declares methods and member variables
 */

#include "Person.h"

using namespace std;

class Student : public Person {

public:
  Student(); // constructors
  Student(int id, string name, string level, string major, double gpa, int advisor);
  Student(int id, string name, string level);

  //accessors
  string getMajor();
  double getGPA();
  int getAdvisor();

  // aux functions
  void setAdvisor(int advisorID);
  Person isStudent();

private:
  string m_major; // member variables
  double m_GPA;
  int m_advisor;

};
