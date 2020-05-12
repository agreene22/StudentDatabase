/* Anna Greene - 2314663
  Brandon Kleinman - 2291703
  Assignment 5 - Student Database
  Tree Node template class to create a node for a binary search tree
 */
#include <iostream>
using namespace std;

template <typename T>
class TreeNode{
public:
  // constructors
  TreeNode();
  TreeNode(int k);
  TreeNode(int k, T value);
  ~TreeNode(); // destructor

  int getKey();

  // member variables
  int key;
  T value;
  TreeNode *left;
  TreeNode *right;
};

//treenode implementation

// default constructor
template <typename T>
TreeNode<T>::TreeNode(){
  key = 0; // initialize values to null
  value = NULL;
  left = NULL;
  right = NULL;
}

// overloaded constructors
template <typename T>
TreeNode<T>::TreeNode(int k){
  key = k;
  value = NULL;
  left = NULL;
  right = NULL;
}

template <typename T>
TreeNode<T>::TreeNode(int k, T v){
  key = k;
  value = v;
  left = NULL;
  right = NULL;
}

// destructor
template <typename T>
TreeNode<T>::~TreeNode(){
  delete right; // delete pointers
  delete left;
}


// Accessor which returns an integer represnting the node's key
template <typename T>
int TreeNode<T>::getKey(){
  return key;
}
