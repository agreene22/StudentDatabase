#include <string>

using namespace std;

class Person{

public:
  Person();
  ~Person();

  //Accessors
  int getID();
  string getName();
  string getLevel();


protected:
  int m_ID;
  string m_name;
  string m_level;

};
