#include <iostream>
#include "TreeNode.h"
using namespace std;

template <typename T>
class BST{
public:
  BST();
  ~BST();
  //virtual ~BST() - when working with template Class

  void insert(T value); // which in this example is also our key
  bool search(T value);
  bool deleteNode(T k);

  bool isEmpty();
  TreeNode<T>* getMin();
  TreeNode<T>* getMax();

  TreeNode<T>* getSuccessor(TreeNode<T> *d);
  void printTree(TreeNode<T> *node);
private:
  TreeNode<T> *root;
};

template <typename T>
BST<T>::BST(){
  root = NULL; //empty tree
}

template <typename T>
BST<T>::~BST(){
  //as always lets build some character
  delete root;
}

template <typename T>
void BST<T>::printTree(TreeNode<T> *node){ // O(N)
  if(node == NULL){
    return;
  }
  printTree(node->left);
  cout << node->key << endl;
  printTree(node->right);
}

template <typename T>
TreeNode<T>* BST<T>::getMax(){
  TreeNode<T> *curr = root;

  if(root == NULL){
    //empty tree;
    return NULL;
  }
  while(curr->right != NULL){
    curr = curr->right;
  }
  return curr; //curr->data or curr->key you can return what you want
}

template <typename T>
TreeNode<T>* BST<T>::getMin(){
  TreeNode<T> *curr = root;

  if(root == NULL)
    return NULL;
  while(curr->left != NULL){
    curr = curr->left;
  }
  return curr;
}

template <typename T>
bool BST<T>::isEmpty(){
  return (root == NULL);
}

template <typename T>
void BST<T>::insert(T value){

  if(search(value)){
    cout << "value already exists" << endl;
    return;
  }
  TreeNode<T> *node = new TreeNode<T>(value);

  if(isEmpty()){
    //empty tree
    root = node;
  }else{
    //not an empty tree
    TreeNode<T> *curr = root; //start at the root
    TreeNode<T> *parent;

    while(true){
      parent = curr;
      if(value < curr->key){
        //go left
        curr = curr->left;
        if(curr == NULL){
          parent->left = node;
          break;
        }
      }
      else{
        // go right
        curr = curr->right;
        if(curr == NULL){
          parent->right = node;
          break;
        }
      }
    }
  }
}

template <typename T>
bool BST<T>::search(T value){
  if(isEmpty())
    return false;
  else{
    //its not an empty tree
    TreeNode<T> *current = root;

    while(current->key != value){
      if(value < current->key){
        current = current->left;
      }else{
        current = current->right;
      }

      if(current == NULL){ // we didn't find the value
        return false;
      }
    }

    return true;
  }
}

template <typename T>
bool BST<T>::deleteNode(T k){
  if(isEmpty()){
    return false;
  }

  TreeNode<T> *parent = root;
  TreeNode<T> *current = root;
  bool isLeft = true;

  while(current->key != k){
    parent = current;
    if(k < current->key){
      isLeft = true;
      current = current->left;
    }else{
      isLeft = false;
      current = current->right;
    }

    if(current == NULL){
      return false;
    }
  }

  //if we make it here, we found the value now lets proceed to delete
  if(current->left == NULL && current->right == NULL){
    //then we have a leaf node
    if(current == root){
      root = NULL;
    }else if(isLeft){
      parent->left = NULL;
    }else{
      parent->right = NULL;
    }
  }
  //one child case
  else if(current->right == NULL){ // no right child so it must be left
    if(current == root){
      root = current->left;
    }else if(isLeft){
      parent->left = current->left;
    }else{
      parent->right = current->left;
    }
  }else if(current->right == NULL){ // no left child so it must be right
    //^this else if determines position of children of node to be deleted
    //these branching statements identify position of node to be deleted
    if(current == root){
      root = current->right;
    }else if(isLeft){
      parent->left = current->right;
    }else{
      parent->right = current->right;
    }
  }else{
    TreeNode<T> *successor = getSuccessor(current);

    if(current == root)
      root = successor;
    else if(isLeft)
      parent->left = successor;
    else
      parent->right = successor;

    //connect/link successor to current's(d) left child
    successor->left = current->left;

    return true;
  }
}

template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){
  // the parameter d represents the node to be deleted
  TreeNode<T> *current = d->right;
  TreeNode<T> *sp = d;
  TreeNode<T> *successor = d;

  while(current != NULL){
    sp = successor;
    successor = current;
    current = current->left;
  }

  if(successor != d->right){
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}
