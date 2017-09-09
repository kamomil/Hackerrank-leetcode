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

typedef pair<struct vertex,int> neighbour;//a neightbour vertex and an int - the weight of the edge connecting it

typedef struct vertex{
    
    short label;
    int dist;
    vertex() : label(0) , dist(-1) {}
    vertex(short olabel) : label(olabel) , dist(-1) {}
    vertex(short olabel,int odist) : label(olabel) , dist(odist) {}
} vertex;
 

    
bool dist_comp(const vertex*& e1, const vertex*& e2) {
    if(!e2)
        return true;
    if(!e1)
        return false;
    if(e2->dist == -1)
        return true;
    if(e1->dist == -1)
        return false;
    return e1->dist < e2->dist; 
}




bool relex(vertex* v, vertex* u,int edge_weight){//u and v are not null
    if(v->dist == -1)
        return false;
    //cout <<"relex:"<<endl;
    //cout << "v = "<< v << " v->dist = "<<v->dist<<endl;
    //cout << "u = "<< u << " u->dist = "<<u->dist<<endl;
    //cout << "w = "<< edge_weight<<endl;
    
    if(u->dist == -1 || u->dist > v->dist + edge_weight){
        u->dist = v->dist + edge_weight;
        return true;
    }
    return false;
    //cout << "u = "<< u << " u->dist = "<<u->dist<<" after"<<endl;
}

void print_dists(vector<vertex>& graph, short s){
    for(size_t i=0;i<graph.size();i++){
        if(i == s-1)
            continue;
        cout<<graph[i].dist<<" ";
    }
    cout<<endl;
}

bool stam_comp(const int& e1, const int& e2) {
    return e1<e2;
}
auto cmp = [](vertex e1, vertex e2) {
    //cout <<"cmp "<<e1<<" "<<e2<<endl;
    //cout <<"cmp "<<e1->dist<<" "<<e2->dist<<endl;
    
    if(e2.dist == -1)
        return false;
    if(e1.dist == -1)
        return true;
    return e1.dist > e2.dist; 
};

void dijkstra(vector<vertex>& graph, vector<vector<neighbour>>& neighbours, short s){
    
    
    if(!graph[s-1].label)    
        return;
    
    graph[s-1].dist = 0;
    
    vector<bool> founds(graph.size(),false);
  
    priority_queue<vertex,vector<vertex>,decltype(cmp)> vqueue(cmp);
    
    vqueue.push(graph[s-1]);
    
    while(!vqueue.empty()){
        
        vertex v;
        do{
            v = vqueue.top();
            vqueue.pop();
        }while(!vqueue.empty() && founds[v.label-1]);
        
        //if(founds[v.label-1])
        //    return;
        founds[v.label-1] = true;
        
    
        
        size_t sz = neighbours[v.label-1].size();//vnei is a vector
        for(size_t i = 0; i<sz;i++){
            
            vertex nei = neighbours[v.label-1][i].first;
            int w = neighbours[v.label-1][i].second;
            
            
            if(!(founds[nei.label-1]) && 
               (graph[nei.label-1].dist == -1 || graph[nei.label-1].dist > v.dist+w)){
                graph[nei.label-1].dist = v.dist+w;
                vqueue.push(vertex(nei.label,v.dist+w));    
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
        vector<vertex>graph(n);
        vector<vector<neighbour>>neighbours(n);
        
        for(int a1 = 0; a1 < m; a1++){
            short x;
            short y;
            int r;
            cin >> x >> y >> r;
            vertex vx = graph[x-1].label ? graph[x-1] : vertex(x);
            vertex vy = graph[y-1].label ? graph[y-1] : vertex(y);
            
            neighbours[x-1].push_back({y,r});
            
            neighbours[y-1].push_back({x,r});
            
            if(!graph[x-1].label){
                graph[x-1] = vx;
            }
            if(!graph[y-1].label){
                graph[y-1] = vy;
            }
        }
        short s;
       
        cin >> s;
        
        dijkstra(graph,neighbours,s);
        print_dists(graph,s);
    }
    return 0;
}

