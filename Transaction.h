//transaction class
//#include "Student.h"
#include "Faculty.h"
#include <string>

class Transaction{

public:
  Transaction(string type, Person data);
  string getPersonType();
  string getTransactionType();


private:
  string m_transactionType;
  Person m_person;

};
