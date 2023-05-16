/**
 * SkipList https://en.wikipedia.org/wiki/Skip_list
 * also used by MemSQL
 * https://www.singlestore.com/blog/what-is-skiplist-why-skiplist-index-for-memsql/
 * SkipList with a depth of 1 is similar to a linked list
 * Each item has a p percent chance of being at the next level up
 * If p is 50%,
 * All elements are inserted at the lowest Level (1)
 * 50% of the elements inserted in Level = 2
 * 50% of 50%, or 25% of the elements inserted in Level = 3
 * and so on
 *
 * If a Skip List has only 1 level
 * Insert O(n), Search O(n)
 * For Level > 1
 * Insert O(log n), Search O(log n)
 * Modifying p allows us to trade off search speed and storage cost
 *
 */

/**
 * SkipList that supports insertion, deletion,
 * and lookup in logn time by traversing top down.
 *
 * @authors Cami Lacy, Vikrant Verma
 *
 * 🐄
 */

#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

// only SkipList class can create SNode objects

class SkipList;

class SNode {
  // SkipList can access SNode's private variables
  friend class SkipList;

  // prints the value of an SNode
  friend ostream &operator<<(ostream &out, const SNode *sNode) {
    return out << sNode->val;
  }

  // this declaration is also needed so SNode properties can be
  // accessed in the SkipList << overload
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // constructor
  explicit SNode(int val = 0);

  // copy constructor
  SNode(const SNode &other);

  // data contained in the object
  int val;

  // link to Next SNode at each level
  vector<SNode *> next;
};

class SkipList {

  // display by level
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // Number of levels in SkipList
  int levels;

  // probability of inserting at a higher level
  // as an integer between 0% and 100% (exclusive)
  int probability;

  // special head SNode that is always present
  SNode *head;

  // return true p% of time,
  // for p = 50, each node has a 50% chance of being at higher level
  bool shouldInsertAtHigherLevel() const;

  // collect all SNode* objects that come before this value at each level
  // used as a helper function to add and remove
  vector<SNode *> getBeforeNodes(int val) const;

  // clears all nodes in a skip list
  void clear();

  // forces insertion of a node with a certain level
  void forceInsertion(int val, int level);

  // returns all nodes in a skiplist (the bottom level)
  vector<SNode *> getLevel0() const;

public:
  // Constructor with a default level count of 1
  explicit SkipList(int levels = 1, int probability = 0);

  // Copy Constructor
  SkipList(const SkipList &other);

  // Destructor
  virtual ~SkipList();

  // Adds a val to the list, doesn't allow duplicates
  void add(int val);

  // Adds a vector of vals to the list, doesn't allow duplicates
  void add(const vector<int> &values);

  // Removes a value, returns true if successful
  bool remove(int val);

  // Returns true if value is in skip list
  bool contains(int val) const;
};

#endif // ASS4_SKIPLIST_H