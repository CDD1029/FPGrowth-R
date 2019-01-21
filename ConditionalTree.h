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
  std::vector<int> leafNodes;
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
      items.at(lastNodeLocation).prevItems = currentRule.items;
      
    }
    if(itemID == endingID){
      leafNodes.push_back((lastNodeLocation));
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
  void removeBelowSupport(int minSupport, int numberOfItemsConsidering){
    // im worried a lot of the trees later down the line will eventually be overwhelmingly consumed by minsupport. like an item slightly above the threshold has no chance because of the slice and dicing
    
  }
};
