//
//

#include "creature.h"

#include <algorithm>
#include <sstream>
#include <string>

/**
 * Creature class implementation
 * Recursively solves a maze
 *
 */

using namespace std;

/**
 * Overloads the << operator to print current location in (row, col) format
 *
 * @param out
 * @param creature
 * @return ostream&
 */
ostream &operator<<(ostream &out, const Creature &creature) {
   return out << "C(" << creature.curRow << ", " << creature.curCol << ")";
}

/**
 * Overloads the >> operator to accept user input in the form:
 * "row, col"
 *
 * @param out
 * @param creature
 * @return istream&
 */
istream &operator>>(istream &in, Creature &creature) {
   string input;
   getline(cin, input);
   istringstream s(input);

   string temp;
   int row = -1;
   int col = -1;
   while (s >> temp) {
      if (temp == ",") {
         continue;
      } else {
         if (row == -1) {
            row = stoi(temp);
         } else {
            col = stoi(temp);
         }
      }
   }

   creature = Creature(row, col);
   return in;
}

/**
 * Constructor that takes a starting row and col
 *
 * @param Row
 * @param Col
 */
Creature::Creature(int Row, int Col) :
    row(Row), col(Col), curRow(Row), curCol(Col) {}

/**
 * Returns true if the current row and col is the exit location.
 * False otherwise.
 *
 * @param Maze
 * @param row
 * @param col
 * @return true
 * @return false
 */
bool Creature::atExit(const Maze &Maze, int row, int col) const {
   return row == Maze.getExitRow() && col == Maze.getExitColumn();
}

/**
 * Recursively solves the maze.
 * The row and col parameters given intially is the starting location.
 *
 * The function recursively calls itself to iterate through the maze,
 * thus the row and col parameters are automatically adjusted when backtracking.
 *
 * The algorithm the function uses is a depth first search,
 * where it tries to go as far west as possible,
 * then east (if it didn't just come from there),
 * north, and south, in that order.
 *
 * The reason it tries going east right after going west,
 * is because otherwise the path would result in a zigzagging
 * formation, which would be confusing to look when the maze is output
 * in this format.
 *
 * Only builds the path once exit is found.
 *
 * @param Maze
 * @param row
 * @param col
 */
void Creature::solveHelper(Maze &Maze, int row, int col) {
   // if we are on a wall or visited spot, end the call and go back
   if (!(Maze.isClear(row, col))) {
      return;
   }
   // if space hasn't been visited, mark it as visited, check if at exit
   // and go other directions
   else {
      curRow = row;
      curCol = col;
      Maze.markAsVisited(row, col);
      if (atExit(Maze, row, col)) {
         // mark the empty space as path
         Maze.markAsPath(row, col);
         foundExit = true;
         return;
      }

      // no point searching after exit found
      // need separate if statements because recursion will
      // continue where it left off even inside conditionals
      if (!foundExit) solveHelper(Maze, row, col - 1);
      if (!foundExit) solveHelper(Maze, row, col + 1);
      if (!foundExit) solveHelper(Maze, row - 1, col);
      if (!foundExit) solveHelper(Maze, row + 1, col);
   }

   // if all recursive calls finish and exit found,
   // change + to * on the way back to initial location
   if (foundExit && !crossedInitial) {
      Maze.markAsPath(row, col);
   }

   // if temp row and col == starting row col
   // then all above recursive calls have finished
   if (this->row == row && this->col == col) {
      crossedInitial = true;
   }

   // if all recursive calls finish and we are back to initial call
   // and exit still not found, then it doesnt exist
   if (!foundExit && crossedInitial) {
      cerr << "unsolvable" << endl;
      return;
   }

   // while backtracking, tell the path to
   // goEast, west, north, or south depending on
   // where backtracking from
   if (foundExit) {
      if (Maze.isPath(row, col + 1)) {
         path += goEast();
      } else if (Maze.isPath(row, col - 1)) {
         path += goWest();
      } else if (Maze.isPath(row - 1, col)) {
         path += goNorth();
      } else if (Maze.isPath(row + 1, col)) {
         path += goSouth();
      }
   }
}

/**
 * Method that allows the user to tell a creature to solve its maze.
 *
 * Solving is done by the solveHelper method.
 *
 * If creature is placed on a wall, cerr to let user know
 *
 * Reverses the path class variable because it gets built backwards
 * by the solveHelper method
 *
 * Return a temp string so the path class var can be wiped and
 * the creature can be reused
 * @param Maze
 * @return string
 */
string Creature::solve(Maze &Maze) {
   if (Maze.isWall(row, col)) {
      cerr << "creature placed on wall" << endl;
      return path;
   } else {
      solveHelper(Maze, row, col);

      // reverse the path because it was built backwards
      // from exit to spawn
      reverse(path.begin(), path.end());
   }

   string t = path;

   // empty the path so the creature can be reused
   path = "";

   return t;
}

/**
 * goNorth function used for building the path
 * e.g. tells the path to say go north
 * @return string
 */
string Creature::goNorth() {
   return "N";
}

/**
 * goWest function used for building the path
 * e.g. tells the path to say go west
 * @return string
 */
string Creature::goWest() {
   return "W";
}

/**
 * goEast function used for building the path
 * e.g. tells the path to say go east
 * @return string
 */
string Creature::goEast() {
   return "E";
}

/**
 * goSouth function used for building the path
 * e.g. tells the path to say go south
 * @return string
 */
string Creature::goSouth() {
   return "S";
}