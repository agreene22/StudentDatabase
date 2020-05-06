#include <iostream>
#include "BST.h"
//#include "Faculty.h"
#include "Rollback.h"
using namespace std;

class Simulation{
public:
  Simulation();
  ~Simulation();

  void setTrees();

  int Menu();
  void Simulate(int choice);

  void printStudents();
  void printFaculty();
  void findStudent(int id);
  void findFaculty(int id);
  void getStudentAdvisor(int studentID);
  void getAdvisorList(int facultyID);
  Student addStudent();
  void deleteStudent(int studentID);
  Faculty addFaculty();
  void deleteFaculty(int facultyID);
  void changeAdvisor(int studentID, int facultyID);
  Student getStudent(int id);
  Faculty getFaculty(int id);
  void removeAdvisee(int studentID, int facultyID);
  // void Rollback(); // not sure what this should take in
private:
  BST<Student>* studentTree; // should this be a pointer/of pointers to students
  BST<Faculty>* facultyTree; // I feel like I should've made them of pointers rather than just objects but now I'm in a bit deep lmao but we could still change it
  Rollback* rb = new Rollback();
};
