
#include "Rollback.h"

Rollback::Rollback(){
  m_stack = new GenStack<Transaction>(5);
}
