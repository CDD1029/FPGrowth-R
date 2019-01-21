#include <Rcpp.h>
#include <iostream>
#include <vector>
#include "ItemNode.h"
#include "RuleNode.h"
#include "ConditionalTree.h"
using namespace Rcpp;

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

// [[Rcpp::export]]

double uhh(NumericVector rFreq,int rNumItems, int rNumTrans, LogicalVector rTransData,CharacterVector rItems, int minSupport) {
  int freq[2][rNumItems];
  int placeHolder = 0;
  std::vector<int> frequentItemIDs; // head = most freq, end is least freq
  for(int col1 = 0; col1 < 2; col1++){
    
    for(int col2 = 0; col2 < rNumItems; col2++){
      freq[col1][col2] = rFreq[placeHolder++];
      Rcout << freq[col1][col2] << " ";
    }
    Rcout << "" << std::endl;
  }
  //The code before does the same as the following, but this is faster, i suppose. 
  bool itemIsAboveMinSupport[rNumItems]; // other ideas could be to have a cutoff, but this is safer as it does not assume the frequency is ordered. 
  //another assumption is that each item is unique
  int lastItemIsAboveMinSupport = -1;
  int totalItemsAboveMinSupport = 0;
  for(int i = 0; i < rNumItems; i++){
    freq[0][i] = rFreq[i];
    freq[1][i] = rFreq[i+rNumItems];
    itemIsAboveMinSupport[i] = rFreq[i] > minSupport;
    //can add a simple if next item is > prev, its not ordered here
    if (rFreq[i] > minSupport) {
      lastItemIsAboveMinSupport = i;
      totalItemsAboveMinSupport++;
      
      frequentItemIDs.push_back(rFreq[i+rNumItems]);
      
      //this might be redundant, if ordered these values should be equal
    }
    else{
    }
  }
  for(int i = totalItemsAboveMinSupport-1; i >= 0; i--){
    Rcout << freq[1][i] << std::endl;
  }
  bool transData[rNumTrans][rNumItems]; // transid | itemNumber // idea: make it 2 vectors and consolidate finding correct index. 
  placeHolder = 0;
  for(int col1 = 0; col1 < rNumTrans; col1++){
    for(int col2 = 0; col2 < rNumItems; col2++){
      transData[col1][col2] = rTransData[placeHolder++];
    }
    /*
    if(col1 < 10){
      if(transData[col1][18]){
        Rcout << "heyyo" << std::endl;
      }
      Rcout << transData[col1][18] << std::endl;
    }*/
  }

  std::vector<ItemNode> allNodes;
  std::vector<ConditionalTree> trees;
  for(int i = totalItemsAboveMinSupport-1; i >= 0; i--){
    ConditionalTree emptyTreeWithItemItIsSupposedToEndIn(rNumItems,frequentItemIDs.at(i));
    trees.push_back(emptyTreeWithItemItIsSupposedToEndIn);
  }

  for(int transID = 0; transID < rNumTrans; transID++){
    // put this in a function 
    int correctTreeIndex = -1;
    for(int i = totalItemsAboveMinSupport-1; i >= 0; i--){
      if(transData[transID][freq[1][i]]){
        correctTreeIndex = i;
        break;
      }
    }
    if(correctTreeIndex == -1){
      break;
    }
    //end would be function
    RuleNode currentRule(totalItemsAboveMinSupport);
    
    trees.at(correctTreeIndex).reset();
    for(int itemIterator = 0; itemIterator < rNumItems; itemIterator++){
      int itemID = freq[1][itemIterator];
      
      if(transData[transID][itemID]) {
       trees.at(correctTreeIndex).add(itemID,rNumItems,currentRule);
        currentRule.add(itemIterator);
        /*
        if(allNodes.at(lastNodeLocation).itemAlreadyInModel(itemID)) {
          lastNodeLocation = allNodes.at(lastNodeLocation).findNextNodeIndex(itemID);
          allNodes.at(lastNodeLocation).increment();
        }
        else {
          allNodes.at(lastNodeLocation).setNextItem(itemID,allNodes.size());//allNodes.size() really just indicates last node location
          lastNodeLocation = allNodes.size();
          ItemNode newNode(rNumItems,itemID);
          allNodes.push_back(newNode);
          allNodes.at(lastNodeLocation).prevItems = currentRule.items;
          
        }*/
      // not sure if needed  currentRule.add(itemID); // put before the .itemalreadyinmodel if statement if you want to include the new rule to include the current item.
        
      }
    }
  }
  for(int i = 0; i < trees.size();i++){
    trees.at(i).removeBelowSupport(minSupport,trees.size()-i-1);//-1 because I don't need to redo math for the last item. 
  }
  int zero = 0;
  for(int nodeIterator = 0; nodeIterator < allNodes.size();nodeIterator++){
    if(allNodes.at(nodeIterator).prevItems.size() == 0){
      zero++;
      continue;
    }
  //   Rcout << allNodes.at(nodeIterator).prevItems.at(0) << std::endl;
  }
  
 // Rcout << zero << std::endl;
  return 222.0;
}

// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
a = uhh(dataFreq(data),ncol(data),nrow(data),boolVec(data),data@itemInfo$labels,15000)
*/
