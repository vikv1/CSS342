/**
 *
 * Threaded Binary Tree structure
 *
 * @authors Vikrant Verma, Cami Lacy
 *
 * 🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄
 */

#include "tbtree.h"
#include <algorithm>
#include <queue>

/**
 * @brief Construct a new TNode::TNode object
 *
 * @param val
 * @param lft
 * @param rt
 */
TNode::TNode(int val, TNode *lft, TNode *rt)
    : val{val}, lftPtr{lft}, rtPtr{rt} {}

/**
 * @brief Construct a new Tbs Tree:: Tbs Tree object
 *
 */
TbsTree::TbsTree() : root{nullptr} {}

/**
 * @brief Construct a new Tbs Tree:: Tbs Tree object
 * Level order traversal to ensure ordering of nodes is correct
 * @param tree
 */
TbsTree::TbsTree(const TbsTree &tree) : root{nullptr} {
  if (tree.root != nullptr) {
    queue<TNode *> q;
    q.push(tree.root);

    while (!q.empty()) {
      TNode *t = q.front();
      q.pop();

      if (t->lftPtr != nullptr) {
        q.push(t->lftPtr);
      }
      if (t->rtPtr != nullptr && !t->isThread) {
        q.push(t->rtPtr);
      }

      add(t->val);
    }
  }
}

/**
 * @brief Construct a new Tbs Tree:: Tbs Tree object
 * Constructs a tree with nodes numbered 1 to n
 * Constructs a balanced tree
 * @param val
 */
TbsTree::TbsTree(int val) : root{nullptr} {
  vector<int> v;
  for (int i = 1; i <= val; i++) {
    v.push_back(i);
  }
  add(v);
}

/**
 * @brief Destroy the Tbs Tree:: Tbs Tree object
 *
 */
TbsTree::~TbsTree() { clear(); }

/**
 * @brief Clears all nodes
 *
 */
void TbsTree::clear() {
  vector<int> v;
  TNode *t = root;
  inorderTraverseToVector(t, v);

  for (int i = 0; i < v.size(); i++) {
    if (contains(v[i])) {
      remove(v[i]);
    }
  }
}

/**
 * Public way to delete all nodes
 *
 */
void TbsTree::deleteAll() { clear(); }

/**
 * @brief Adds a node to the tree
 *
 * @param val
 */
void TbsTree::add(int val) {
  if (root == nullptr) {
    root = new TNode(val);
    return;
  }

  if (contains(val)) {
    cout << "already present" << endl;
    return;
  }

  TNode *t = root;
  TNode *p = nullptr;

  while (t != nullptr) {
    if (t->val == val) {
    }
    p = t;
    if (val < t->val) {
      t = t->lftPtr;
    } else {
      if (!t->isThread) {
        t = t->rtPtr;
      } else {
        break;
      }
    }
  }

  TNode *n = nullptr;

  // redoes pointers to insert into tree
  if (val < p->val) {
    n = new TNode(val, nullptr, p);
    n->isThread = true;
    p->lftPtr = n;
  } else {
    n = new TNode(val, nullptr, p->rtPtr);
    // n will take p's thread if it becomes right child
    if (p->isThread) {
      n->isThread = true;
    }
    p->rtPtr = n;
    p->isThread = false;
  }
}

/**
 * Adds a vector of values
 *
 * @param vals
 */
void TbsTree::add(vector<int> &vals) { add(vals, 0, vals.size() - 1); }

/**
 * Adds a vector of vals by adding middle of each half recursively
 *
 * @param vals
 * @param start
 * @param end
 * @return TNode*
 */
TNode *TbsTree::add(vector<int> &vals, int start, int end) {
  if (start <= end) {
    int mid = end + ((start - end) / 2);

    add(vals[mid]);

    add(vals, start, mid - 1);

    add(vals, mid + 1, end);
  }

  return nullptr;
}

/**
 * @brief Checks if tree is empty
 *
 * @return true
 * @return false
 */
bool TbsTree::isEmpty() const { return (root == nullptr); }

/**
 * Searches tree for a val
 *
 * @param val
 * @return TNode*
 */
TNode *TbsTree::searchTree(int val) const {
  TNode *iter = root;
  if (iter == nullptr) {
    return nullptr;
  }

  while (iter != nullptr) {
    if (val == iter->val) {
      break;
    } else if (val < iter->val) {
      iter = iter->lftPtr;
    } else {
      if (!iter->isThread) {
        iter = iter->rtPtr;
      } else {
        iter = nullptr;
        break;
      }
    }
  }

  return iter;
}

/**
 * @brief Checks if tree contains a value
 *
 * @param val
 * @return true
 * @return false
 */
bool TbsTree::contains(int val) const { return searchTree(val) != nullptr; }

