#include <iostream>

using namespace std;

void helper(int, int);
void TruthTable(int, const string&);

int main() {
   string s = "";
   TruthTable(3,s);

   return 0;
}


void TruthTable(int n, const string& sofar) {
   if(n <= 1) {
      cout << sofar << "T" << endl;
      cout << sofar << "F" << endl;
   } else {
      TruthTable(n - 1, sofar + "T");
      TruthTable(n - 1, sofar + "F");
   }

}

// void helper(int n, int startingN) {
//    if(n == 0) {
//       for(int i = 0; i < startingN; i++) {
//          cout << "T";
//       }
//       cout << endl;
//    } else {
//       if(n == startingN) {
//          for(int i = 0; i < startingN; i++) {
//             cout << "F";
//          }
//          cout << endl;
//       }

//       helper(n - 1, startingN);



//    }


// }