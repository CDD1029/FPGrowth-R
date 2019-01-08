#include <vector>
#include <iostream>
#include "ItemNode.h"
class ConditionalTree {
public:
  std::vector<ItemNode> items;
  int number;
  void add(ItemNode item) {
    items.push_back(item);
  }
  ConditionalTree(int x){
    
  }
  void add(int x){
    number = x;
  }
  int sub(){
    return number;
  }
};
