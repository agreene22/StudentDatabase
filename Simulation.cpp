/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Simulation implementation file which defines methods
 */

#include "Simulation.h"
#include <fstream>
#include <sstream>

// default constructor
Simulation::Simulation(){
  masterStudent = new BST<Student>();
  masterFaculty = new BST<Faculty>();
  rb = new Rollback();
}

// overloaded constructor
Simulation::Simulation(BST<Student>* students, BST<Faculty>* facultys){
  masterStudent = students;
  masterFaculty = facultys;
  rb = new Rollback();
}

// destructor
Simulation::~Simulation(){
  delete masterStudent; // delete pointers
  delete masterFaculty;
  delete rb;
}

// Set Trees will find studentTable and facultyTable files and read their objects in and add to the trees
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


  inFS.open("studentTable.txt"); // opens file stream
  if(!inFS.is_open()){
    // continue;
  }else{

    string currLine;
    while(getline(inFS,currLine)){
      stringstream  linestream(currLine); // starts string stream to separate variables on comma or line break
      string stringID;
      string stringGPA;
      string stringAdvisor;
      getline(linestream,stringID,',');
      getline(linestream,name,',');
      getline(linestream,level,',');
      getline(linestream,major,',');
      getline(linestream,stringGPA,',');
      getline(linestream,stringAdvisor,'\n');

      id = stoi(stringID); // changing variables from string to correct type -  string to integer
      gpa = stod(stringGPA); // string to double
      advisorID = stoi(stringAdvisor); // string to integer
      Student s(id,name,level,major,gpa,advisorID); // creating instance of student
      masterStudent->insert(id,s); // adding to tree of students
    }

  }
  inFS.close(); // closes filestream

  inFS.open("facultyTable.txt");
  if(!inFS.is_open()){
    // continue;
  }else{
    string currLine;
    while(getline(inFS,currLine)){
      stringstream  linestream(currLine); // stringstream to read in variables identified by separation with comma
      string stringID;
      string stringAdvisees;
      getline(linestream,stringID,',');
      getline(linestream,name,',');
      getline(linestream,level,',');
      getline(linestream,department,',');
      getline(linestream,stringAdvisees,'\n');

      id = stoi(stringID); // converting string to integer
      Faculty f(id,name,level,department); // creating instance of faculty with information from file

      string studentID;
      for(int i = 0; i < stringAdvisees.size(); ++i){ // reading in the advisee list and adding them to the faculty instance
        if(stringAdvisees[i] != ','){
          studentID += stringAdvisees[i];
        }else{
          int idToAdd = stoi(studentID); // converting string to integer for studentID
          f.addAdvisee(idToAdd); // assigning faculty to student
          studentID = "";
        }

      }
      int idToAdd = stoi(studentID);
      f.addAdvisee(idToAdd);

      masterFaculty->insert(id,f); // inserting the faculyt into the tree

    }
  }
  inFS.close();
}


