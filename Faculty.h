#include "Person.h"
#include "DoublyLinkedList.h"
#include "Student.h"

using namespace std;

class Faculty : Person{

public:
  Faculty();
  Faculty(int id, string name, string level, string dept, int advisees);
  //advisees needs to be changed to a linkedList
  ~Faculty();

  string getDepartment();


  void addAdvisee(Student* s);
  void printAdvisees();


private:
  string m_department;
  int m_temp;
  DoublyLinkedList<int>* m_advisees;

};
