//
//

#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include <iostream>

#include "maze.h"

/**
 * Creature class header
 * Allows for constructing a creature
 * Allows for solving a maze
 *
 */

class Creature {
 public:
   /*
    * Overloaded << operator to output creature location
    */
   friend ostream &operator<<(ostream &out, const Creature &creature);

   /*
    * Overloaded >> operator to create creature with "row, col" format
    */
   friend istream &operator>>(istream &in, Creature &creature);

   /*
    * Constructor that takes initial row and col
    */
   Creature(int Row, int Col);

   /*
    * Solves the maze
    */
   string solve(Maze &Maze);

 private:
   /*
    * The starting row of the creature
    */
   int row;

   /*
    * The starting col of the creature
    */
   int col;

   /*
    * The current row of the creature
    */
   int curRow;

   /*
    * The current row of the creature
    */
   int curCol;

   /*
    * The path to the exit of the maze in reverse order
    */
   string path;

   /*
    * Recursively solves the maze
    */
   void solveHelper(Maze &Maze, int row, int col);

   /*
    * Whether creature has foundExit yet
    */
   bool foundExit = false;

   /*
    * Whether the creature has returned to original pos
    * after examining all possible directions
    */
   bool crossedInitial = false;

   /*
    * Whether the creature is currently at the exit
    */
   bool atExit(const Maze &Maze, int row, int col) const;

   /*
    * Adds an "N" to path to go north
    */
   string goNorth();

   /*
    * Adds an "S" to path to go south
    */
   string goSouth();

   /*
    * Adds an "E" to path to go east
    */
   string goEast();

   /*
    * Adds an "W" to path to go west
    */
   string goWest();
};

#endif  // ASS3_CREATURE_H