#include "skiplist.h"
#include "random.h"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <unordered_map>

/**
 * SkipList class that uses SkipNodes to store values
 * and pointers to next nodes in the skiplist.
 * Each SNode may have a different size of a vector
 * to hold next pointers, this corresponds to the "level"
 * the node is on.
 *
 * @authors Cami Lacy, Vikrant Verma
 *
 * 🐄
 */

using namespace std;

/**
 * Constructs a new SNode object given a value
 *
 * @param val
 */
SNode::SNode(int val) : val(val){};

/**
 * Copies the value of an SNode into a new SNode
 *
 * @param other
 */
SNode::SNode(const SNode &other) { this->val = other.val; }

/**
 * Determines whether node should go up a level
 *
 * @return true
 * @return false
 */
bool SkipList::shouldInsertAtHigherLevel() const {
  return probability >= Random::random() % 100;
}

/**
 * Constructs a new SkipList object given levels and probability
 *
 * @param levels: max levels the skiplist can have
 * @param probability: chance a node moves up a level
 */
SkipList::SkipList(int levels, int probability) {
  this->levels = levels;
  this->probability = probability;

  /*
   * Nothing smaller than INT_MIN can be inserted, so no need to worry
   * about reassigning head later, and INT_MIN can still be inserted
   * by user.
   */
  head = new SNode(INT_MIN);
  head->next = vector<SNode *>(levels + 1);
}

/**
 * Constructs a new SkipList object given another SkipList
 *
 * @param other
 */
SkipList::SkipList(const SkipList &other)
    : levels(other.levels), probability(other.probability) {

  head = new SNode(INT_MIN);
  head->next = vector<SNode *>(this->levels + 1);

  // get all nodes in other
  vector<SNode *> level0 = other.getLevel0();

  for (int i = 0; i < level0.size(); i++) {
    // force skiplist to be identical to other by forcing nodes onto levels
    // level of node related to size of vector of next pointers

    // guaranteed to copy node because forceInsertion only takes primitive
    // integer
    forceInsertion(level0[i]->val, level0[i]->next.size() - 1);
  }
}

/**
 * Destructor to clear the heap.
 * Uses clear() to do so.
 *
 */
SkipList::~SkipList() { clear(); }

/**
 * Private method used by the destructor to
 * clear the heap by deleting each node one by one.
 *
 */
void SkipList::clear() {
  vector<SNode *> level0 = getLevel0();

  for (int i = level0.size() - 1; i >= 0; i--) {
    remove(level0[i]->val);
  }

  delete head;
  head = nullptr;
}

/**
 * Private method that returns a vector
 * of pointers of all nodes, which will just be the bottom level.
 *
 * @return vector<SNode *>
 */
vector<SNode *> SkipList::getLevel0() const {
  vector<SNode *> level0;
  SNode *iter = head->next[0];

  // get all nodes from bottom level
  while (iter != nullptr) {
    level0.push_back(iter);
    iter = iter->next[0];
  }

  return level0;
}

/**
 * Gets all nodes that come directly before the node containing
 * val from all levels. toUpdate[0] is the node right before val
 * on the 0th level (interpreted as the first though).
 *
 * @param val
 * @return vector<SNode *>
 */
vector<SNode *> SkipList::getBeforeNodes(int val) const {
  SNode *iter = head;
  vector<SNode *> toUpdate(levels);

  for (int i = levels - 1; i >= 0; i--) {
    // move as far right on each level as possible

    while (iter->next[i] != nullptr && iter->next[i]->val < val) {
      iter = iter->next[i];
    }

    // element right before we dropped, need to change pointer
    toUpdate[i] = iter;
  }

  return toUpdate;
}

/**
 * Traverses top-down via the getBeforeNodes method,
 * if the node right after what should be the previous node of argVal
 * is either a nullptr or a different val,
 * then the list does not contain the argVal.
 *
 * Returns true if argVal is present, else false.
 *
 * @param argVal
 * @return true
 * @return false
 */
bool SkipList::contains(int argVal) const {
  vector<SNode *> traverse = getBeforeNodes(argVal);

  // iter is where the argVal should be if it is present
  SNode *iter = traverse[0]->next[0];
  if (iter == nullptr) {
    return false;
  } else {
    return iter->val == argVal;
  }
}

