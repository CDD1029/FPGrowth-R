#ifndef RULENODE
#define RULENODE
#include <vector>
#include <iostream>
class RuleNode {
private:
  int value;
public:
  std::vector<bool> items;
  void add(int index) {
    items.at(index) = true;
  }
  void setValue(int val){
    value = val;
  }
  RuleNode(int totItems){
    items.push_back(false);
  }
};
#endif