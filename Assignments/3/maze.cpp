//
//

#include "maze.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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

int Maze::getExitRow() const {
   return exitRow;
}

int Maze::getExitColumn() const {
   return exitColumn;
}

bool Maze::isClear(int Row, int Col) const {
   return Field[Row][Col] == ' ';
}

void Maze::markAsPath(int Row, int Col) {
   Field[Row][Col] = '*';
}

void Maze::markAsVisited(int Row, int Col) {
   Field[Row][Col] = '+';
}