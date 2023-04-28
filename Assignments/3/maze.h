//
//
//

#ifndef ASS3_MAZE_H
#define ASS3_MAZE_H

#include <ostream>
#include <vector>

/**
 * Maze header
 * Generates a maze from text file
 *
 */

using namespace std;

class Maze {
   /*
    * Overloaded << operator that outputs the maze
    */
   friend ostream &operator<<(ostream &Out, const Maze &Maze);

 private:
   /*
    * Max size of the maze
    */
   const static int MAX_SIZE = 100;

   /*
    * The 2D array representation of the maze
    */
   char Field[MAX_SIZE][MAX_SIZE];

   /*
    * Width and height of the maze
    */
   int width, height;

   /*
    * Where the exit is located
    */
   int exitRow, exitColumn;

 public:
   /*
    * Constructor that takes in a file
    */
   explicit Maze(const string &FileName);

   /*
    * Returns if the space is empty
    */
   bool isClear(int Row, int Col) const;

   /*
    * Returns if the current space is part of the path
    */
   bool isPath(int Row, int Col) const;

   /*
    * Returns if the current space is a wall
    */
   bool isWall(int Row, int Col) const;

   /*
    * Marks a location as part of the path
    */
   void markAsPath(int Row, int Col);

   /*
    * Marks a location as visited
    */
   void markAsVisited(int Row, int Col);

   /*
    * Returns the exit row
    */
   int getExitRow() const;

   /*
    * Returns the exit column
    */
   int getExitColumn() const;
};

#endif  // ASS3_MAZE_H