// Displays menu options and reads in user choice
int Simulation::Menu(){
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

// simulate method to call corresponding method based on user choice and input of information
void Simulation::Simulate(int choice){
  int id = 0;
  int studentID = 0;
  int facultyID = 0;
  switch (choice) {
    case 1:
      printStudents(); // will print all the students in ascending order
      break;
    case 2:
      printFaculty(); // print all the faculty in ascending order
      break;
    case 3:
      cout << "Enter the ID of the student: " << endl;
      cin >> id;
      while(cin.fail()){ // checks if input is the valid type for variable
        cout << "Invalid input type. Please enter a valid id: " << endl;
        cin.clear();
        cin.ignore();
        cin >> id;
      }
      findStudent(id); // will display information of student given ID
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
      findFaculty(id); // display information of faculty given ID
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
      getStudentAdvisor(studentID); // display faculty information for student given student ID
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
      getAdvisorList(facultyID); // display list of advisees asigned to a faculty
      break;
    case 7:
    {
      Student s1 = addStudent();
      Transaction t1 = Transaction("delete", s1); // instance of transaction of type delete with student as input
      rb->push(t1); // pushes onto rollback
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
      Transaction t2 = Transaction("add", s2); // instance of transaction to add a student to the tree
      rb->push(t2);
      deleteStudent(studentID); // deletes student from tree given ID
      break;
    }
    case 9:
    {
      Faculty f1 = addFaculty();
      Transaction t3 = Transaction("delete", f1); // instance of transaction which will undo the addition of faculty to tree
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
      Transaction t4 = Transaction("add", f2); // transaction which will undo deletion of faculty from tree
      rb->push(t4);
      deleteFaculty(facultyID); // deletes faculty from tree given id number
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
      changeAdvisor(studentID, facultyID); // will change student advisor given new faculty ID
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
      removeAdvisee(studentID, facultyID); // remove an advisee from an advisor and asign a new one
      break;
    }
    case 13:
    {
      Transaction t5 = rb->pop(); // getting transaction from rollback
      Person p5 = t5.getPerson(); // getting person from the transaction
      if(t5.getPersonType() == "Student"){
        Student & s5 = static_cast<Student&>(p5);
        if(t5.getTransactionType() == "add"){
          addStudent(s5);
          cout << "Rollback delete from student database." << endl;
        }else{
          deleteStudent(s5.getID());
          cout << "Rollback insert from student database." << endl;
        }
      }else{
        Faculty & f5 = static_cast<Faculty&>(p5);
        if(t5.getTransactionType() == "add"){
          addFaculty(f5);
          cout << "Rollback delete from faculty database." << endl;
        }else{
          deleteFaculty(f5.getID());
          cout << "Rollback insert from faculty database." << endl;
        }
      }
      break;
    }
    case 14:
    {


      cout << "Exiting program." << endl;
      // serialize everything to the file
      ofstream outFS;

      outFS.open("masterStudent.txt"); // opens output stream
      TreeNode<Student>* studentRoot = masterStudent->getRoot(); // gets root of student tree
      string studentInfo = serializeStudents(studentRoot);
      outFS << studentInfo; // writes student info to output stream
      outFS.close(); // closes output stream

      outFS.open("masterFaculty.txt"); // opens output stream
      TreeNode<Faculty>* facultyRoot = masterFaculty->getRoot(); // gets root of faculty tree
      string facultyInfo = SerializeFaculty(facultyRoot);
      outFS << facultyInfo; // writes faculty information to output stream
      outFS.close(); // closes output stream

      exit(0); // will exit the program
      break;
    }
    default:
      cout << "Invalid input please try again." << endl;
      exit(1);
      break;
  }
}

// Print students will display all student information from the BST
void Simulation::printStudents(){
  TreeNode<Student>* root = masterStudent->getRoot();
  masterStudent->printTree(root); // starting from root of tree
}

// Print faculty will display all faculty information from the BST starting from the root
void Simulation::printFaculty(){
  TreeNode<Faculty>* root = masterFaculty->getRoot();
  masterFaculty->printTree(root);
}

// Get Student will return the current student given ID number as a parameter
Student Simulation::getStudent(int id){
  Student currStudent = masterStudent->search(id);
  return currStudent;
}

// get Faculty will return the current faculty given ID number as a parameter
Faculty Simulation::getFaculty(int id){
  Faculty currFaculty = masterFaculty->search(id);
  return currFaculty;
}

// find student will search the tree given an ID and then display all of that student's information
void Simulation::findStudent(int id){
  while(!masterStudent->containsKey(id)){
    cout << "No student with that ID. Please enter a valid student ID: " << endl;
    cin >> id; // prompt for ID number of a student that exists
    while(cin.fail()){
      cout << "Invalid input type. Please enter a valid id: " << endl;
      cin.clear();
      cin.ignore();
      cin >> id; // prompt for input of correct type
    }
  }
  Student currStudent = masterStudent->search(id);
  cout << "Name: " << currStudent.getName() << endl; // display information
  cout << "Level: " << currStudent.getLevel() << endl;
  cout << "Major: " << currStudent.getMajor() << endl;
  cout << "GPA: " << currStudent.getGPA() << endl;
  cout << "Advisor ID: " << currStudent.getAdvisor() << endl;
}

// find faculty will search the tree given an ID and then display all of the faculty's information including advisees
void Simulation::findFaculty(int id){
  while(!masterFaculty->containsKey(id)){
    cout << "No faculty with that ID. Please enter a valid student ID: " << endl;
    cin >> id; // prompt for ID number that exiists
    while(cin.fail()){
      cout << "Invalid input type. Please enter a valid id: " << endl;
      cin.clear();
      cin.ignore();
      cin >> id; // prompt for input of correct type
    }
  }
  Faculty currFaculty = masterFaculty->search(id);
  cout << "Name: " << currFaculty.getName() << endl;
  cout << "Level: " << currFaculty.getLevel() << endl;
  cout << "Department: " << currFaculty.getDepartment() << endl;
  cout << "Faculty's Advisees: " << endl;
  currFaculty.printAdvisees(); // calls method to print advisees
}

// Get Student Advisor will display the information of the advisor for a student given the ID
void Simulation::getStudentAdvisor(int studentID){
  while(!masterStudent->containsKey(studentID)){
    cout << "No student with that ID. Please enter a valid student ID: " << endl;
    cin >> studentID; // prompt for ID number that exists
    while(cin.fail()){
      cout << "Invalid input type. Please enter a valid id: " << endl;
      cin.clear();
      cin.ignore();
      cin >> studentID; // prompt for input of correct type
    }
  }
  int advisorID = 0;
  Student currStudent = masterStudent->search(studentID); // search tree for student
  advisorID = currStudent.getAdvisor(); // retrieve their advisor
  findFaculty(advisorID);
}

// Get Advisor List will display information of a faculty member's advisees given ID
void Simulation::getAdvisorList(int facultyID){
  while(!masterFaculty->containsKey(facultyID)){
    cout << "No student with that ID. Please enter a valid student ID: " << endl;
    cin >> facultyID; // prompts for ID that exits
    while(cin.fail()){
      cout << "Invalid input type. Please enter a valid id: " << endl;
      cin.clear();
      cin.ignore();
      cin >> facultyID; // prompt for input of correct type
    }
  }
  Faculty currFaculty = masterFaculty->search(facultyID); // searches for faculty with ID in the tree
  DoublyLinkedList<int>* students = currFaculty.getAdvisees(); // linked list of that faculty member's advisees
  for(int i = 0; i < students->getSize(); ++i){
    int studentID = students->accessAtPos(i);
    cout << studentID << endl; // display student information
    Student currStudent = masterStudent->search(studentID);
    findStudent(currStudent.getID());
  }
}

// Add student prompts user for input and adds student instance to the tree
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
    cin >> studentID; // prompts for input of correct type
  }
  cout << "Name: " << endl;
  cin >> name;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid name: " << endl;
    cin.clear();
    cin.ignore();
    cin >> name; // prompts for input of correct type
  }
  cout << "Level: (Freshman, sophomore, junior, senior)" << endl;
  cin >> level;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid input: " << endl;
    cin.clear();
    cin.ignore();
    cin >> level; // prompts for input of correct type
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
  // while loop to ensure that the advisor number entered matches an existing advisor
  while(masterFaculty->containsKey(advisor) == false && advisor >= 0){
    cout << "Invalid ID number. Enter an existing Advisor ID number (or -1 to exit): " << endl;
    cin >> advisor;
  }
  Student newStudent(studentID,name,level,major,gpa,advisor); // create new student object
  masterStudent->insert(studentID,newStudent); // insert new student into tree
  Faculty newAdvisor = masterFaculty->search(advisor);
  newAdvisor.addAdvisee(studentID); // assign the student to the advisor's list
  return newStudent;
}