/**
 * Returns root
 *
 * @return TNode*
 */
TNode *TbsTree::getRoot() const { return root; }

/**
 * Returns inorder traversal as a vector, used privately
 *
 * @param cur
 * @param v
 */
void TbsTree::inorderTraverseToVector(TNode *cur, vector<int> &v) const {
  if (cur != nullptr) {
    if (cur->lftPtr != nullptr)
      inorderTraverseToVector(cur->lftPtr, v);
    v.push_back(cur->val);
    if (cur->rtPtr != nullptr && !cur->isThread) {
      inorderTraverseToVector(cur->rtPtr, v);
    }
  }
}

/**
 * @brief Inorder traversal
 *
 * @param cur
 */
void Iterator::inorderTraverse(TNode *cur, TbsTree &t) {
  // empty tree
  if (cur == nullptr) {
    cout << "empty" << endl;
    return;
  }

  // one node
  else if ((cur->lftPtr == nullptr) && (cur->rtPtr == nullptr)) {
    cout << cur->val << " ";
  }

  else {
    // get to further left node
    while (cur->lftPtr != nullptr) {
      cur = cur->lftPtr;
    }

    // traversing to next largest value
    while (cur != nullptr) {
      cout << cur->val << " ";
      cur = t.getInOrderSuccessor(cur);
    }
  }

  cout << endl;
}

/**
 * @brief Gets in order successor of a node
 *
 * @param argNode
 * @return TNode*
 */
TNode *TbsTree::getInOrderSuccessor(TNode *argNode) const {
  if (argNode->isThread) {
    // if threaded then just follow thread
    return argNode->rtPtr;
  } else {
    argNode = argNode->rtPtr;
    // left most node in right subtree is inorder successor
    while (argNode != nullptr && argNode->lftPtr != nullptr) {
      argNode = argNode->lftPtr;
    }
  }

  return argNode;
}

/**
 * @brief Returns max node in subtree
 *
 * @param start
 * @return TNode*
 */
TNode *TbsTree::maxNode(TNode *start) const {
  while (start->rtPtr != nullptr && !start->isThread) {
    start = start->rtPtr;
  }

  return start;
}

/**
 * @brief Returns inorder predecessor to node
 *
 * @param root
 * @param node
 * @return TNode*
 */
TNode *TbsTree::findPredecessor(TNode *start, TNode *node) const {
  if (start == nullptr) {
    return nullptr;
  }

  TNode *pred = nullptr;

  while (start != nullptr) {
    if (node->val < start->val) {
      start = start->lftPtr;
    } else if (node->val > start->val) {
      pred = start;
      if (!start->isThread) {
        start = start->rtPtr;
      } else {
        start = nullptr;
      }
    } else {
      if (start->lftPtr != nullptr) {
        pred = maxNode(start->lftPtr);
      }

      break;
    }
  }

  return pred;
}

/**
 * @brief << overload to print inorder contents of tree using threads
 *
 * @param out
 * @param argTree
 * @return ostream&
 */
ostream &operator<<(ostream &out, const TbsTree &argTree) {

  TNode *curPtr = argTree.root;

  // empty tree
  if (curPtr == nullptr) {
    return out;
  }

  else {
    // get to further left node
    while (curPtr->lftPtr != nullptr) {
      curPtr = curPtr->lftPtr;
    }

    // traversing to next largest value
    while (curPtr != nullptr) {
      out << curPtr->val << " ";
      curPtr = argTree.getInOrderSuccessor(curPtr);
    }
  }

  out << endl;
  return out;
}

/**
 * @brief Returns height of the tree
 *
 * @return int
 */
int TbsTree::getHeight() { return (heightHelper(root)); }

/**
 * @brief Level order traversal to determine tree height
 *
 * @param argNode
 * @return int
 */
int TbsTree::heightHelper(TNode *argNode) const {
  if (root == nullptr) {
    return 0;
  } else if (root->lftPtr == nullptr && root->rtPtr == nullptr) {
    return 1;
  }

  int levels = 0;
  queue<TNode *> q;
  q.push(argNode);

  while (!q.empty()) {
    levels++;
    for (int i = 0; i < q.size(); i++) {
      if (q.front()->lftPtr != nullptr) {
        q.push(q.front()->lftPtr);
      }

      if (q.front()->rtPtr != nullptr && !q.front()->isThread) {
        q.push(q.front()->rtPtr);
      }

      q.pop();
    }
  }

  return levels;
}

/**
 * @brief Returns number of nodes in tree
 *
 * @return int
 */
int TbsTree::getNumNodes() const { return numNodesHelper(root, 0); }

/**
 * @brief Recursively counts all nodes in tree
 *
 * @param curNode
 * @param countNodes
 * @return int
 */
