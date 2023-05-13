#include "skiplist.h"
#include "random.h"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <string.h>

using namespace std;

// node constructor vikraent == nrd
//                         cami != nrd nrd
SNode::SNode(int val) : val(val) { };

// checks if the value needs to be inserted at a higher level
bool SkipList::shouldInsertAtHigherLevel() const {
   return probability >= Random::random() % 100;
}

SkipList::~SkipList() {
   clear();
}

void SkipList::clear() {
   vector<SNode*> level0;
   SNode* iter = head->next[0];

   //get all nodes from bottom level
   while(iter != nullptr) {
      level0.push_back(iter);
      iter = iter->next[0];
   }

   for(int i = level0.size() - 1; i >= 0; i--) {
      remove(level0[i]->val);
   }

   delete head;
   head = nullptr;
}

// SkipList constructor
SkipList::SkipList(int levels, int probability) {
   this->levels = levels;
   this->probability = probability;


   head = new SNode(INT_MIN); // fjdksl
   head->next = vector<SNode*>(levels + 1);
   //tail = new SNode(INT_MAX); // need to initialize???
   // do we need tail ptr to check if reached end?


   // next.size - 1 == highest level, next[0] is 1st level
//    head->next.resize(levels, nullptr);
//    memset(head->next, 0, sizeof(SNode*)*(levels+1));
   //head->val = INT_MIN; //  this breaking meh CLION djkslfjdk

}

// copy constructor
SkipList::SkipList(const SkipList &other){

}




// return true if found in SkipList
bool SkipList::contains(int val) const{

// this funky logic disregard for now jfdkslfljs
   SNode *currPtr = head;

   // consider if no nodes?? i dunno if did rihght
   //if(head->next[0] == nullptr){ // disregrd compilr not hapy wit dis
   //    return false;
   //}


   // loop through head vector of SNodes* start at top-most level
   for(int i = levels; i > 0; i--){

      // loop through each SNodes* on each level?
      while(currPtr != nullptr){

         if(val == currPtr[i].val){
            return true;
         }

         currPtr = currPtr->next[i]; // bad this nullptr
      }

      // set back to beginning???
      currPtr = head; // funky

   }

   return false; // disregard fdjskflkjds

}


vector<SNode*> SkipList::getBeforeNodes(int val) const {
   SNode* iter = head;
   vector<SNode*> toUpdate(levels);

   for(int i = levels - 1; i >= 0; i--) {
      //move as far right on each level as possible

      while(iter->next[i] != nullptr && iter->next[i]->val < val) {
         iter = iter->next[i];
      }

      // element right before we dropped, need to change pointer
      toUpdate[i] = iter;
   }

   iter = iter->next[0];

   return toUpdate;
}

void SkipList::add(int val) {
   vector<SNode*> toUpdate = getBeforeNodes(val);
   SNode* iter = toUpdate[0]->next[0];
//    memset(toUpdate, 0, sizeof(SNode*)*(levels+1));

//    for(int i = levels; i >= 0; i--) {
//        //move as far right on each level as possible
//
//        while(iter->next[i] != nullptr && iter->next[i]->val < val) {
//            iter = iter->next[i];
//        }
//
//        // element right before we dropped, need to change pointer
//        toUpdate[i] = iter;
//    }

   // moooooo stuff  🐄            🐄
   // 🐄 i didnt know emojis could go 🐄in hrer u r COW CUS IM SO 🐄


   if(iter == nullptr || iter->val != val) {
      int newNodeLevel = 1;
      while(shouldInsertAtHigherLevel() && newNodeLevel < levels) {
         newNodeLevel++;

      }

//       if (newNodeLevel > curLevel) {
//          for (int i= curLevel + 1;i<newNodeLevel + 1;i++)
//             toUpdate[i] = head;
//
//          // Update the list current level
//          curLevel = newNodeLevel;
//       }


      string x = "🐄"; // cow

      SNode* newNode = new SNode(val);
      newNode->next = vector<SNode*>(newNodeLevel + 1);

//       memset(newNode->next, 0, sizeof(SNode*)*(newNodeLevel + 1));

      for(int i = 0; i < newNodeLevel; i++) {
         newNode->next[i] = toUpdate[i]->next[i];
         toUpdate[i]->next[i] = newNode;
      }


   }

   cout << "done" << endl;






//    for(int i = 0; i < sizeof(head->next) / sizeof(int); i++) {
//        cout << head->next[i]->val << ", ";
//    }



}

void SkipList::add(const vector<int> &values) {
   for(int i = 0; i < values.size(); i++) {
      add(values[i]);
   }
}

bool SkipList::remove(int val) {
   vector<SNode*> toRm = getBeforeNodes(val);
   SNode* rm = toRm[0]->next[0];
   if(rm == nullptr) {
      return false;
   }

   for(int i = levels - 1; i >= 0; i--) {
      if(toRm[i] != nullptr && toRm[i]->next[i] != nullptr) {
         toRm[i]->next[i] = rm->next[i];
      }
   }

   delete rm;
   rm = nullptr;
   

   return true;
}



/*

5: ----------------->9🐄
4: ----------------->9
3:--------->5------->9
2:----->3-->5-->7--->9
1:->1-->3-->5-->7--->9

*/
// operator<< for printing can access val directly ok thanks for the information
ostream& operator<<(ostream &out, const SkipList &skip){

// no worky stukcy on this for 267 hrs qsx tutr stuck too disregard dis
/*
    SNode* currPtr = skip.head; // funky

    // loop through head vector of SNodes*
    for(int i = skip.levels; i > 0; i--){

        out << i << ": " << endl; // output levels

        // loop through each SNodes* on each level?🐄
        while(currPtr != nullptr){
            currPtr = currPtr->next; // why it say ->next is privat wut
        }

        // set back to beginning???
        currPtr = skip.head[i]; // funky

    }

*/

   for (int i = skip.levels - 1; i >= 0; i--)
   {
      SNode *node = skip.head->next[i];
      cout << (i + 1) << ": ";
      while (node != nullptr)
      {
         cout << node->val << " ";
         node = node->next[i];
      }
      cout << "\n";
   }

   return out;

}