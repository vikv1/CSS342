#include <cassert>
#include <iostream>

#include "creature.h"

void test() {
   Maze m("maze.txt");
   Creature c(4, 4);
   string path = c.solve(m);
   cout << "Path: " << path << endl;
   cout << m << endl;

   Maze m2("maze2.txt");
   Creature c2(4, 4);
   string path2 = c2.solve(m2);
   cout << "Path: " << path2 << endl;
   cout << m2 << endl;

   Maze m3("maze3.txt");
   Creature c3(1, 98);
   string path3 = c3.solve(m3);
   cout << "Path: " << path3 << endl;
   cout << m3 << endl;

   Maze m4("maze4.txt");
   Creature c4(1, 1);
   string path4 = c4.solve(m4);
   cout << "Path: " << path4 << endl;
   cout << m4 << endl;
}

int main() {
   test();
   cout << "Done!" << std::endl;
   return 0;
}