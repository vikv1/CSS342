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

bool Creature::atExit(const Maze &Maze) const {
   return true;
}

void Creature::solveHelper(Maze &Maze, int row, int col) {
   if (Maze.Field[row][col] == 'x') {
      return;
   }

   if (Maze.Field[row][col] != '+') {
      Maze.Field[row][col] = '+';
      if (row == Maze.getExitRow() && col == Maze.getExitColumn()) {
         Maze.Field[row][col] = '*';
         foundExit = true;
         return;
      }
      if (!foundExit) solveHelper(Maze, row, col - 1);
      if (!foundExit) solveHelper(Maze, row, col + 1);
      if (!foundExit) solveHelper(Maze, row - 1, col);
      if (!foundExit) solveHelper(Maze, row + 1, col);
      
      
   }

   if (this->row == row && this->col == col && foundExit) {
      Maze.Field[row][col] = ' ';
      crossedInitial = true;
   }

   if (foundExit && !crossedInitial) {
      Maze.Field[row][col] = '*';
   }

   if (foundExit) {
      if (Maze.Field[row][col + 1] == '*') {
         path += "E";
      } else if (Maze.Field[row][col - 1] == '*') {
         path += "W";
      } else if (Maze.Field[row - 1][col] == '*') {
         path += "N";
      } else if (Maze.Field[row + 1][col] == '*') {
         path += "S";
      }
   }
}

string Creature::solve(Maze &Maze) {
   solveHelper(Maze, row, col);
   reverse(path.begin(), path.end());

   return this->path;
}

string Creature::goNorth(Maze &Maze) {
   Maze.Field[row][col] = '*';
   row -= 1;
   return "X";
}

string Creature::goWest(Maze &Maze) {
   Maze.Field[row][col] = '*';
   col -= 1;
   return "X";
}

string Creature::goEast(Maze &Maze) {
   Maze.Field[row][col] = '*';
   col += 1;
   return "X";
}

string Creature::goSouth(Maze &Maze) {
   Maze.Field[row][col] = '*';
   row += 1;
   return "X";
}