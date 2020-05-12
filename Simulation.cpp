#include "Simulation.h"
#include <fstream>

Simulation::Simulation(){
  masterStudent = new BST<Student>();
  masterFaculty = new BST<Faculty>();
  rb = new Rollback();
}

Simulation::~Simulation(){
  delete masterStudent;
  delete masterFaculty;
  delete rb;
}

void Simulation::setTrees(){ // This method might not be necessary and could just be our defualt constructor
  ifstream inFS;
  int studentID = 0;
  string name = "";
  string level = "";
  string major = "";
  double gpa = 0.0;
  int advisorID = 0;
  string department = "";

  inFS.open("studentTable.txt");
  if(!inFS.is_open()){
    // continue;
  }else{
    while(!inFS.eof()){
      // Student s = Student();
      inFS >> studentID;
      inFS >> name;
      inFS >> level;
      inFS >> major;
      inFS >> gpa;
      inFS >> advisorID;
      if(!inFS.fail()){
        Student s(studentID,name,level,major,gpa,advisorID);
        masterStudent->insert(s.getID(),s);
      }
    }
  }
  inFS.close();

  inFS.open("facultyTable.txt");
  if(!inFS.is_open()){
    // continue;
  }else{
    while(!inFS.eof()){
      inFS >> advisorID;
      inFS >> name;
      inFS >> level;
      inFS >> department;
      if(!inFS.fail()){
        Faculty f(advisorID,name,level,department);
        masterFaculty->insert(f.getID(),f);
        inFS >> studentID; // HMMMMM
        // How are the list of advisees being passed?
        f.addAdvisee(studentID);
      }
    }
  }
  inFS.close();
  // Student s1(50,"Anna","Sophomore", "CompSci", 4.0, 5); // I'm not sure if the trees should hold objects or pointers (ik it would be a bitch to change them all to pointers)
  // masterStudent->insert(s1.getID(),s1);
}

int Simulation::Menu(){ // should come up with more choices because he said we'd get more credit lol
  int choice = 0;

  cout << "Enter the number corresponding to the desired task: " << endl;
  cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
  cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
  cout << "3. Find and display student information given the students id" << endl;
  cout << "4. Find and display faculty information given the faculty id" << endl;
  cout << "5. Given a student’s id, print the name and info of their faculty advisor" << endl;
  cout << "6. Given a faculty id, print ALL the names and info of his/her advisees." << endl;
  cout << "7. Add a new student" << endl;
  cout << "8. Delete a student given the id" << endl;
  cout << "9. Add a new faculty member" << endl;
  cout << "10. Delete a faculty member given the id." << endl;
  cout << "11. Change a student’s advisor given the student id and the new faculty id." << endl;
  cout << "12. Remove an advisee from a faculty member given the ids" << endl;
  cout << "13. Rollback" << endl;
  cout << "14. Exit" << endl;

  cin >> choice;
  while(choice < 1 || choice > 14){
    cout << "Invalid entry. Please enter a valid task number" << endl;
    cin >> choice;
  }

  return choice;
}

