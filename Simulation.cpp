#include "Simulation.h"
#include <fstream>
#include <sstream>

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

void Simulation::setTrees(){ 
  ifstream inFS;
  string student;
  int id;
  string name;
  string level;
  string major;
  double gpa;
  int advisorID;
  string department;


  inFS.open("studentTable.txt");
  if(!inFS.is_open()){
    // continue;
  }else{

    string currLine;
    while(getline(inFS,currLine)){
      stringstream  linestream(currLine);
      string stringID;
      string stringGPA;
      string stringAdvisor;
      getline(linestream,stringID,',');
      getline(linestream,name,',');
      getline(linestream,level,',');
      getline(linestream,major,',');
      getline(linestream,stringGPA,',');
      getline(linestream,stringAdvisor,'\n');

      id = stoi(stringID);
      gpa = stod(stringGPA);
      advisorID = stoi(stringAdvisor);
      Student s(id,name,level,major,gpa,advisorID);
      masterStudent->insert(id,s);
    }
    // while(!inFS.eof()){
    //   // Student s = Student();
    //   // inFS >> studentID;
    //   inFS >> student;
    //
    //
    //   // if(!inFS.fail()){
    //     inFS >> name;
    //   // }
    //
    //   inFS >> level;
    //   inFS >> major;
    //   inFS >> gpa;
    //   inFS >> advisorID;
    //   if(!inFS.fail()){
    //     cout << "here" << endl;
    //     Student s(studentID,name,level,major,gpa,advisorID);
    //     cout << "here 2" << endl;
    //     masterStudent->insert(s.getID(),s);
    //   }
    // }
  }
  inFS.close();

  inFS.open("facultyTable.txt");
  if(!inFS.is_open()){
    // continue;
  }else{
    string currLine;
    while(getline(inFS,currLine)){
      stringstream  linestream(currLine);
      string stringID;
      string stringAdvisees;
      getline(linestream,stringID,',');
      getline(linestream,name,',');
      getline(linestream,level,',');
      getline(linestream,department,',');
      getline(linestream,stringAdvisees,'\n');

      id = stoi(stringID);
      // cout << name << endl;
      // cout << level << endl;
      // cout << department << endl;
      // cout << stringAdvisees << endl;
      Faculty f(id,name,level,department);

      string studentID;
      for(int i = 0; i < stringAdvisees.size(); ++i){
        if(stringAdvisees[i] != ','){
          // cout << stringAdvisees[i] << endl;
          studentID += stringAdvisees[i];
        }else{
          int idToAdd = stoi(studentID);
          f.addAdvisee(idToAdd);
          studentID = "";
        }

      }
      // cout << studentID << endl;
      int idToAdd = stoi(studentID);
      f.addAdvisee(idToAdd);

      // cout << "before insert" << endl;
      masterFaculty->insert(id,f);
      // cout << "here" << endl;

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
      while(cin.fail()){
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> id;
      }
      findStudent(id);
      break;
    case 4:
      cout << "Enter the ID of the faculty member: " << endl;
      cin >> id;
      while(cin.fail()){
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> id;
      }
      findFaculty(id);
      break;
    case 5:
      cout << "Enter the student ID number: " << endl;
      cin >> studentID;
      while(cin.fail()){
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> studentID;
      }
      getStudentAdvisor(studentID);
      break;
    case 6:
      cout << "Enter the faculty ID number: " << endl;
      cin >> facultyID;
      while(cin.fail()){
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> facultyID;
      }
      getAdvisorList(facultyID);
      break;
    case 7:
    {
      Student s1 = addStudent();
      cout << "stack" << endl;
      Transaction t1 = Transaction("delete", s1);
      cout << "transaction created" << endl;
      rb->push(t1);
      cout << "pushed" << endl;
      break;
    }
    case 8:
    {
      cout << "Enter the student ID number: " << endl;
      cin >> studentID;
      while(cin.fail()){
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> studentID;
      }
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
      while(cin.fail()){
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> facultyID;
      }
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
      while(cin.fail()){
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> studentID;
      }
      cout << "Enter the new advisor faculty ID number: " << endl;
      cin >> facultyID;
      while(cin.fail()){
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> facultyID;
      }
      changeAdvisor(studentID, facultyID);
      break;
    }
    case 12:
    {
      cout << "Enter the student ID number: " << endl;
      cin >> studentID;
      while(cin.fail()){
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> studentID;
      }
      cout << "Enter the new advisor faculty ID number: " << endl;
      cin >> facultyID;
      while(cin.fail()){
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> facultyID;
      }
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
      // ofstream outFS;
      //
      // outFS.open("masterStudent.txt");

      // outFS.close();
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
  masterStudent->printTree(root);
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
  while(!masterStudent->containsKey(id)){
    cout << "No student with that ID. Please enter a valid student ID: " << endl;
    cin >> id;
  }
  Student currStudent = masterStudent->search(id);
  cout << "Name: " << currStudent.getName() << endl;
  cout << "Level: " << currStudent.getLevel() << endl;
  cout << "Major: " << currStudent.getMajor() << endl;
  cout << "GPA: " << currStudent.getGPA() << endl;
  cout << "Advisor ID: " << currStudent.getAdvisor() << endl;
}

void Simulation::findFaculty(int id){
  while(!masterFaculty->containsKey(id)){
    cout << "No faculty with that ID. Please enter a valid student ID: " << endl;
    cin >> id;
  }
  Faculty currFaculty = masterFaculty->search(id);
  cout << "Name: " << currFaculty.getName() << endl;
  cout << "Level: " << currFaculty.getLevel() << endl;
  cout << "Department: " << currFaculty.getDepartment() << endl;
  cout << "Faculty's Advisees: " << endl;
  currFaculty.printAdvisees();
}

void Simulation::getStudentAdvisor(int studentID){
  while(!masterStudent->containsKey(studentID)){
    cout << "No student with that ID. Please enter a valid student ID: " << endl;
    cin >> studentID;
    while(cin.fail()){
      cout << "Invalid input type. Please enter a valid id: " << endl;
      cin.clear();
      cin.ignore();
      cin >> studentID;
    }
  }
  int advisorID = 0;
  Student currStudent = masterStudent->search(studentID);
  advisorID = currStudent.getAdvisor();
  findFaculty(advisorID);
}

void Simulation::getAdvisorList(int facultyID){
  while(!masterFaculty->containsKey(facultyID)){
    cout << "No student with that ID. Please enter a valid student ID: " << endl;
    cin >> facultyID;
  }
  Faculty currFaculty = masterFaculty->search(facultyID);
  DoublyLinkedList<int>* students = currFaculty.getAdvisees();
  for(int i = 0; i < students->getSize(); ++i){
    int studentID = students->accessAtPos(i);
    cout << studentID << endl;
    Student currStudent = masterStudent->search(studentID);
    cout << "successful search 2" << endl;
    findStudent(currStudent.getID());
    cout << "successful search 3" << endl;
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
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid id: " << endl;
    cin.clear();
    cin.ignore();
    cin >> studentID;
  }
  cout << "Name: " << endl;
  cin >> name;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid name: " << endl;
    cin.clear();
    cin.ignore();
    cin >> name;
  }
  cout << "Level: (Freshman, sophomore, junior, senior)" << endl;
  cin >> level;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid input: " << endl;
    cin.clear();
    cin.ignore();
    cin >> level;
  }
  cout << "Major: " << endl;
  cin >> major;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid input: " << endl;
    cin.clear();
    cin.ignore();
    cin >> major;
  }
  cout << "GPA: " << endl;
  cin >> gpa;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid input: " << endl;
    cin.clear();
    cin.ignore();
    cin >> gpa;
  }
  cout << "Advisor ID number: " << endl;
  cin >> advisor;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid id: " << endl;
    cin.clear();
    cin.ignore();
    cin >> advisor;
  }
  while(masterFaculty->containsKey(advisor) == false && advisor >= 0){
    cout << "Invalid ID number. Enter an existing Advisor ID number (or -1 to exit): " << endl;
    cin >> advisor;
  }
  Student newStudent(studentID,name,level,major,gpa,advisor);
  masterStudent->insert(studentID,newStudent);
  Faculty newAdvisor = masterFaculty->search(advisor);
  newAdvisor.addAdvisee(studentID);
}

void Simulation::deleteStudent(int studentID){
  Student currStudent = masterStudent->search(studentID);
  Faculty advisor = masterFaculty->search(currStudent.getAdvisor());
  advisor.removeAdvisee(studentID);
  masterStudent->deleteNode(studentID);
}

Faculty Simulation::addFaculty(){
  int facultyID = 0;
  string name = "";
  string level = "";
  string department = "";
  DoublyLinkedList<int>* advisees = new DoublyLinkedList<int>();
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

// string Simulation::SerializeStudents(TreeNode<Student> root){
//   if(root == NULL){
//     return "";
//   }
//   String leftSerialized = Serialize(root.left);
//   String rightSerialized = Serialize(root.right);
//   return root.value + leftSerialized + rightSerialized;
// }

// string Simulation::SerializeFaculty(TreeNode<Faculty> root){
//   if(root == NULL){
//     return "";
//   }
//   String leftSerialized = Serialize(root.left);
//   String rightSerialized = Serialize(root.right);
//   return root.value + leftSerialized + rightSerialized;
// }
