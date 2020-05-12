#include "Transaction.h"

using namespace std;

Transaction::Transaction(){
  m_transactionType = "";
  m_person = Person();
}

Transaction::Transaction(string type, Person data){
  //cout << "in transaction constructor2" << endl;
  m_transactionType = type;
  m_person = data;
  //cout << "in transaction constructor2" << endl;
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
  cout << "Inside get person1" << endl;
  return m_person;
}

void Transaction::Speak(){
  cout << "Name" << m_person.getName() << endl;
  cout << "ID" << m_person.getID() << endl;
  cout << "Level" << m_person.getLevel() << endl;
}
