/**
 *
 * Threaded Binary Tree structure
 *
 * @authors Vikrant Verma, Cami Lacy
 *
 * 🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄
 */

#include "tbtree.h"

TNode::TNode(int val, TNode *lft, TNode *rt)
    : val{val}, lftPtr{lft}, rtPtr{rt}, isThread(false){};

TbsTree::TbsTree() : curDepth{0}, maxDepth{0}, root{nullptr} {};

TbsTree::~TbsTree() = default;

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

bool TbsTree::isEmpty() const { return (root == nullptr); }

bool TbsTree::isLeaf(const TNode &argNode) const {
  // null & threaded
  return (argNode.lftPtr == nullptr) &&
         ((argNode.isThread || argNode.rtPtr == nullptr));
}

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

TNode *TbsTree::searchParentOf(int val) const {
  TNode *iter = root;
  if (iter == nullptr) {
    return nullptr;
  }

  while (iter != nullptr) {
    if (val == iter->val) {
      break;
    } else if (val < iter->val) {
      if (iter->lftPtr->val == val) {
        break;
      }
      iter = iter->lftPtr;
    } else {
      if (!iter->isThread) {
        if (iter->rtPtr->val == val) {
          break;
        }
        iter = iter->rtPtr;
      } else {
        iter = nullptr;
        break;
      }
    }
  }

  return iter;
}

bool TbsTree::contains(int val) const { return searchTree(val) != nullptr; }

TNode *TbsTree::getRoot() const { return root; }

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
    // else {
    //   cout << cur->val << " threaded to: " << cur->rtPtr << endl;
    //   }
  }
}

// cami spaz code stufsfjdkslkljfdkljfsdkljsdjkl

int TbsTree::getHeight() { // ---> this no wrky rn
  return (heightHelper(root));
}

int TbsTree::heightHelper(const TNode *argNode) {
  if (argNode != nullptr) {
    curDepth++;
    heightHelper(argNode->lftPtr);

    if (!(argNode->isThread)) {
      heightHelper(argNode->rtPtr);
    }

    if (curDepth > maxDepth) {
      maxDepth = curDepth;
    }

    curDepth--;
  }

  curDepth = 0;
  int t = maxDepth;
  maxDepth = 0;

  return t;
}

int TbsTree::getNumNodes() const {

  return numNodesHelper(root, 0); // jklfdjsklfds
}

int TbsTree::numNodesHelper(TNode *curNode, int countNodes) const {
  // check if node nullptr
  if (curNode != nullptr) {
    countNodes++;

    // Checks node left
    countNodes = numNodesHelper(curNode->lftPtr, countNodes);

    // Checks node right, forgot about threading ack
    if (!(curNode->isThread)) {
      countNodes = numNodesHelper(curNode->rtPtr, countNodes);
    }
  }
  return countNodes;
}

// Removes a value, returns true if successful
bool TbsTree::remove(int val) {

  // empty tree or value not in tree
  if ((root == nullptr) || (!(contains(val)))) {
    return false;
  } // WHERE COWS??? FR!!!!!!!!!!!!!!!!!
    // W==L      METHOD
    TNode* parent = searchParentOf(val);
  TNode *removeNode = searchTree(val);

  // if removing root with no children
  if (removeNode->val == root->val) { // ---> valgrind goud
    if ((root->lftPtr == nullptr) && (root->rtPtr == nullptr)) {
      delete removeNode;
      removeNode = nullptr;
      return true;
    }

    // if removing root with only left subtree  ---> valgrind still vry unhappy
    else if (root->rtPtr == nullptr) {

      // left child is now root
      TNode *updateRoot = root->lftPtr;
      updateRoot->rtPtr = nullptr;
      updateRoot->isThread = false;

      // deletion
      root->lftPtr = nullptr;
      delete root;
      root = updateRoot;

      return true;
    }

    // if removing root with only right subtree  ---> valgrind still vry unhappy
    else if (root->lftPtr == nullptr) {

      // right child is now root
      root = removeNode->rtPtr;

      // deletion
      removeNode->rtPtr = nullptr;
      delete removeNode;
      removeNode = nullptr;
      return true;
    }
  }

  // if removing right most leaf with a left child

  // if removing right most leaf with a null children both

  // if removing leaf with no children (null/threaded)

  //          INENUDIASHJdiaujsdsaio  MINE         MINE MINE MINE
  // if removing leaf with both children
  if (!removeNode->isThread && removeNode->lftPtr != nullptr &&
      removeNode->rtPtr != nullptr) {
    removeNode->val = removeNode->rtPtr->val;
    TNode *rm = removeNode->rtPtr;
    removeNode->rtPtr = rm->rtPtr;
    delete rm;
    rm = nullptr;
  }

  // if removing leaf with left child/isThreaded
  else if (removeNode->lftPtr != nullptr) {
    TNode *rm = removeNode->lftPtr;
    TNode *p = nullptr;
    while (rm != nullptr && !rm->isThread) {
      p = rm;
      rm = rm->rtPtr;
    }

    removeNode->val = rm->val;
    p->rtPtr = nullptr;

    delete rm;
    rm = nullptr;

  }

  // if removing leaf with right child/no left child
  else {
    
  }

  return false; // fjdksfdjksl
}