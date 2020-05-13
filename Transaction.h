/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Transaction
 */
#include "Faculty.h"
#include <string>

class Transaction{

public:
  Transaction();//default constructor
  Transaction(string type, Person data);//overloaded constructor
  string getPersonType();//returns a string of what type the person is
  string getTransactionType();//returns whether the transaction is insert or delete
  Person getPerson();//returns whether the transaction is insert or delete
  void Speak();//method that helps debug


private:
  string m_transactionType;//string which holds info on whether the transaction was an insert or delete
  Person m_person;//contains the person involved in the transaction

};
