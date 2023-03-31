#include <iostream>
#include <string>
using namespace std;

void swap(string& a, string& b)
{
   cout << "original: " << a << " " << b << "\n";
   string t = a;
   a = b;
   b = t;
   cout << "after: " << a << " " << b << "\n";

}

int main() 
{
   string a = "a";
   string b = "b";
   swap(a, b);
   

   return 0;
}