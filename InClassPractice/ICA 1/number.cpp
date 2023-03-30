#include <iostream>
using namespace std;

int main() 
{
   int max;

   //PRiNT ACTIVE MAX
   
   #if 1
   while(true) 
   {
      int a;

      std::cin >> a;


      if(a > max) 
      {
         max = a;
      }

      std::cout << max << std::endl;

   }
   #endif


   //PRINT MAX OF TWO NUMS
   #if 1
   int a;
   int b;

   cin >> a >> b;

   cout << ((a > b) ? a : b) << endl;

   #endif



   return 0;
}