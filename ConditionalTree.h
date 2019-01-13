#include <vector>
#include <iostream>
#include "ItemNode.h"
#include "RuleNode.h"
class ConditionalTree {
private:
  int lastNodeLocation;
  int endingID;
public:
  std::vector<ItemNode> items;
  
  void add(int itemID, int numItems, RuleNode currentRule) {
    if(items.at(lastNodeLocation).itemAlreadyInModel(itemID)) {
      lastNodeLocation = items.at(lastNodeLocation).findNextNodeIndex(itemID);
      items.at(lastNodeLocation).increment();
    }
    else {
      items.at(lastNodeLocation).setNextItem(itemID,items.size());//allNodes.size() really just indicates last node location
      lastNodeLocation = items.size();
      ItemNode newNode(numItems,itemID);
      items.push_back(newNode);
   //   items.at(lastNodeLocation).prevItems = currentRule.items;
      
    }
  }
  ConditionalTree(int rNumItems, int ending_id){
    ItemNode root(rNumItems,-1);
    items.push_back(root);
    
    endingID = ending_id;
  }
  void reset(){
    lastNodeLocation = 0;
  }
};