/**
 * Adds a new node to the skiplist.
 * Uses the getBeforeNodes function to not only
 * get all nodes that may need to be rechained,
 * but also is used to traverse the list top-down
 * by comparing values and stopping at nodes that would
 * be right before val.
 *
 * @param val
 */
void SkipList::add(int val) {
  // traverses to bottom of skiplist while keeping track
  // of before nodes
  vector<SNode *> toUpdate = getBeforeNodes(val);

  // positions iteration pointer where value should be inserted
  SNode *iter = toUpdate[0]->next[0];

  // quicker to manually check at this point whether skiplist
  // contains the value instead of calling contains
  if (iter != nullptr && iter->val == val) {
    cout << "value already in list" << endl;
  } else {
    // starting at 1 replicates the same effect of using do-while loop
    int newNodeLevel = 1;

    // increments level count while shouldInsertAtHigherLevel() returns true
    while (shouldInsertAtHigherLevel() && newNodeLevel < levels) {
      newNodeLevel++;
    }

    // create new node, size of vector corresponds to node level
    SNode *newNode = new SNode(val);
    newNode->next = vector<SNode *>(newNodeLevel + 1);

    // for loop that rechains all node that came before it on each level
    // only rechains those on levels the new node will be present on
    for (int i = 0; i < newNodeLevel; i++) {
      newNode->next[i] = toUpdate[i]->next[i];
      toUpdate[i]->next[i] = newNode;
    }
  }
}

/**
 * Takes a vector of integers and adds them one by one
 * by calling the add(int val) method.
 *
 * @param values
 */
void SkipList::add(const vector<int> &values) {
  for (int i = 0; i < values.size(); i++) {
    add(values[i]);
  }
}

/**
 * Private method used by copy constructor
 * that forces a node to be present at a certain level.
 *
 * @param val
 * @param level
 */
void SkipList::forceInsertion(int val, int level) {
  vector<SNode *> toUpdate = getBeforeNodes(val);
  SNode *iter = toUpdate[0]->next[0];

  if (iter == nullptr || iter->val != val) {
    // same as add method except level is passed in rather than
    // randomly determined
    SNode *newNode = new SNode(val);
    newNode->next = vector<SNode *>(level + 1);

    for (int i = 0; i < level; i++) {
      newNode->next[i] = toUpdate[i]->next[i];
      toUpdate[i]->next[i] = newNode;
    }
  }
}

/**
 * Traverses top-down to find element to remove
 * If it's not present in list, return false;
 * Else, rechain level to level and delete the node.
 *
 * @param val
 * @return true
 * @return false
 */
bool SkipList::remove(int val) {
  vector<SNode *> toRm = getBeforeNodes(val);
  SNode *rm = toRm[0]->next[0];
  // val should be element in front of previous element via getBeforeNodes
  // if rm is nullptr or some other value, then val is not in list
  if (rm == nullptr || (rm != nullptr && rm->val != val)) {
    return false;
  }

  // perform rechaining similar to add method
  for (int i = levels - 1; i >= 0; i--) {
    if (toRm[i] != nullptr && toRm[i]->next[i] != nullptr) {
      toRm[i]->next[i] = rm->next[i];
    }
  }

  delete rm;
  rm = nullptr;

  return true;
}

/**
 * Overloaded << operator for the SkipList.
 * Adds to the ostream in level order from top to bottom,
 * left to right.
 *
 * @param out
 * @param skip
 * @return ostream&
 */
ostream &operator<<(ostream &out, const SkipList &skip) {

  // check for any data
  if (skip.head->next[0] == nullptr) {
    out << "Empty skiplist!\n";
    return out;
  }

  // start at first node
  SNode *currPtr = skip.head->next[0];

  // an attempt
  for (int i = skip.levels - 1; i >= 0; i--) { // loop until "at bottom" level

    out << "[level: " << i + 1 << "] ";

    // loop through list
    while (currPtr != nullptr) {
      // check if level 0 vector size of first node > levels
      if (currPtr->next.size() > i + 1) {
        out << currPtr->val << "-->";
      }

      currPtr = currPtr->next[0]; // traverse right one node
    }

    out << "nullptr";

    // set back to beginning
    currPtr = skip.head->next[0];
    out << endl;
  }

  currPtr = nullptr;
  return out;
}