// Implementation file for AVL search tree

#include "Dictionary.h"

int max(int x, int y)
{
  if (x > y)
    return x;
  else
    return y;
}

Dictionary::Dictionary()
{
  root = NULL;
  size = 0;
}

Dictionary::Dictionary(const Dictionary& orig)
{
  this->copyDict(orig);
}

Dictionary::~Dictionary()
{
  this->deleteDict();
}

Dictionary& Dictionary::operator=(const Dictionary& orig)
{
  if (this->root != orig.root)
    {
      this->deleteDict();
      this->copyDict(orig);
    }
  return *this;
}

int GetNodeHeight(AVLTreeNode* t)
{
  return t == NULL ? -1 : t->height;
}

void RotateWithLeftChild(AVLTreeNode*& k2)
{
  AVLTreeNode* k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = max(GetNodeHeight(k2->left), GetNodeHeight(k2->right)) + 1;
  k1->height = max(GetNodeHeight(k1->left), k2->height) + 1;
  k2 = k1;
}

void RotateWithRightChild(AVLTreeNode*& k2)
{
  AVLTreeNode* k1 = k2->right;
  k2->right = k1->left;
  k1->left = k2;
  k2->height = max(GetNodeHeight(k2->left), GetNodeHeight(k2->right)) + 1;
  k1->height = max(k2->height, GetNodeHeight(k1->left)) + 1;
  k2 = k1;
}

void DoubleWithLeftChild(AVLTreeNode*& k3)
{
  RotateWithRightChild(k3->left);
  RotateWithLeftChild(k3);
}

void DoubleWithRightChild(AVLTreeNode*& k3)
{
  RotateWithLeftChild(k3->right);
  RotateWithRightChild(k3);
}

void Insert(AVLTreeNode* p, AVLTreeNode*& t)
{

  if (t == NULL)
    t = p;
  else
    {
      if (p->data < t->data) // headed left
	{
	  Insert(p, t->left);
	  if ( GetNodeHeight(t->left) - GetNodeHeight(t->right) == 2)
	    if (p->data < t->left->data)
	      RotateWithLeftChild(t);
	    else
	      DoubleWithLeftChild(t);
	}
      else
	{
	  Insert(p, t->right);
	  if (GetNodeHeight(t->right) - GetNodeHeight(t->left) == 2)
	    if (p->data > t->right->data)
	      RotateWithRightChild(t);
	    else
	      DoubleWithRightChild(t);
	}
    }
  t->height =max(GetNodeHeight(t->left), GetNodeHeight(t->right)) + 1;
}

void Dictionary::AddEntry(string anEntry)
{
  // create the node
  AVLTreeNode* p = new AVLTreeNode;
  p->data = anEntry;
  p->height = 0;
  p->left = NULL;
  p->right = NULL;
  
  Insert(p, root);
}

bool Dictionary::FindEntry(string key)
{
  AVLTreeNode* q = root;
  bool found = false;

  while (!found && q)
    {
      if (q->data == key)
	{
	  found = true;
	}
      else if (q->data < key)
	{
	  q = q->right;
	}
      else
	{
	  q = q->left;
	}
    }
  return found;
}
	
void PrintInOrder(AVLTreeNode* p, ostream& outStream)
{
  if (p)
    {
      PrintInOrder(p->left, outStream);
      outStream << p->data << endl;
      PrintInOrder(p->right, outStream);
    }
}

void Dictionary::PrintSorted(ostream& outStream)
{
  PrintInOrder(root,outStream);
}

AVLTreeNode* copyTree(const AVLTreeNode* node)
{
  if (!node)
    return NULL;
  else
    {
      AVLTreeNode* newNode = new AVLTreeNode;
      newNode->data = node->data;
      newNode->height = node->height;
      newNode->left = copyTree(node->left);
      newNode->right = copyTree(node->right);
      return newNode;
    }
}

void Dictionary::copyDict(const Dictionary& orig)
{
  this->size = orig.size;
  this->root = copyTree(orig.root);
}

void deleteTree(AVLTreeNode* node)
{
  if (node)
    {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
}

void Dictionary:: deleteDict()
{
  deleteTree(this->root);
  this->root = NULL;
}