// Delete student will delete a student from the tree given the ID
void Simulation::deleteStudent(int studentID){
  Student currStudent = masterStudent->search(studentID); // finds the student in the tree
  Faculty advisor = masterFaculty->search(currStudent.getAdvisor());
  advisor.removeAdvisee(studentID); // removes advisee from advisor list
  masterStudent->deleteNode(studentID); // deletes node from tree
  cout << "Student deleted." << endl;
}

// Adds faculty will take user input to add a new faculty instance to the tree
Faculty Simulation::addFaculty(){
  int facultyID = 0;
  string name = "";
  string level = "";
  string department = "";
  DoublyLinkedList<int>* advisees = new DoublyLinkedList<int>();
  int studentID = 0;

  // Getting information for faculty member
  cout << "Enter the following information: " << endl;
  cout << "Faculty ID: " << endl;;
  cin >> facultyID;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid id: " << endl;
    cin.clear();
    cin.ignore();
    cin >> facultyID;
  }
  cout << "Name: " << endl;
  cin >> name;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid name: " << endl;
    cin.clear();
    cin.ignore();
    cin >> name;
  }
  cout << "Level: " << endl;
  cin >> level;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid level: " << endl;
    cin.clear();
    cin.ignore();
    cin >> level;
  }
  cout << "Department: " << endl;
  cin >> department;
  while(cin.fail()){
    cout << "Invalid input type. Please enter a valid department: " << endl;
    cin.clear();
    cin.ignore();
    cin >> department;
  }
  // while loop to get ID numbers of student's who will be faculty's advisees
  while(studentID != -1){
    cout << "Advisee ID numbers (enter -1 when done): ";
    cin >> studentID;
    while(cin.fail()){
      cout << "Invalid input type. Please enter a valid id: " << endl;
      cin.clear();
      cin.ignore();
      cin >> studentID;
    }
    advisees->insertBack(studentID); // add to advisor's list
  }

  Faculty newFaculty(facultyID,name,level,department,advisees); // new faculty object
  masterFaculty->insert(facultyID,newFaculty); // insert faculty into tree
  return newFaculty;
}

