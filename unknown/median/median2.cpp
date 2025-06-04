
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

/*
This implementation is easyer to maintain but does not passes the tests due to timeout
The idea is that we have two multimaps, one of all the values larger then the median and one of all the values smaller the the median.
To get the median we either take the begin() from the bigger map or take the avarage of the begins if maps sizes are equal.
We must maintain the property that the absolute difference in size between the maps must alsways be 0 or 1.
So after key addition or removal we call "adjust" function that moves one key from map to map if needed
*/

int get_median(std::multimap<int,int,std::less<int>>& largers, std::multimap<int,int,std::greater<int>>& smallers,double* mod);

void print_median(std::multimap<int,int,std::less<int>>& largers, std::multimap<int,int,std::greater<int>>& smallers){
    
    
    if(largers.empty() && smallers.empty()){
        cout << "Wrong!"<<endl;
        return;
    }
    double extra = 0.0;
   
    int median = get_median(largers,smallers,&extra);
    if(extra == 0.0)
        cout << median << endl;
    
    else if(median == 0){
        if(extra>0)
            cout << "0.5" << endl;
        else
            cout << "-0.5" << endl;
    }
    else{
        cout << median <<".5" << endl;
    }
}



void adjust(std::multimap<int,int,std::less<int>>& largers, std::multimap<int,int,std::greater<int>>& smallers){
    int ls = (int)largers.size();
    int ss = (int)smallers.size();
    
    if(ls-ss>1 || ls-ss<-1){
        if(ls>ss){
            int key = largers.begin()->first;
            largers.erase(largers.begin());
            smallers.emplace(std::make_pair(key,key));
        }
        else{
            int key = smallers.begin()->first;
            smallers.erase(smallers.begin());
            largers.emplace(std::make_pair(key,key));
        }
    }
}

int get_median(std::multimap<int,int,std::less<int>>& largers, std::multimap<int,int,std::greater<int>>& smallers,double* mod){
    *mod = 0.0;
    
    if(largers.size() > smallers.size())
        return largers.begin()->first;
    if(largers.size() < smallers.size())
        return smallers.begin()->first;
    
    long  m = (long)smallers.begin()->first;
    long  M = (long)largers.begin()->first;
    if( (m+M)%2 != 0){
        if(m+M > 0)
            *mod = 0.5;
        if(m+M < 0)
            *mod = -0.5;   
    }
    return ((int)((m+M)/2));
    
}

bool is_smaller(int val,int median,double extra){
    if(extra == 0.0)
        return val<median;
    else
        return ((double) val) < (((double) median)+extra);
}
bool is_larger(int val,int median,double extra){
    if(extra == 0.0)
        return val>median;
    return ((double) val) > (((double) median)+extra);
}

template <class cmp> int remove_key(int key,std::multimap<int,int,cmp>& m){
    auto it = m.begin();
    for(;it != m.end();it++){
        if(it->first == key)
            break;
    }
    if(it == m.end())
        return -1;
    m.erase(it);
    return 0;
}

template <class cmp> void add_key(int key,std::multimap<int,int,cmp>& m){
    m.emplace(std::make_pair(key,key));
}




int remove(std::multimap<int,int,std::less<int>>& largers, std::multimap<int,int,std::greater<int>>& smallers,int val){
    if(largers.size() == 0 && smallers.size() == 0){
        return -1;
    }
    double mod = false;
    int median = get_median(largers,smallers,&mod);
    int res = 0;
    if(is_smaller(val,median,mod)){
        res = remove_key(val,smallers);
    }
    else if(is_larger(val,median,mod)){
        res = remove_key(val,largers);
    }
    else{
        if(largers.size()>smallers.size())
            res = remove_key(val,largers);
        else
            res = remove_key(val,smallers);
    }
    adjust(largers,smallers); 
     return res;
}

int add(std::multimap<int,int,std::less<int>>& largers, std::multimap<int,int,std::greater<int>>& smallers,int val){
    
    if(largers.size() == 0 && smallers.size() == 0){
        add_key(val,smallers);
        return 0;
    }
    double mod = 0.0;
    int median = get_median(largers,smallers,&mod);
    //cout << "add: median:"<< median<<" extra: "<<mod<<endl;
    if(is_smaller(val,median,mod)){
        add_key(val,smallers);
    }
    else if(is_larger(val,median,mod)){
        //cout<<"add: add to larger"<<endl;
        add_key(val,largers);
    }
    else{
        if(largers.size()>smallers.size())
            add_key(val,smallers);
        else
            add_key(val,largers);
    }
    adjust(largers,smallers); 
    return 0;
}
void median(vector<char>& op,vector<int>& val) {
    
    std::multimap<int,int,std::less<int>> largers;
    std::multimap<int,int,std::greater<int>> smallers;
    
    int i =0;
    
    do{
        int res = 0;
        if(op[i] == 'a'){
           res = add(largers,smallers,val[i]);
        }
        else{
            
            res = remove(largers,smallers,val[i]);
        }
        if(res == 0)
            print_median(largers,smallers);
        else
            cout << "Wrong!"<<endl;
        
        //cout <<"l:"<<largers.size() << " s:"<<smallers.size()<<endl;
        i++;
        
    }while(i<op.size());
    //cout << "return!";
}

int main(void){

//Helpers for input and output

   int N;
   cin >> N;
   
   vector<char> s;
    vector<int> X;
   char temp;
    int tempint;
   for(int i = 0; i < N; i++){
      cin >> temp >> tempint;
        s.push_back(temp);
        X.push_back(tempint);
   }
   
   median(s,X);
   return 0;
}
