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
  bool isThread;

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

  // Helper for add

  // Removes a value, returns true if successful
  bool remove(int val);

  // Returns true if value is in tree
  bool contains(int val) const;

  TNode *getRoot() const;

private:
  // starts as nulllptr
  TNode *root;

  // clears all nodes in threaded binary tree
  void clear();

  TNode *add(TNode *cur, int val);

  // check empty tree
  bool isEmpty() const;

  // check leaf by checking if isThread is true
  // and if on the rightmost node with 2 nullptr/no thread
  bool isLeaf(const TNode &argNode) const;

  // Search tree for value and return address, logn operation
  TNode *searchTree(int val) const;

  TNode *searchParentOf(int val) const;

  // Redo thread pointer helper
  TNode *getBeforeNode(const TNode &argNode) const;

  // Rethreads a node, used after deletion
  void rethread(const TNode *argNode);

  // Gets the next largest value and threads argNode to it
  TNode *getInOrderSuccessor(const TNode *argNode);

  // Get the height of a binary search tree.
  int getHeight();

  int heightHelper(const TNode *argNode);

  // Get the number of nodes in a binary search tree.
  int getNumNodes() const;

  int numNodesHelper(TNode *curNode, int countNodes) const;

  // Get the data in a binary search tree’s root
  int getRootVal() const;

  int curDepth;
  int maxDepth;
};

class Iterator {
  // Tbtree can access Iterator private variables
  friend class TbsTree;
  friend class TNode;

public:
  // performs inorder traversal
  void inorderTraverse(TNode *cur);
};

#endif