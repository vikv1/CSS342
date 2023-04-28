//
//

#include "maze.h"

#include <fstream>
#include <iostream>
#include <string>

/**
 * Maze implementation
 * Allows for checking the property of a row, col in the maze
 * Stores the maze in a 2d array
 */

using namespace std;

/**
 * Outputs the string representation of the 2D array
 * in which the maze is stored
 * 
 * @param Out 
 * @param Maze 
 * @return ostream& 
 */
ostream &operator<<(ostream &Out, const Maze &Maze) {
   for (int row = 0; row < Maze.height; ++row) {
      for (int col = 0; col < Maze.width; ++col) {
         Out << Maze.Field[row][col];
      }
      Out << endl;
   }
   Out << endl;
   return Out;
}

// For Clion, need the following line in CMakeLists.txt so maze.txt is found
// at the same location as the cpp files
// # need to load data files from current directory as cpp files
// set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
/**
 * Constructs a maze from a text file, using a 2D array
 * 
 * @param FileName 
 */
Maze::Maze(const string &FileName) {
   ifstream inFile;
   inFile.open(FileName);
   if (!inFile) {
      cout << "Unable to open file";
      exit(1);  // terminate with error
   }
   inFile >> width >> height;
   inFile >> exitRow >> exitColumn;
   string str;
   getline(inFile, str);
   for (int row = 0; row < height; ++row) {
      for (int col = 0; col < width; ++col) {
         inFile.get(Field[row][col]);
         // cout << Row << ", " << col << ": " << field[Row][col] << endl;
      }
      getline(inFile, str);
   }
}

/**
 * Returns exit row
 * 
 * @return int 
 */
int Maze::getExitRow() const {
   return exitRow;
}

/**
 * Returns exit col
 * 
 * @return int 
 */
int Maze::getExitColumn() const {
   return exitColumn;
}

/**
 * Returns if the row and col is clear
 * 
 * @param Row 
 * @param Col 
 * @return true 
 * @return false 
 */
bool Maze::isClear(int Row, int Col) const {
   return Field[Row][Col] == ' ';
}

/**
 * Marks the row and col as the path
 * 
 * @param Row 
 * @param Col 
 */
void Maze::markAsPath(int Row, int Col) {
   Field[Row][Col] = '*';
}

/**
 * Returns if the row and col is the path
 * 
 * @param Row 
 * @param Col 
 * @return true 
 * @return false 
 */
bool Maze::isPath(int Row, int Col) const {
   return Field[Row][Col] == '*';
}

/**
 * Returns if the row and col is a wall
 * 
 * @param Row 
 * @param Col 
 * @return true 
 * @return false 
 */
bool Maze::isWall(int Row, int Col) const {
   return Field[Row][Col] == 'x';
}

/**
 * Marks the row and col as visited
 * 
 * @param Row 
 * @param Col 
 */
void Maze::markAsVisited(int Row, int Col) {
   Field[Row][Col] = '+';
}
