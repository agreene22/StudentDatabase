#include "Person.h"

using namespace std;

class Student : public Person {

public:
  Student();
  Student(int id, string name, string level, string major, double gpa, int advisor);
  ~Student();

  //accessors
  string getMajor();
  double getGPA();
  int getAdvisor();

  void setAdvisor(int advisorID);


private:
  string m_major;
  double m_GPA;
  int m_advisor;

};