int TbsTree::numNodesHelper(TNode *curNode, int countNodes) const {
  // check if node nullptr
  if (curNode != nullptr) {
    countNodes++;

    // Checks node left
    countNodes = numNodesHelper(curNode->lftPtr, countNodes);

    // Checks node right
    if (!(curNode->isThread)) {
      countNodes = numNodesHelper(curNode->rtPtr, countNodes);
    }
  }
  return countNodes;
}

/**
 * @brief Removes a value from the tree
 *
 * @param val
 * @return true
 * @return false
 */
bool TbsTree::remove(int val) {
  if (!(contains(val))) {
    return false;
  }
  root = removeHelper(root, val);

  return true;
}

/**
 * Removes the node with val from the tree and rethreads
 *
 * @param root
 * @param val
 * @return TNode*
 */
TNode *TbsTree::removeHelper(TNode *root, int val) {
  TNode *p = nullptr;
  TNode *t = root;

  // p is the parent of t
  //  t is node to be removed

  if (!contains(val)) {
    cout << "not present" << endl;
    return root;
  }

  bool found = false;

  while (t != nullptr) {
    if (t->val == val) {
      found = true;
      break;
    }

    p = t;

    if (val < t->val) {
      t = t->lftPtr;
    }

    else {
      if (!t->isThread) {
        t = t->rtPtr;
      } else {
        break;
      }
    }
  }

  if (!found) {
    cout << "not found" << endl;
  }

  else if (t->lftPtr != nullptr && !t->isThread) {
    root = ifTwoChild(root, t);
  }

  else if (!t->isThread) {
    root = ifOneChild(root, t, p);
  }

  // if leaf
  else {
    root = ifLeaf(root, t, p);
  }

  return root;
}

/**
 * Removal case for when node is a leaf
 *
 * @param root
 * @param t - node to be removed
 * @param p - parent of node to be removed
 * @return TNode*
 */
TNode *TbsTree::ifLeaf(TNode *root, TNode *t, TNode *p) {
  // parent is nullptr only if removing root
  if (p == nullptr) {
    delete root;
    root = nullptr;
    return root;
  } else if (t == p->lftPtr) {
    p->lftPtr = t->lftPtr;
    // if lftptr is threaded, it will be pointing to invalid location t
    // rethreads it
    if (p->lftPtr != nullptr &&
        (p->lftPtr->isThread || p->lftPtr->rtPtr == nullptr)) {
      p->lftPtr->rtPtr = p;
    }

  } else {
    p->rtPtr = t->rtPtr;
    if (p->rtPtr != nullptr) {
      // if rtptr is greater than val, then must be threaded
      if (p->rtPtr->val > p->val) {
        p->isThread = true;
      }
    }
  }

  delete t;

  return root;
}

/**
 * @brief Removal case if node has 2 children
 *
 * @param root - root of tree
 * @param t - node to be removed
 * @return TNode*
 */
TNode *TbsTree::ifTwoChild(TNode *root, TNode *t) {
  // successor to t
  TNode *successor = nullptr;

  // parent of successor to t
  TNode *parentSuccessor = nullptr;

  parentSuccessor = t;
  // go to right subtree of t
  successor = t->rtPtr;

  // get in order successor/minimum in right subtree
  while (successor != nullptr && successor->lftPtr != nullptr) {
    parentSuccessor = successor;
    successor = successor->lftPtr;
  }

  // swap values of t and the successor
  t->val = successor->val;

  // removes the successor node according to whether it is a leaf or one child
  if (successor->lftPtr == nullptr &&
      (successor->rtPtr == nullptr || successor->isThread)) {
    root = ifLeaf(root, successor, parentSuccessor);
  } else {
    root = ifOneChild(root, successor, parentSuccessor);
  }

  return root;
}

/**
 * @brief Removal case for if node has one child
 *
 * @param root
 * @param t - node to be removed
 * @param p - parent of node to be removed
 * @return TNode*
 */
TNode *TbsTree::ifOneChild(TNode *root, TNode *t, TNode *p) {
  TNode *directChild = nullptr;

  // sets directchild to child of t
  if (t->lftPtr != nullptr) {
    directChild = t->lftPtr;
  } else {
    directChild = t->rtPtr;
  }

  // parent is only null if rm'ing root
  if (p == nullptr) {
    root = directChild;
  } else if (t == p->lftPtr) {
    p->lftPtr = directChild;
  } else {
    p->rtPtr = directChild;
  }

  TNode *successor = getInOrderSuccessor(t);
  TNode *predecessor = findPredecessor(this->root, t);

  // rethreads predecessor to successor of t if needed
  if (predecessor != nullptr && predecessor->isThread) {
    predecessor->rtPtr = successor;
  }

  delete t;

  return root;
}