#include <iostream>
using namespace std;

class Node {
   friend ostream& operator<<(ostream& os, const Node& n);
   public:
      Node* next = nullptr;
      int data;

      Node(int data, Node& next) {
         this->data = data;
         this->next = &next;
      }

      Node(int data) {
         this->data = data;
         this->next = nullptr;
      }

      Node(const Node& n) {
         this->data = n.data;
         this->next = n.next;
      }
};