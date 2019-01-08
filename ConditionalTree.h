#include <vector>
#include <iostream>
#include "ItemNode.h"
class ConditionalTree {
public:
  std::vector<ItemNode> items;
  void add(ItemNode item) {
    items.push_back(item);
  }
  ConditionalTree(ItemNode root){
    items.push_back(root);
  }
};
