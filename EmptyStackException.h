/*
Anna Greene - 2314663
Assignment 3
This file is the header file for the Empty Stack Exception
 */

#include <iostream>
using namespace std;

// Class which is an Empty Stack Exception to be thrown
class EmptyStackException{
public:
  // constructors
  EmptyStackException(); // default constructor
  EmptyStackException(string err); // overloaded constructor

  string getMessage(); // Will return error message
private:
  string errMessage;
};
