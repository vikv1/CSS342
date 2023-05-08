#include "skiplist.h"

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

#include "random.h"

using namespace std;

// checks if the value needs to be inserted at a higher level
bool SkipList::shouldInsertAtHigherLevel() const {
   return probability >= Random::random() % 100;
}

// you code goes here
SNode::SNode(int val, int level) : val(val) {
   for (int i = 0; i < level; i++) {
      next.emplace_back(nullptr);
   }
}

SkipList::SkipList(int levels, int probability) :
    levels(levels), probability(probability) {}

int SkipList::curLevel(vector<SNode*>& v) const {
   int curLevel = 1;


   
   return curLevel;
}

