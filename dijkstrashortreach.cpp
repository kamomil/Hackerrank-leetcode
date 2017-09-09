#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
Final Solution to https://www.hackerrank.com/challenges/dijkstrashortreach/problem
Compiles with c++14
After manny attempts. thinkgs to notice:
1. The priority queue by default is a max queue so need to define cmp to the opposite.
2. The big obtacle is that in the begginig I pushed to the queue pointers to vertices that were allocated on the heap.
The problem with this is that the relex operation changes the values pointed by those pointers that are in the queue but the priority queue does not update 
when the values pointed are updated this is a bug sine the priority queue does not save the property that frot() returns the smallest value.
The solution is to use copy by value so there might be different vertices struct in the queue that represent the same vertex but it's not the same pointer so it's ok.
We push an updated vertex upon relex.

3. In Corman's book the solution starts by putting all the vertices in the queue before the itereation. This is not necessary, better push only the root.
4. When sending a vector to a function it's importent to send it using reference or pointer, otherwise the whole vector is copied with O(n)

*/

//first - the label of the neighbour
//second - the  weight of the edge connecting it
typedef pair<int,int> neighbour;

typedef struct vertex{
    
    short label;
    int dist;
    vertex() : label(0) , dist(-1) {}
    vertex(short olabel,int odist) : label(olabel) , dist(odist) {}
} vertex;
 
void print_dists(vector<int>& distances, short s){
    for(size_t i=0;i<distances.size();i++){
        if(i == s-1)
            continue;
        cout<<distances[i]<<" ";
    }
    cout<<endl;
}

auto cmp = [](vertex e1, vertex e2) {
    
    if(e2.dist == -1)
        return false;
    if(e1.dist == -1)
        return true;
    return e1.dist > e2.dist; 
};

void dijkstra(vector<int>& distances, vector<vector<neighbour>>& neighbours, short s){
    

  //s is the label of the root
    distances[s-1] = 0;
    
    vector<bool> founds(distances.size(),false);
  
    priority_queue<vertex,vector<vertex>,decltype(cmp)> vqueue(cmp);
    
    vqueue.push(vertex(s,0));
    
    while(!vqueue.empty()){
        
        vertex v;

	//whene a vertex in poped it means that it's distance it found and won't be further reduced so we assign true to its index in "founds"
	//a vertex that was found can still be in the queue from previous updates that are not relevant anymore.
	//So we pop until we get to a vertex that was not yet found
        do{
            v = vqueue.top();
            vqueue.pop();
        }while(!vqueue.empty() && founds[v.label-1]);
        
        if(founds[v.label-1])
            return;
        
        founds[v.label-1] = true;
        
    
        
        size_t sz = neighbours[v.label-1].size();//vnei is a vector
        for(size_t i = 0; i<sz;i++){
            
            int nei_label = neighbours[v.label-1][i].first;
            int w = neighbours[v.label-1][i].second;
            
            
            if(!(founds[nei_label-1]) && 
               (distances[nei_label-1] == -1 || distances[nei_label-1] > v.dist+w)){
                distances[nei_label-1] = v.dist+w;
                vqueue.push(vertex(nei_label,v.dist+w));    
            } 
        }
    }
}
 

int main(){
    int t;
    cin >> t;
    
    for(int a0 = 0; a0 < t; a0++){
        int n;
        int m;
        cin >> n >> m;
        vector<int>distances(n,-1);

        vector<vector<neighbour>>neighbours(n);
        
        for(int a1 = 0; a1 < m; a1++){
            short x;
            short y;
            int r;
            cin >> x >> y >> r;
            
            neighbours[x-1].push_back({y,r});
            neighbours[y-1].push_back({x,r});
        }
        short s;
       
        cin >> s;
        
        dijkstra(distances,neighbours,s);
        print_dists(distances,s);
    }
    return 0;
}
