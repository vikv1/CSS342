//
//

#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include <ostream>

#include "maze.h"

class Creature {
 public:
   friend ostream &operator<<(ostream &Out, const Creature &Creature);

 private:
   int row;
   int col;
   string path;
   void solveHelper(Maze &Maze, int row, int col);
   bool foundExit = false;
   bool crossedInitial = false;

 public:
   Creature(int Row, int Col);
   string solve(Maze &Maze);
   


   //IMPLEMENT
   bool atExit(const Maze &Maze, int row, int col) const;
   string goNorth(Maze &Maze);
   string goSouth(Maze &Maze);
   string goEast(Maze &Maze);
   string goWest(Maze &Maze);
};

#endif  // ASS3_CREATURE_H