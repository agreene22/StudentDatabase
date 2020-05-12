
#include "Rollback.h"

Rollback::Rollback(){
  m_stack = new GenStack<Transaction>(5);
}

void Rollback::push(Transaction t){
  m_stack->push(t);
}

Transaction Rollback::pop(){
  return m_stack->pop();
}
