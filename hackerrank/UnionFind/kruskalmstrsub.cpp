#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


#include <list>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>


/*
Solution to https://www.hackerrank.com/challenges/kruskalmstrsub/problem
base on union-find
 */
class DisJointSets{

private:
  class setNode{
    
  public:
    int parent;
    int rank;
    
  };
  
  setNode* sets;
  
public:
  DisJointSets(int sz);
  ~DisJointSets();
  int find(int a);
  void union_sets(int a,int b);
};


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
      //std::cout <<"pushing "<<i<<"\n";
    l.push_back(i);
    i = sets[i].parent; 
  }

  int root = i;
  
    if(!l.empty()){
        for(auto it = l.begin();it != l.end();it++)
            //std::cout << *it<<" ";// a = 1;
            sets[*it].parent = root;
    }
    //std::cout <<"\n";

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
 

class Edge{

public:
  int v1,v2;
  int w;
  Edge(int v1,int v2,int w) : v1(v1),v2(v2),w(w){}
  Edge() : v1(-1),v2(-1),w(-1){}
};

struct edge_cmp{
  
  inline bool operator() (const Edge& e1, const Edge& e2){
    if(e1.w != e2.w)
      return e1.w < e2.w;
    return e1.v1+e1.v2+e1.w <= e2.v1+e2.v2+e2.w;
  }
};

int kruskal(std::vector<Edge>& edges,int n){

  int sum = 0;
  int nedges = 0;

  DisJointSets sets = DisJointSets(n);
   
  
  for(auto it = edges.begin();it != edges.end() && nedges < n-1; it++){
    Edge e = *it;
    if(sets.find(e.v1) != sets.find(e.v2) ){
      sets.union_sets(e.v1,e.v2);
      nedges++;
      sum +=e.w;
    }
  }
  return sum;
}
int main(){
  
  int n,m;
  std::cin >> n >> m;
  
  std::vector<Edge> edges = std::vector<Edge>(m);
  for(int i = 0;i<m;i++){
    int v1,v2,w;
    std::cin >> v1 >> v2 >> w;
    //std::cout << i<<" "<<n<< " "<<m<<"\n";
    edges[i] = Edge(v1-1,v2-1,w);
  }
  std::sort(edges.begin(),edges.end(),edge_cmp());

  std::cout << kruskal(edges,n) << "\n";
  
  return 0;
}
