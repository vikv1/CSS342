#include "tbtree.h"

TNode::TNode(int val, TNode *lft, TNode *rt)
    : val{val}, lftPtr{lft}, rtPtr{rt}, isThread(false){};

Tbtree::Tbtree() : curDepth{0}, maxDepth{0}, root{nullptr} {};

Tbtree::~Tbtree() = default;

void Tbtree::add(int val) {
  if (root == nullptr) {
    root = new TNode(val);
    return;
  }

  TNode *t = root;
  TNode *p = nullptr;
  while (t != nullptr) {
   
    p = t;
    if (val < t->val) {
      t = t->lftPtr;
    } else {
      if(!t->isThread) {
         t = t->rtPtr;
      } else {
         break;
      }
         
    }
  }
  // at this point, t is a nullptr and p is a leaf node

  TNode *n = nullptr;

  if (val < p->val) {
    n = new TNode(val, nullptr, p);
    n->isThread = true;
    p->lftPtr = n;
  } else {
    n = new TNode(val, nullptr, p->rtPtr);
    if (p->isThread) {
      n->isThread = true;
    }
    p->rtPtr = n;
    p->isThread = false;
  }
}

// Removes a value, returns true if successful
bool Tbtree::remove(int val) {
  val = 1; // jfdksklsdjkl
  // consider empty tree
  // consider one val
  // consider multi vals
  return false; // fjdksfdjksl
}

bool Tbtree::isEmpty() const { return (root == nullptr); }

bool Tbtree::isLeaf(const TNode &argNode) const {
  // null & threaded
  return (argNode.lftPtr == nullptr) &&
         ((argNode.isThread || argNode.rtPtr == nullptr));
}

TNode *Tbtree::searchTree(int val) const {
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
      iter = iter->rtPtr;
    }
  }

  return iter;
}

bool Tbtree::contains(int val) const { return searchTree(val) != nullptr; }

TNode *Tbtree::getRoot() const { return root; }

/*
cam:
clear()
destructor
operator<<
rethread
getInOrder Successor

getNumNodes

victor:
add - need to threading
getBeforeNode - after do threading
searchTree - dne i fink
contains - dme i tink
copy constructor


*/

void Iterator::inorderTraverse(TNode *cur) {
  if (cur != nullptr) {
    inorderTraverse(cur->lftPtr);
    cout << cur->val << endl;
    if (!cur->isThread) {
      inorderTraverse(cur->rtPtr);
    }
   //   else {
   //     cout << cur->val << " threaded to: " << cur->rtPtr << endl;
   //     }
  }
}