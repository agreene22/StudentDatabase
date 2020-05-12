/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Person header file which methods and member variables
 */
#include <string>

using namespace std;

class Person{

public:
  // constructors
  Person();
  Person(int id, string name, string level);

  //Accessors
  int getID();
  string getName();
  string getLevel();

  bool isStudent();

protected:
  // member variables
  int m_ID;
  string m_name;
  string m_level;
  bool m_isStudent;

};
