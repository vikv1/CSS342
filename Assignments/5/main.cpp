/**
 *
 * Threaded Binary Tree structure
 *             this isme          nrd
 * @authors Vikrant Verma, Cami Lacy
 *
 * 🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄 MOO
 */

#include "tbtree.h"
#include <iostream>

int main() {

  TbsTree t;

  t.add(1);
  //   t.add(2);
  //   t.add(1);
  t.add(4);
  t.add(2);
  t.add(3);

  Iterator i;
  //   i.inorderTraverse(t.getRoot());

  t.remove(4);

  i.inorderTraverse(t.getRoot());

  return 0;
}