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
      if (!foundExit) solveHelper(Maze, row, col - 1);
      if (!foundExit) solveHelper(Maze, row, col + 1);
      if (!foundExit) solveHelper(Maze, row - 1, col);
      if (!foundExit) solveHelper(Maze, row + 1, col);
      
      
   }

   if (this->row == row && this->col == col && foundExit) {
      Maze.clear(row, col);
      crossedInitial = true;
   }

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
   solveHelper(Maze, row, col);
   reverse(path.begin(), path.end());

   return this->path;
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