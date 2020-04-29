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


private:
  int m_ID;
  string m_name;
  string m_level;

};