void Simulation::Simulate(int choice){
  int id = 0;
  int studentID = 0;
  int facultyID = 0;
  switch (choice) {
    case 1:
      printStudents();
      break;
    case 2:
      printFaculty();
      break;
    case 3:
      cout << "Enter the ID of the student: " << endl;
      cin >> id;
      findStudent(id);
      break;
    case 4:
      cout << "Enter the ID of the faculty member: " << endl;
      cin >> id;
      findFaculty(id);
      break;
    case 5:
      cout << "Enter the student ID number: " << endl;
      cin >> studentID;
      getStudentAdvisor(studentID);
      break;
    case 6:
      cout << "Enter the faculty ID number: " << endl;
      cin >> facultyID;
      getAdvisorList(facultyID);
      break;
    case 7:
    {
      Student s1 = addStudent();
      Transaction t1 = Transaction("delete", s1);
      rb->push(t1);
      break;
    }
    case 8:
    {
      cout << "Enter the student ID number: " << endl;
      cin >> studentID;
      Student s2 = getStudent(studentID);
      Transaction t2 = Transaction("add", s2);
      rb->push(t2);
      deleteStudent(studentID);
      break;
    }
    case 9:
    {
      Faculty f1 = addFaculty();
      Transaction t3 = Transaction("delete", f1);
      rb->push(t3);
      break;
    }
    case 10:
    {
      cout << "Enter the faculty ID number: " << endl;
      cin >> facultyID;
      Faculty f2 = getFaculty(facultyID);
      Transaction t4 = Transaction("add", f2);
      rb->push(t4);
      deleteFaculty(facultyID);
      break;
    }
    case 11:
    {
      cout << "Enter the student ID number: " << endl;
      cin >> studentID;
      cout << "Enter the new advisor faculty ID number: " << endl;
      cin >> facultyID;
      changeAdvisor(studentID, facultyID);
      break;
    }
    case 12:
    {
      cout << "Enter the student ID number: " << endl;
      cin >> studentID;
      cout << "Enter the faculty ID number: " << endl;
      cin >> facultyID;
      removeAdvisee(studentID, facultyID);
      break;
    }
    case 13:
    {
      Transaction t5 = rb->pop();
      Person p5 = t5.getPerson();
      if(t5.getPersonType() == "Student"){
        Student & s5 = static_cast<Student&>(p5);
        if(t5.getTransactionType() == "add"){
          addStudent(s5);
          cout << "Rollback delete from student database." << endl;
        }else{
          deleteStudent(p5.getID());
          cout << "Rollback insert from student database." << endl;
        }
      }else{
        Faculty & f5 = static_cast<Faculty&>(p5);
        if(t5.getTransactionType() == "add"){
          addFaculty(f5);
          cout << "Rollback delete from faculty database." << endl;
        }else{
          deleteFaculty(p5.getID());
          cout << "Rollback insert from faculty database." << endl;
        }
      }


      break;
    }
    case 14:
      cout << "Exiting program." << endl;
      //here we need to serialize everything to the file
      exit(0); // will exit the program
      break;
    default:
      cout << "Invalid input please try again." << endl;
      exit(1);
      break;
  }
}

void Simulation::printStudents(){
  TreeNode<Student>* root = masterStudent->getRoot();
  masterStudent->printTree(root); // needs to take in root but im not quite sure how to do that
}

void Simulation::printFaculty(){
  TreeNode<Faculty>* root = masterFaculty->getRoot();
  masterFaculty->printTree(root);
}

Student Simulation::getStudent(int id){
  Student currStudent = masterStudent->search(id);
  return currStudent;
}

Faculty Simulation::getFaculty(int id){
  Faculty currFaculty = masterFaculty->search(id);
  return currFaculty;
}

void Simulation::findStudent(int id){
  Student currStudent = masterStudent->search(id);
  // cout << id << endl; // should we display their ID number? bc its given
  cout << currStudent.getName() << endl;
  cout << currStudent.getLevel() << endl;
  cout << currStudent.getMajor() << endl;
  cout << currStudent.getGPA() << endl;
  cout << currStudent.getAdvisor() << endl;
}

void Simulation::findFaculty(int id){
  Faculty currFaculty = masterFaculty->search(id);
  // cout << id << endl; // should we display their ID number? bc its given
  cout << currFaculty.getName() << endl;
  cout << currFaculty.getLevel() << endl;
  cout << currFaculty.getDepartment() << endl;
  cout << "Faculty's Advisees: " << endl;
  currFaculty.printAdvisees(); // will print their ID numbers
}

void Simulation::getStudentAdvisor(int studentID){
  int advisorID = 0;
  Student currStudent = masterStudent->search(studentID);
  advisorID = currStudent.getAdvisor();
  findFaculty(advisorID);
}

void Simulation::getAdvisorList(int facultyID){
  Faculty currFaculty = masterFaculty->search(facultyID); // all these searches seem inefficient but I'm not sure how else to do it
  DoublyLinkedList<int>* students = currFaculty.getAdvisees();
  for(int i = 0; i < students->getSize(); ++i){
    int studentID = students->accessAtPos(i);
    Student currStudent = masterStudent->search(studentID);
    findStudent(currStudent.getID());
  }
}

