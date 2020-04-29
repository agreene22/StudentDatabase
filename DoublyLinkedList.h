/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Doubly Linked List class to build a template list that can hold data of any type
 */

#include "ListNode.h"
using namespace std;

template <typename T>
class DoublyLinkedList{
public:
  DoublyLinkedList(); // default constructor
  ~DoublyLinkedList(); // destructor

  void insertFront(T* d); // insert functions
  void insertBack(T d);
  T* removeFront(); // remove functions
  // T removeBack();
  T* accessAtPos(int pos);
  T remove(T value);
  int search(T val); //will return position of node depending where it is in the list
  T removeAtPos(int pos);

  // aux functions
  unsigned int getSize();
  bool isEmpty();
  void printList();
  T* getFront();

private:
  ListNode<T> *front; // member variables
  ListNode<T> *back;
  unsigned int size;
};

// Default constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
  size = 0; // initilize member variables to null
  front = NULL;
  back = NULL;
}

// destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
  front = NULL; // null pointers before deletion
  back = NULL;
  delete front; // delete front and back pointers
  delete back;
}

// Get size returns the size of the doubly linked list
template <typename T>
unsigned int DoublyLinkedList<T>::getSize(){
  return size;
}

// Returns a bool representing if the list is empty
template <typename T>
bool DoublyLinkedList<T>::isEmpty(){
  return (size == 0);
}

// Print List method to display contents of list
template <typename T>
void DoublyLinkedList<T>::printList(){
  ListNode<T> *curr = front;
  while(curr != NULL){ // starting at the front of the list and iterating through using the next pointer
    cout << curr->data << endl; // displaying current node to the screen
    curr = curr->next;
  }
}

// Insert front method taken in a pointer to a node
template <typename T>
void DoublyLinkedList<T>::insertFront(T* d){
  ListNode<T> *node = new ListNode<T>(d); // creating new node

  if(isEmpty()){ // if the list is empty set the back pointer to be the node
    back = node;
  }
  else{
    //not isEmpty
    front->prev = node; // updating next pointers for current front and new node
    node->next = front;
  }
  front = node; // setting front pointer to new node
  size++; // updating size member variable
}

// Insert back function which takes in a pointer to a node
template <typename T>
void DoublyLinkedList<T>::insertBack(T d){
  ListNode<T> *node = new ListNode<T>(d); // creating new node

  if(isEmpty()){ // if the list is empty set the front pointer to the node
    front = node;
  }
  else{
    //not isEmpty
    back->next = node; // updating next and previous pointers for back and new node
    node->prev = back;
  }
  back = node; // setting back pointer to new node
  size++; // updating size
}

// Remove Front returns a pointer to a node's data
template <typename T>
T* DoublyLinkedList<T>::removeFront(){
  if(isEmpty()){ // if the list is empty give an error message
    cout << "Trying to remove from an empty list" << endl;
    exit(1); // exit the program
  }
  ListNode<T> *tempNode = front; // creating new node to store current front

  if(front->next == NULL){ //there is only one node in the list
    back = NULL; // nulling pointer before deletion
  }
  else{ //more than one node in the list
    front->next->prev = NULL; // nulling previous pointer of second node
  }

  front = front->next; // updating pointer for front
  tempNode->next = NULL; // nulling pointers before deletion
  tempNode->prev = NULL;
  T* temp = tempNode->data; // storing data from node
  size--; // decrementing size
  delete tempNode; // delete pointer

  return temp; // return student from node deleted
}

// Access at position returns a pointer to a node's data and takes in the position as a parameter
template <typename T>
T* DoublyLinkedList<T>::accessAtPos(int pos){
  ListNode<T> *curr = front; // creating node pointer to front
  int idx = 0; // declare and initialize index variable

  while(curr != NULL){ // iterate through the list
    if(idx == pos){ // when the position is found
      T* temp = curr->data; // store data of node into temp veriable

      return temp; // return data from node
    }
    curr = curr->next; // updating current for iteration
    idx++; // incrementing index

  }
}

// Remove function takes value to be deleted as parameter and returns a value
template <typename T>
T DoublyLinkedList<T>::remove(T value){
  ListNode<T> *curr = front; // creating node pointer to front

  while(curr->data != value){ // iterating until the data is found
    curr = curr->next;

    if(curr == NULL){ // the value was not found and NULL is returned
      return NULL;
    }
  }

  if(curr == front){ // node to be deleted is front
    front = curr->next; // updating front pointer
  }else{ //node to be deleted is somewhere in between front and back
    curr->prev->next = curr->next; // updating previous node's next pointer
  }

  if(curr == back){ // node to be deleted is the back
    back = curr->prev;
  }else{ //node to be deleted is somewhere in between front and back
    curr->next->prev = curr->prev; // updating next node's previous pointer
  }

  curr->next = NULL; // nulling pointers before deletion
  curr->prev = NULL;
  T temp = curr->data;  // storing node data in temporary variable
  size--;
  delete curr;

  return temp; // return node's data
}

// Search method takes in value as parameter and returns position
template <typename T>
int DoublyLinkedList<T>::search(T val){
  int pos = -1;
  ListNode<T> *curr = front;

  while(curr != NULL){ // loop to find the value in the list
    ++pos;
    if(curr->data == val){ // value found
      break;
    }
    else{
      curr = curr->next; // updating current pointer
    }

    if(curr == NULL){ // value not found
      pos = -1;
    }
    return pos;
  }
}

// Remove at position takes a position as parameter and returns data
template <typename T>
T DoublyLinkedList<T>::removeAtPos(int pos){
  if(pos > size){ // check that position is not greater than the size of the list
    return NULL;
  }
  int idx = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

  while(idx != pos){  // loop until find the position
    prev = curr; // updating pointers and index
    curr = curr->next;
    idx++;
  }

  prev->next = curr->next; // updating pointers
  curr->next = NULL;
  T temp = curr->data; // storing node's data to be returned
  delete curr;
  size--;

  return temp;
}

// Get Front returns a pointer to the front's data
template <typename T>
T* DoublyLinkedList<T>::getFront(){
  ListNode<T> *curr = front;
  T* temp = curr->data;
  return temp;
}
