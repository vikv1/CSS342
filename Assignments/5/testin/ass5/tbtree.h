/**
 *
 * Threaded Binary Tree structure
 *
 * @authors Vikrant Verma, Cami Lacy
 *
 * 🐄🐄🐄
 */

#ifndef ASS5_TBTREE_H
#define ASS5_TBTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TbsTree;
class Iterator;

class TNode {
  // Tbtree can access tNode's private variables
  friend class TbsTree;
  friend class Iterator;

  // prints the value of an tNode
  friend ostream &operator<<(ostream &out, const TNode *tNode) {
    return (out << tNode->val);
  }

  // this declaration is also needed so tNode properties can be
  // accessed in the Tbtree << overload
  friend ostream &operator<<(ostream &out, const TbsTree &argTree);

private:
  // default constructor
  explicit TNode(int val = 0, TNode *lft = nullptr, TNode *rt = nullptr);

  // copy constructor
  TNode(const TNode &other);

  // data contained in the object
  int val;

  // check if right pointer is a thread
  bool isThread = false;

  // pointers to children
  TNode *lftPtr;
  TNode *rtPtr;
};

class TbsTree {
  // display tree
  friend ostream &operator<<(ostream &out, const TbsTree &argTree);
  friend class Iterator;

public:
  // default constructor
  TbsTree();

  // copy constructor
  TbsTree(const TbsTree &tree);

  // takes integer, specifies no. of nodes in tree
  explicit TbsTree(int val);

  // destructor
  virtual ~TbsTree();

  // Adds a val to the tree, doesn't allow duplicates
  void add(int val);

  // adds a vectpr of vals
  void add(vector<int> &vals);

  // Removes a value, returns true if successful
  bool remove(int val);

  // Returns true if value is in tree
  bool contains(int val) const;

  // Get the height of a binary search tree.
  int getHeight();

  // returns root node
  TNode *getRoot() const;

  // clears all nodes in threaded binary tree
  void deleteAll();

private:
  // starts as nulllptr
  TNode *root;

  // clears all nodes in threaded binary tree
  void clear();

  // check empty tree
  bool isEmpty() const;

  // Search tree for value and return address
  TNode *searchTree(int val) const;

  // gets predecessor of node
  TNode *findPredecessor(TNode *start, TNode *node) const;

  // method wrapped by remove to del a node
  TNode *removeHelper(TNode *root, int val);

  // removal case if node has no children
  TNode *ifLeaf(TNode *root, TNode *t, TNode *p);

  // removal case if node has one child
  TNode *ifOneChild(TNode *root, TNode *t, TNode *p);

  // removal case if node has two children
  TNode *ifTwoChild(TNode *root, TNode *t);

  // max node in subtree
  TNode *maxNode(TNode *start) const;

  // Gets the next largest value
  TNode *getInOrderSuccessor(TNode *argNode) const;

  // recursive method to add a vector in a balanced fashion
  TNode *add(vector<int> &vals, int start, int end);

  // helper for getheight
  int heightHelper(TNode *argNode) const;

  // Get the number of nodes in a binary search tree.
  int getNumNodes() const;

  // helper to get numnodes
  int numNodesHelper(TNode *curNode, int countNodes) const;

  // return inorder vector representation of tree
  void inorderTraverseToVector(TNode *cur, vector<int> &v) const;
};

class Iterator {
  // Tbtree can access Iterator private variables
  friend class TbsTree;
  friend class TNode;

public:
  // performs inorder traversal
  void inorderTraverse(TNode *cur, TbsTree &t);
};

#endif