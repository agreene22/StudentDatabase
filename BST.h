#include <iostream>
#include "TreeNode.h"
using namespace std;

template <typename T>
class BST{
public:
  BST();
  ~BST();

  TreeNode<T>* getRoot();
  TreeNode<T>* getRootLeftChild();

  void insert(int key, T value);
  T search(int key);
  bool containsKey(int key);
  bool deleteNode(int k);

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
  delete root;
}

template <typename T>
TreeNode<T>* BST<T>::getRoot(){
  return root;
}

template <typename T>
TreeNode<T>* BST<T>::getRootLeftChild(){
  return root->left;
}

template <typename T>
void BST<T>::printTree(TreeNode<T> *node){
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
  return curr->key;
}

template <typename T>
TreeNode<T>* BST<T>::getMin(){
  TreeNode<T> *curr = root;

  if(root == NULL)
    return NULL;
  while(curr->left != NULL){
    curr = curr->left;
  }
  return curr->key;
}

template <typename T>
bool BST<T>::isEmpty(){
  return (root == NULL);
}

template <typename T>
void BST<T>::insert(int key, T value){
  TreeNode<T> *node = new TreeNode<T>(key, value);

  if(isEmpty()){
    //empty tree
    root = node;
  }else{
    if(containsKey(key)){
      cout << "value already exists" << endl;
      return;
    }
    //not an empty tree
    TreeNode<T> *curr = root;
    TreeNode<T> *parent;

    while(true){
      parent = curr;
      if(value.getID() < curr->key){
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
  // delete node;
}

template <typename T>
T BST<T>::search(int key){
  if(isEmpty()){
  cout << "Empty Database." << endl;
  // NEED TO EXIT HERE BUT IDK WHAT TO RETURN
  }else{
    //its not an empty tree
    TreeNode<T>* current = root;

    while(current->key != key){
      if(key < current->key){
        current = current->left;
      }else{
        current = current->right;
      }

      if(current == NULL){ // didn't find the value
        cout << "Value not found." << endl;
        // NEED TO EXIT HERE BUT IDK WHAT TO RETURN
      }
    }

    return current->value;
  }
}

template <typename T>
bool BST<T>::containsKey(int key){ // may need to return pointer depending on what is in tree
  if(isEmpty()){
  cout << "Empty Database." << endl;
  // NEED TO EXIT HERE BUT IDK WHAT TO RETURN
  }else{
    //its not an empty tree
    TreeNode<T>* current = root;

    while(current->key != key){
      if(key < current->key){
        current = current->left;
      }else{
        current = current->right;
      }

      if(current == NULL){ // didn't find the value
        return false;
      }
    }

    return true;
  }
}

template <typename T>
bool BST<T>::deleteNode(int k){
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

    successor->left = current->left;

    return true;
  }
}

template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){ // the parameter d represents the node to be deleted
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
