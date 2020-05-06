#include <string>

using namespace std;

class Person{

public:
  Person();
  Person(int id, string name, string level);
  ~Person();

  //Accessors
  int getID();
  string getName();
  string getLevel();

  bool isStudent();

protected:
  int m_ID;
  string m_name;
  string m_level;
  bool m_isStudent;

};
