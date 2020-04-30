#include <iostream>
#include "BST.h"
#include "Faculty.h"
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
  void addStudent();
  void deleteStudent(int studentID);
  void addFaculty();
  void deleteFaculty(int id); // not sure if we should specify in variable name type of person's ID
  void changeAdvisor(int studentID, int facultyID);
  void removeAdvisee(int studentID, int facultyID);
  void Rollback(); // not sure what this should take in
private:
  BST<Student>* studentTree; // should this be a pointer/of pointers to students
  BST<Faculty>* facultyTree;

};
