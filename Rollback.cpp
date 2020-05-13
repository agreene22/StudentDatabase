/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Rollback 
 */
#include "Rollback.h"

Rollback::Rollback(){ //constructor
  m_stack = new GenStack<Transaction>(5);
}

void Rollback::push(Transaction t){ //pushing a transaction onto the stack
  m_stack->push(t);
}

Transaction Rollback::pop(){ //popping the transaction off the stack
  return m_stack->pop();
}
