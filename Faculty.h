//#include "Person.h"
#include "DoublyLinkedList.h"
#include "Student.h"

using namespace std;

class Faculty : public Person {

public:
  Faculty();
  Faculty(int id, string name, string level, string dept, DoublyLinkedList<int>* advisees);
  //advisees needs to be changed to a linkedList
  ~Faculty();

  string getDepartment();

  DoublyLinkedList<int>* getAdvisees();
  void addAdvisee(int studentID);
  void printAdvisees();
  void removeAdvisee(int studentID);


private:
  string m_department;
  // int m_temp; // what's this?
  DoublyLinkedList<int>* m_advisees;

};
