#include <iostream>
using namespace std;

template <typename T>
class TreeNode{
public:
  TreeNode();
  TreeNode(int k);
  TreeNode(int k, T value);
  ~TreeNode();
  //virtual ~TreeNode(); -when working with a template class

  int key;
  T value;
  TreeNode *left;
  TreeNode *right;
};

//treenode implementation
template <typename T>
TreeNode<T>::TreeNode(){
  key = 0;
  value = NULL;
  left = NULL;
  right = NULL;
}

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

template <typename T>
TreeNode<T>::~TreeNode(){
  delete right;
  delete left;
}
