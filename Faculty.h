/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Faculty header file which inherits Person and declares methods and member variables
 */

//#include "Person.h"
#include "DoublyLinkedList.h"
#include "Student.h"

using namespace std;

class Faculty : public Person {

public:
  // constructors
  Faculty();
  Faculty(int id, string name, string level);
  Faculty(int id, string name, string level, string dept);
  Faculty(int id, string name, string level, string dept, DoublyLinkedList<int>* advisees);
  // destructor
  ~Faculty();

  // accessor
  string getDepartment();

  // aux functions
  DoublyLinkedList<int>* getAdvisees();
  void addAdvisee(int studentID);
  void printAdvisees();
  void removeAdvisee(int studentID);


private:
  // member variables
  string m_department;
  DoublyLinkedList<int>* m_advisees;

};
