/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Rollback
 */
#include "GenStack.h"
#include "Transaction.h"

class Rollback{

public:
  Rollback(); //constructor
  void push(Transaction t); //push adds a transaction to the stack
  Transaction pop(); //pop remove the transaction from the top off


private:
  GenStack<Transaction>* m_stack; //stack

};
