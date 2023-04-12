#include <iostream>

#include "creature.h"
#include "maze.h"
#include <cassert>

void test() {
   Maze m("maze.txt");
   Creature c(4, 4);
   string path = c.solve(m);
   cout << "Path: " << path << endl;
   cout << m << endl;

   // assert(path == "EEENNNEEEEEESEESSSEEENNNNN");
}

int main() {
   test();
   cout << "Done!" << std::endl;
   return 0;
}