
#include "GenStack.h"
#include "Student.h"
#include "DoublyLinkedList.h"
#include "BST.h"

int main(int argc, char** argv){

  GenStack<Student*>* stack = new GenStack<Student*>();

  Student* myStudent = new Student();

  stack->push(myStudent);
  cout << stack->pop() << endl;

  return 0;
}
