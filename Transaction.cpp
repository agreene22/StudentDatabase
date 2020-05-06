#include "Transaction.h"

Transaction::Transaction(string type, Person data){
  m_transactionType = type;
  m_person = data;
}

string Transaction::getPersonType(){
  if(){//m_person.isStudent()){
    return "Student";
  }
  //return "Faculty";
}

string Transaction::getTransactionType(){
  return m_transactionType;
}
