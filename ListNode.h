/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  List Node class to create a node for a doubly linked list
 */

#include <iostream>
using namespace std;

template <typename T>
class ListNode{
public:
  T data; // Pointer to the data and its next and previous nodes //i took out the pointer
  ListNode<T> *next;
  ListNode<T> *prev;

  ListNode(); //constructor
  ListNode(T d); //overloaded constructor
  ~ListNode();
};

// default constructor
template <typename T>
ListNode<T>::ListNode(){
  data = NULL; // initilizing pointers to null
  next = NULL;
  prev = NULL;
}

// overloaded constructor
template <typename T>
ListNode<T>::ListNode(T d){
  data = d; // setting data pointer to parameter //took out the pointer for now
  next = NULL;
  prev = NULL;
}

// destructor
template <typename T>
ListNode<T>::~ListNode(){
  next = NULL; // deleting pointers for deletion
  prev = NULL;
  delete next;
  delete prev;
}