// Delete faculty will remove the node from the tree given the ID as the key
void Simulation::deleteFaculty(int facultyID){
  Faculty currFaculty = masterFaculty->search(facultyID); // finds the current faculty member
  DoublyLinkedList<int>* advisees = currFaculty.getAdvisees();
  for(int i = 0; i < advisees->getSize(); ++i){ // assigns all the advisee's to a new advisor
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
  masterFaculty->deleteNode(facultyID); // removes node from tree
  cout << "Faculty deleted." << endl;
}

// change Advisor will assign a student a new faculty advisor given IDs
void Simulation::changeAdvisor(int studentID, int facultyID){
  Student currStudent = masterStudent->search(studentID); // finds student in tree
  int prevAdvisorID = currStudent.getAdvisor(); // stores previous advisor's id number
  Faculty prevAdvisor = masterFaculty->search(prevAdvisorID);
  prevAdvisor.removeAdvisee(studentID); // removes the advisee from the previous advisor list
  currStudent.setAdvisor(facultyID); // sets new advisor
  Faculty newAdvisor = masterFaculty->search(facultyID);
  newAdvisor.addAdvisee(studentID); // adds student to new advisor's list
}

// Remove student from advisee and assigns a new advisor
void Simulation::removeAdvisee(int studentID, int facultyID){
  Faculty advisor = getFaculty(facultyID); // gets faculty from tree given advisee
  advisor.removeAdvisee(studentID); // removes student from advisor's list
  Student currStudent = getStudent(studentID);
  if(facultyID == masterFaculty->getRoot()->getKey()){ // assigns student new advisor
    int advisorID = masterFaculty->getRootLeftChild()->getKey();
    currStudent.setAdvisor(advisorID);
  }else{
    int advisorID = masterFaculty->getRoot()->getKey();
    currStudent.setAdvisor(advisorID);
  }
}

// Adds student into tree
void Simulation::addStudent(Student s){
  masterStudent->insert(s.getID(),s);
}

// Adds faculty into tree
void Simulation::addFaculty(Faculty f){
  masterFaculty->insert(f.getID(),f);
}

string Simulation::serializeStudents(TreeNode<Student>* root){
  if(root == NULL){
    return "";
  }
  Student s = root->value;
  string ret = "";
  string id = to_string(s.getID());
  ret += id;
  ret += ",";
  ret += s.getName();
  ret += ",";
  ret += s.getLevel();
  ret += ",";
  ret += s.getMajor();
  ret += ",";
  string gpa = to_string(s.getGPA());
  ret += gpa;
  ret += ",";
  string advisorID = to_string(s.getAdvisor());
  ret += advisorID;
  ret += "\n";
  string leftSerialized = serializeStudents(root->left);
  string rightSerialized = serializeStudents(root->right);
  return (ret + leftSerialized + rightSerialized);
}

string Simulation::SerializeFaculty(TreeNode<Faculty>* root){
  if(root == NULL){
    return "";
  }
  Faculty f = root->value;
  string ret = "";
  string id = to_string(f.getID());
  ret += id;
  ret += ",";
  ret += f.getName();
  ret += ",";
  ret += f.getLevel();
  ret += ",";
  ret += f.getDepartment();
  ret += ",";
  DoublyLinkedList<int>* a = f.getAdvisees();
  for(int i = 0; i < a->getSize(); ++i){
    string studentID = to_string(a->accessAtPos(i));
    ret += studentID;
    if(i != (a->getSize()-1)){
      ret += ",";
    }
  }
  ret += "\n";
  string leftSerialized = SerializeFaculty(root->left);
  string rightSerialized = SerializeFaculty(root->right);
  return ret + leftSerialized + rightSerialized;
}
