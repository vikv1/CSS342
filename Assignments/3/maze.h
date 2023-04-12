//
//
//

#ifndef ASS3_MAZE_H
#define ASS3_MAZE_H

#include <ostream>
#include <vector>

using namespace std;

enum CELL { CLEAR, WALL, PATH, VISITED };

class Maze {
   friend ostream &operator<<(ostream &Out, const Maze &Maze);
   friend class Creature;

 private:
   const static int MAX_SIZE = 100;
   char Field[MAX_SIZE][MAX_SIZE];
   vector<pair<int, int>> Path;
   int width, height;
   int exitRow, exitColumn;

 public:
   explicit Maze(const string &FileName);
   bool isClear(int Row, int Col) const;
   void markAsPath(int Row, int Col);
   void markAsVisited(int Row, int Col);
   int getExitRow() const;
   int getExitColumn() const;
};

#endif  // ASS3_MAZE_H
