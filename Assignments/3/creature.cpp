//
//

#include "creature.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

std::ostream &operator<<(std::ostream &Out, const Creature &Creature) {
   return Out;
}

Creature::Creature(int Row, int Col) : row(Row), col(Col) {}

bool Creature::atExit(const Maze &Maze, int row, int col) const {
   return row == Maze.getExitRow() && col == Maze.getExitColumn();
}

void Creature::solveHelper(Maze &Maze, int row, int col) {
   if (!(Maze.isClear(row, col)/**Maze.Field[row][col] == 'x'*/)) {
      return;
   }

   if (!(Maze.isVisited(row,col))) {
      Maze.markAsVisited(row, col);
      if (atExit(Maze, row, col)) {
         Maze.markAsPath(row, col);
         foundExit = true;
         return;
      }
      
      // greater risk of stack overflow if keep searching after exit found
      if (!foundExit) solveHelper(Maze, row, col - 1);
      if (!foundExit) solveHelper(Maze, row, col + 1);
      if (!foundExit) solveHelper(Maze, row - 1, col);
      if (!foundExit) solveHelper(Maze, row + 1, col);
      
      
   }

   if (this->row == row && this->col == col) {
      Maze.clear(row, col);
      crossedInitial = true;
   }

   // if all recursive calls finish and we are back to initial call
   // and exit still not found, then it doesnt exist
   if (!foundExit && crossedInitial) {
      cerr << "unsolvable" << endl; 
      return;
   }

   // if all recursive calls finish and exit found,
   // change + to * on the way back to initial location
   if (foundExit && !crossedInitial) {
      Maze.markAsPath(row, col);
   }



   if (foundExit) {
      if (Maze.isPath(row, col + 1)) {
         path += goEast(Maze);
      } else if (Maze.isPath(row, col - 1)) {
         path += goWest(Maze);
      } else if (Maze.isPath(row - 1, col)) {
         path += goNorth(Maze);
      } else if (Maze.isPath(row + 1, col)) {
         path += goSouth(Maze);
      }
   }
}

string Creature::solve(Maze &Maze) {
   if(Maze.isWall(row, col)) {
      cerr << "creature placed on wall" << endl;
      return path;
   } else {
      solveHelper(Maze, row, col);
      reverse(path.begin(), path.end());
   }

   string t = path;
   path = "";
   

   return t;
}

string Creature::goNorth(Maze &Maze) {
   return "N";
}

string Creature::goWest(Maze &Maze) {
   return "W";
}

string Creature::goEast(Maze &Maze) {
   return "E";
}

string Creature::goSouth(Maze &Maze) {
   return "S";
}