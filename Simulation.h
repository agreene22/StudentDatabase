/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Simulation class to create an instance of the BST from user file and run methods
 */

#include <iostream>
#include "BST.h"
#include "Rollback.h"
using namespace std;

class Simulation{
public:
  Simulation(); // constructor
  Simulation(BST<Student>* students, BST<Faculty>* facultys); // overloaded constructor
  ~Simulation(); // destructor

  void setTrees();

  // aux methods
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
  string serializeStudents(TreeNode<Student>* root);
  string SerializeFaculty(TreeNode<Faculty>* root);

private:
  // member variables
  BST<Student>* masterStudent; // Tree to hold students
  BST<Faculty>* masterFaculty; // Tree to hold faculty
  Rollback* rb;
};
