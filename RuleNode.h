#ifndef RULENODE
#define RULENODE
#include <vector>
#include <iostream>
class RuleNode {
private:
  int value;
public:
  std::vector<int> items;
  void add(int item) {
    items.push_back(item);
  }
  void setValue(int val){
    value = val;
  }
  
};
#endif