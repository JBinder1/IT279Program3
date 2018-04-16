// file to implement a binary search tree of Entry objects

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>

using namespace std;

struct AVLTreeNode
{
  string data;
  int height;
  AVLTreeNode* left;
  AVLTreeNode* right;
};

class Dictionary
{
 private:
  AVLTreeNode* root;
  int size;

 public:

  Dictionary();
  // Creates an empty dictionary;

  Dictionary(const Dictionary& orig);
  // Copy constructor

  virtual ~Dictionary();
  // Destructor

  Dictionary& operator=(const Dictionary& orig);
  // assignment operator

  void AddEntry(string anEntry);
  // Preconditions: anEntry has a key not already in the dictionary
  // Postconditions: anEntry has been added to the dictionary

  bool FindEntry(string key);
  // Postconditions: if key is found in the dictionary, returns true; 
  //   otherwise returns false

  void PrintSorted(ostream& outStream);
  // Postconditions: has printed contents of the dictionary in order

 private:

  void copyDict(const Dictionary& orig);
  // copies the contents of orig to this dictionary

  void deleteDict();
  // properly frees all memory occupied by this Dictionary

};

#endif
