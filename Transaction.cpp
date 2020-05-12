#include "Transaction.h"

using namespace std;

Transaction::Transaction(){
  m_transactionType = "";
  m_person = Person();
}

Transaction::Transaction(string type, Person data){
  m_transactionType = type;
  m_person = data;
  // cout << "in constructor" << endl;
}

string Transaction::getPersonType(){
  if(m_person.isStudent()){
    return "Student";
  }
  return "Faculty";
}

string Transaction::getTransactionType(){
  return m_transactionType;
}

Person Transaction::getPerson(){
  return m_person;
}
