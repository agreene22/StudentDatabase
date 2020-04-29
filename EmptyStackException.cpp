/*
Anna Greene - 2314663
Assignment 3
This file is the implementation for the empty stack exception
 */

#include "EmptyStackException.h"

EmptyStackException::EmptyStackException(){
  errMessage = ""; // initializing default value
}

EmptyStackException::EmptyStackException(string err){
  errMessage = err; // initializing default value to equal parameter
}

string EmptyStackException::getMessage(){
  return errMessage; // Returns the error message member variable
}
