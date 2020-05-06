//Rollback
#include "GenStack.h"
#include "Transaction.h"

class Rollback{

public:
  Rollback();
  void push(Transaction t);
  Transaction pop();


private:
  GenStack<Transaction>* m_stack;

};
