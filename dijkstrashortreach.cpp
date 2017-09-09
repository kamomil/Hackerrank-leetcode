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

typedef pair<struct vertex*,int> neighbour;//a neightbour vertex and an int - the weight of the edge connecting it

typedef struct vertex{
    
    struct vertex* parent;
    int dist;
    list<neighbour> nei;
    vertex() : dist(-1), parent(NULL),nei() {}
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
        u->parent = v;
        return true;
    }
    return false;
    //cout << "u = "<< u << " u->dist = "<<u->dist<<" after"<<endl;
}
void print_dists(vector<vertex*> graph, int s){
    for(int i=0;i<graph.size();i++){
        if(i == s-1)
            continue;
        if(!graph[i])
            cout<<-1<<" ";
        else
            cout<<graph[i]->dist<<" ";
    }
    cout<<endl;
}
bool stam_comp(const int& e1, const int& e2) {
    return e1<e2;
}
auto cmp = [](vertex*& e1, vertex*& e2) {
    //cout <<"cmp "<<e1<<" "<<e2<<endl;
    //cout <<"cmp "<<e1->dist<<" "<<e2->dist<<endl;
    if(!e2)
        return false;
    if(e2->dist == -1)
        return false;
    if(!e1 || e1->dist == -1)
        return true;
    return e1->dist > e2->dist; 
};

void dijkstra(vector<vertex*> graph,int s){
    
    if(!graph[s-1])
        return;
    graph[s-1]->dist = 0;
    //cout <<"start = "<<graph[s-1]<<endl;
    //cout <<"start = "<<graph[s-1]->dist<<endl;
   // std::Compare cmp = dist_comp;
    
    priority_queue<vertex*,vector<vertex*>,decltype(cmp)> vqueue(cmp,graph);
    //priority_queue<int,vector<int>,decltype(stam_comp)> vqueue(*stam_comp,v);
    //priority_queue<int,vector<int>,decltype(stam_comp)> vqueue(*stam_comp,v);
    while(!vqueue.empty()){
        vertex* v = vqueue.top();
        
        //if(v == graph[s-1])
        //    cout<<"starting"<<endl;
       // if(v)
       //     cout << "v = "<< v << " v->dist = "<<v->dist<<endl; 
       // else
       //     cout <<"null"<<endl;
        
       
        //cout<<"after pop"<<endl;
        if(!v){
            cout<<"cont"<<endl;
            continue;//if the samllest is null then all the rest must also be null, so we can break
        }
        for(auto it = v->nei.begin();it != v->nei.end();it++){
            //if(v == graph[30]||it->first == graph[30]){
                //cout<< v<<" "<<it->first<<" "<<endl;
                //cout<< v->dist<<" "<<it->first->dist<<" "<<it->second<<endl;
            //}
            if(relex(v,it->first,it->second))
                vqueue.push(it->first);
        }
         vqueue.pop();
    }
}

int main(){
    int t;
    cin >> t;
    
    for(int a0 = 0; a0 < t; a0++){
        int n;
        int m;
        cin >> n >> m;
        vector<vertex*>graph(n,NULL);//array of nodes
        for(int a1 = 0; a1 < m; a1++){
            int x;
            int y;
            int r;
            cin >> x >> y >> r;
            vertex* vx = graph[x-1] ? graph[x-1] : new vertex;
            vertex* vy = graph[y-1] ? graph[y-1] : new vertex;
            
            vx->nei.push_front({vy,r});
            vy->nei.push_front({vx,r});
            //if(x-1 == 30)
            //cout<<"x = "<<x-1<<" vx = "<<vx<<endl;
            //if(y-1 == 30)
            //cout<<"y = "<<y-1<<" vy = "<<vy<<endl;
            
            if(!graph[x-1]){
                graph[x-1] = vx;
            }
            if(!graph[y-1]){
                graph[y-1] = vy;
            }
        }
        int s;
       
        cin >> s;
        
        dijkstra(graph,s);
        print_dists(graph,s);
        //todo - kill graph
    }
    return 0;
}
