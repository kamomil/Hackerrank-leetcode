#include "DisJointSets.hpp"
#include <list>
DisJointSets::DisJointSets(int sz){

  sets = new setNode[sz];
  for(int i = 0;i<sz;i++){
    sets[i].parent = i;
    sets[i].rank = 0;
  }

}
DisJointSets::~DisJointSets(){

  if(sets)
    delete [] sets; 
}
int DisJointSets::find(int a){
  
  int i = a;
  std::list<int> l;

  while(sets[i].parent != i){
    l.push_back(i);
    i = sets[i].parent; 
  }

  int root = i;
  
  for(auto it = l.begin();it != l.end();it++)
    sets[*it].parent = root;

  return root;

}

void DisJointSets::union_sets(int a,int b){

  int root_a = find(a);
  int root_b = find(b);

  if(root_a == root_b)
    return;

  if(sets[root_a].rank < sets[root_b].rank)
    sets[root_a].parent = root_b;

  else if(sets[root_a].rank > sets[root_b].rank)
    sets[root_b].parent = root_a;

  else{
    sets[root_b].parent = root_a;
    sets[root_a].rank++;
  }
}
