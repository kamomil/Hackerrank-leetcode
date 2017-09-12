#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

#define MOD 1000000007

enum Color{
  RED = 0,
  BLUE = 1,
};

/* Solution to https://www.hackerrank.com/challenges/kingdom-division/problem */

//this is the dynamic programing part -
//we save in this arrays values that we calculate so to not calculate same thing more then once
long* ndiff_parent = NULL;//the number of ways to color the tree with root i such that i-node has different color than it's parent
long* nsame_parent = NULL;//the number of ways to color the tree with root i such that i-node has the same  color as it's parent



bool leaf(int node,const vector<int>* const graph[] ){
  //we trat the tree as rooted in node 0, so node 0 isnot a leaf even if it has only one neighbour
  if(node == 0)
    return false;
  return graph[node]->size() == 1;
}

//print for debug
void print(vector<int>* g[],int n){
  
  for(int k = 0;k < n; k++){
    vector<int>* v = g[k];
    //cout << k <<" "<<v <<"\n";
    for(int i =0;i< v->size();i++){
      cout << (*v)[i]+1 <<" ";
    }
    cout << "\n";
  }
}


//return the number of colors to color the tree rooted with the given root
//color - the color of the root
// parent - the label of the parent of the root in the upper tree
// pcolor - the color of the parent
//graph - the neighbourhood - the i'th place is the vector of the neighbours of node i
long num_colors(int root,Color color,int parent,Color pcolor,const vector<int>* const graph[]){
  

  const vector<int>* nei = graph[root];
  int nnei = nei->size();
  if(leaf(root,graph)){
    if(color == pcolor)
      return 1;//if the leaf is the same color as the parent there is one way to color
    else
      return 0;//if the leaf is different color than the parent there is no way to color
  }

  //if current root has the same color as the parent then the kids can hace both colors
  if(color == pcolor){

    if(nsame_parent[root] != -1)
      return nsame_parent[root];
    long s =1;
    for(int j=0;j<nnei;j++){
      if((*nei)[j] == parent)
	continue;
      long r = num_colors((*nei)[j],RED,root,color,graph)%MOD;
      long b = num_colors((*nei)[j],BLUE,root,color,graph)%MOD;
      s = (s * ((r+b)%MOD))%MOD;
    }
    nsame_parent[root] = s;
    
    return s;
  }
  else{
    //if the root has different color than the parent - then it must choose at list one kid to have the same color as he
    if(ndiff_parent[root] != -1)
      return ndiff_parent[root];
    
    long t  = 0;

    //forced_idx is the index of the kid to force it to have the same color as root.
    // in order not to count combinations  more than once we must also force all kid indices before forced_idx to have opposite color of the root
    // this way the forced_idx kid is the first kid with same color as the root and so each combination is unique
    for(int forced_idx = 0;forced_idx<nnei;forced_idx++){
      if((*nei)[forced_idx] == parent)
	continue;
      long s_force_one_nei =1;  
      for(int i =0;i<nnei;i++){
	if((*nei)[i] == parent)
	  continue;
	if(i<forced_idx)
	  s_force_one_nei = (s_force_one_nei * (num_colors((*nei)[i],pcolor,root,(Color)(1-(int)pcolor),graph)%MOD))%MOD;
	else if(i == forced_idx)
	  s_force_one_nei = (s_force_one_nei * (num_colors((*nei)[i],(Color)(1-(int)pcolor),root,(Color)(1-(int)pcolor),graph)%MOD))%MOD;
	else{
	  long r = num_colors((*nei)[i],RED,root,(Color)(1-(int)pcolor),graph)%MOD;
	  long b = num_colors((*nei)[i],BLUE,root,(Color)(1-(int)pcolor),graph)%MOD;
	  s_force_one_nei = (s_force_one_nei * ((r+b)%MOD))%MOD;
	}
      }
      t = (t + s_force_one_nei)%MOD;
      
    }
    ndiff_parent[root] = t;
    return t;
  }
}
  

int main() {
    
    int n;
    cin >>n;
    vector<int>* graph[n];
    for(int i=0;i<n;i++){
        graph[i] = new vector<int>();
        //cout <<i<<": "<<graph[i]<<"\n";
    }

    //this is the dynamic programing part -
    //we save in this arrays values that we calculate so to not calculate same thing more then once

    ndiff_parent = new long[n];//the number of ways to color the tree with root i such that i-node has different color than it's parent
    nsame_parent = new long[n];//the number of ways to color the tree with root i such that i-node has the same  color as it's parent

    
    memset(ndiff_parent,-1,n*sizeof(long));
    memset(nsame_parent,-1,n*sizeof(long));

        
    for(int i=0;i<n-1;i++){
        int a,b;
        cin >> a >> b;
     
        graph[a-1]->push_back(b-1);
        graph[b-1]->push_back(a-1);
        
        
    }
    
    cout << (2*num_colors(0,RED,-1,BLUE,graph))%MOD;
      
    return 0;
}