Student Simulation::addStudent(){
  int studentID = 0;
  string name = "";
  string level = "";
  string major = "";
  double gpa = 0.0;
  int advisor = 0;

  cout << "Enter the following information: " << endl;
  cout << "Student ID: " << endl;;
  cin >> studentID;
  cout << "Name: " << endl;
  cin >> name;
  cout << "Level: (Freshman, sophomore, junior, senior)" << endl;
  cin >> level;
  cout << "Major: " << endl;
  cin >> major;
  cout << "GPA: " << endl;
  cin >> gpa;
  cout << "Advisor ID number: " << endl;
  cin >> advisor;

  Student newStudent(studentID,name,level,major,gpa,advisor);
  masterStudent->insert(studentID,newStudent);
}

void Simulation::deleteStudent(int studentID){
  Student currStudent = masterStudent->search(studentID);
  Faculty advisor = masterFaculty->search(currStudent.getAdvisor());
  advisor.removeAdvisee(studentID);
  masterStudent->deleteNode(studentID);
  // do we need to null the student's node to the advisor before we delete the student?
}

Faculty Simulation::addFaculty(){
  int facultyID = 0;
  string name = "";
  string level = "";
  string department = "";
  DoublyLinkedList<int>* advisees;
  int studentID = 0;

  cout << "Enter the following information: " << endl;
  cout << "Faculty ID: " << endl;;
  cin >> facultyID;
  cout << "Name: " << endl;
  cin >> name;
  cout << "Level: " << endl;
  cin >> level;
  cout << "Department: " << endl;
  cin >> department;
  while(studentID != -1){
    cout << "Advisee ID numbers (enter -1 when done): ";
    cin >> studentID;
    advisees->insertBack(studentID);
  }

  Faculty newFaculty(facultyID,name,level,department,advisees);
  masterFaculty->insert(facultyID,newFaculty);
}

void Simulation::deleteFaculty(int facultyID){
  Faculty currFaculty = masterFaculty->search(facultyID);
  DoublyLinkedList<int>* advisees = currFaculty.getAdvisees();
  for(int i = 0; i < advisees->getSize(); ++i){
    int studentID = advisees->removeFront();
    Student currStudent = masterStudent->search(studentID);
    if(facultyID == masterFaculty->getRoot()->getKey()){
      int advisorID = masterFaculty->getRootLeftChild()->getKey();
      currStudent.setAdvisor(advisorID);
    }else{
      int advisorID = masterFaculty->getRoot()->getKey();
      currStudent.setAdvisor(advisorID);
    }
  }
  masterFaculty->deleteNode(facultyID);
}

void Simulation::changeAdvisor(int studentID, int facultyID){
  Student currStudent = masterStudent->search(studentID);
  int prevAdvisorID = currStudent.getAdvisor();
  Faculty prevAdvisor = masterFaculty->search(prevAdvisorID);
  prevAdvisor.removeAdvisee(studentID);
  currStudent.setAdvisor(facultyID);
  Faculty newAdvisor = masterFaculty->search(facultyID);
  newAdvisor.addAdvisee(studentID);
}

void Simulation::removeAdvisee(int studentID, int facultyID){
  Faculty advisor = getFaculty(facultyID);
  advisor.removeAdvisee(studentID);
  Student currStudent = getStudent(studentID);
  if(facultyID == masterFaculty->getRoot()->getKey()){
    int advisorID = masterFaculty->getRootLeftChild()->getKey();
    currStudent.setAdvisor(advisorID);
  }else{
    int advisorID = masterFaculty->getRoot()->getKey();
    currStudent.setAdvisor(advisorID);
  }
}

void Simulation::addStudent(Student s){
  masterStudent->insert(s.getID(),s);
}

void Simulation::addFaculty(Faculty f){
  masterFaculty->insert(f.getID(),f);
}

string Simulation::SerializeStudents(TreeNode<Student> root){
  if(root == NULL){
    return "";
  }
  String leftSerialized = Serialize(root.left);
  String rightSerialized = Serialize(root.right);
  return root.value + leftSerialized + rightSerialized;
}

// string Simulation::SerializeFaculty(TreeNode<Faculty> root){
//   if(root == NULL){
//     return "";
//   }
//   String leftSerialized = Serialize(root.left);
//   String rightSerialized = Serialize(root.right);
//   return root.value + leftSerialized + rightSerialized;
// }
