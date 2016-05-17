#include "smt.h"

bool Smt::valid(vector<bool> result){
  return true;
}

bool RSmt::valid(vector<bool> result){
  //
  return true;
}

void RSmt::merge(int a, int b){
  if(a==b)
    return;
  
  smt_union(a,b);
  
  int ra = find(a);
  for(int i = 0; i<(int) representant.size(); i++){
    if(find(i) == ra){
      
      for(int y = 0; y<(int) representant.size(); y++){
        if(find(y) != ra){
          merge(find(i), find(y));
        }
      }
    }
  }
  
}

int RSmt::find(int a){
  return representant[a];
}

void RSmt::smt_union(int a, int b){
  int ra = find(a);
  int rb = find(b);
  
  for(int i = 0; i<(int) representant.size(); i++){
    if(find(i) == rb){
      representant[i] = ra;
    }
  }
}