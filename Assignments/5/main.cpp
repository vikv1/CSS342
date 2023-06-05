/**
 *
 * Threaded Binary Tree structure
 *             this isnrd
 * @authors Vikrant Verma, Cami Lacy
 *
 * 🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄🐄 MOOooooooo
 */

#include "tbtree.h"
#include <iostream>

int main() {

  int n = 0;
  cout << "input: ";
  cin >> n;
  cout << endl;

  TbsTree t(n);
  TbsTree t2(t);

   // remove all even from copy
  for (int i = 2; i <= n; i += 2) {
    t2.remove(i);
  }

  cout << "t2" << endl;
  Iterator i;
  i.inorderTraverse(t2.getRoot(), t2);

  cout << "t" << endl;
  cout << t << endl;

  return 0;
}