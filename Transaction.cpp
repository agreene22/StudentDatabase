/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Transaction
 */
#include "Transaction.h"

using namespace std;

Transaction::Transaction(){//default constructor
  m_transactionType = "";
  m_person = Person();
}

Transaction::Transaction(string type, Person data){//overloaded constructor
  //cout << "in transaction constructor2" << endl;
  m_transactionType = type;
  m_person = data;
  //cout << "in transaction constructor2" << endl;
}

string Transaction::getPersonType(){//returns a string of what type the person is
  if(m_person.isStudent()){
    return "Student";
  }
  return "Faculty";
}

string Transaction::getTransactionType(){//returns whether the transaction is insert or delete
  return m_transactionType;
}

Person Transaction::getPerson(){//returns the person member variable of the transaction
  cout << "Inside get person1" << endl;
  return m_person;
}

void Transaction::Speak(){//speak method which helped us debug
  cout << "Name" << m_person.getName() << endl;
  cout << "ID" << m_person.getID() << endl;
  cout << "Level" << m_person.getLevel() << endl;
}
