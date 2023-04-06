#include <iostream>
#include <unordered_map>
#include "string"
using namespace std;

void remove(string arr[], int s);
void print(string arr[]);

int main() {
   string arr[] = {"b", "a", "b", "b", "e", "f", "a"};

   int s = sizeof(arr)/sizeof(arr[0]);

   remove(arr, s);


   for (int i = 0; i < s; i++) {
     cout << arr[i];
   }

   cout << endl;

   
   
   return 0;
}

void remove(string arr[], int s) {
   for(int i = 0; i < s; i++) {
      string t = arr[i];

      for(int j = 0; j < s; j++) {
         if(j != i) {
            if(arr[j] == t) {
               arr[j] = arr[s-1];
               arr[s-1] = "X";
               s = s-1;

            }
         }
      }

   }
}

