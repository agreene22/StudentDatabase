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
  void addStudent(Student s);
  void addFaculty(Faculty f);
  string SerializeStudents(TreeNode<Student>* root);
  // string SerializeFaculty(TreeNode<Faculty> root);
  // void deserializeStudent();
  // void Rollback(); \
private:
  BST<Student>* masterStudent;
  BST<Faculty>* masterFaculty;
  Rollback* rb;
};
