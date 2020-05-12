//transaction class
//#include "Student.h"
#include "Faculty.h"
#include <string>

class Transaction{

public:
  Transaction();
  Transaction(string type, Person data);
  string getPersonType();
  string getTransactionType();
  Person getPerson();
  void Speak();


private:
  string m_transactionType;
  Person m_person;

};
