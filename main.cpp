
// #include "GenStack.h"
// #include "Student.h"
// #include "DoublyLinkedList.h"
// #include "BST.h"
#include "Simulation.h"

int main(int argc, char** argv){

  Simulation* sim = new Simulation();
  int choice = 0;

  sim->setTrees();

  do {
    cout << endl;
    choice = sim->Menu();
    sim->Simulate(choice);
  } while(true);


  return 0;
}
