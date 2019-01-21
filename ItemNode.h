#ifndef ITEMNODE
#define ITEMNODE
#include <vector>
#include <iostream>

class ItemNode {
private:
  std::vector<bool> boolNextItem;
  std::vector<long> nodeLocations;
  void setToTrue(int itemID) {
    boolNextItem.at(itemID) = true;
  }
public:
  std::vector<bool> prevItems;
  int nodeCount;
  int nodeValue;
  ItemNode(int size, int val){
    boolNextItem.resize(size);
    nodeLocations.resize(size);
    nodeCount = 1;
    nodeValue = val;
  }
  bool itemAlreadyInModel(int index){
    return boolNextItem.at(index);
  }
  void increment(){
    nodeCount++;
  }
  void setNextItem(int itemID, int location){
    setToTrue(itemID);
    nodeLocations.at(itemID) = location;
  }
  int findNextNodeIndex(int itemID){
    return nodeLocations.at(itemID);
    
  }
};
#endif
