#include "tbtree.h"
#include <iostream>

int main() {

  Tbtree t;

  t.add(5);
  //   t.add(2);
  //   t.add(1);
  t.add(4);
  t.add(2);
  t.add(3);

  Iterator i;
  i.inorderTraverse(t.getRoot());

  return 0;
}