#include <iostream>
#include "Node.h"

using namespace std;

class LinkedBag {

   public:
      Node* head = nullptr;
      LinkedBag(int data) {
         Node n(data);
         n.next = head;
         head = &n;
      }

      bool insert(Node &n) {
         if (head == NULL) {
            head = &n;
            return true;
         }

         Node* temp = head;
         while (temp->next!= NULL) {
            temp = temp->next;
         }
         temp->next = &n;
         return true;
      }

      void print() {
         Node* t = head;
         while(t->next != nullptr) {
            cout << t->data << endl;
            t = t->next;
         }
      }




};