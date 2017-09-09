#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* 
Solution to https://www.hackerrank.com/challenges/equal/problem 
Compiled as c++14
Was able to solve it only after the hints I get from people in the discussion:


I think we don't need to use dynamic programming here. First of all, if you give chocolate bars to all but chosen one, it is equivalent to take away the chocolate bar(s) from each chosen one until every one is equal. So the challenge becomes decrease from each individual 1, 2 or 5 until all are equal. Second to calculate the ops we need to use to decrease an integer n until it reaches 0 (call it the function f) is equivalent to convert 1, 5 (no need to use dynamic programming here). Finally, to solve this challenge, we find the min (call it m) of the given list, then for i from 0 to 4, we find min of ops[i]=sum(f(c-min+i)) where c is each individual colleague and thus no need to use dynamic programming here :)
    
baseline is not necessarily 0. It is a number between the minimum in the sequence M and the max(0, (M - 4)).
*/

/*
ops[i] = the number of operations it takes to change all collouges to m-i where m is the cluoge with the minimal initial number of chocolates   
*/
std::vector<int> ops {0,0,0,0};

//assume c >= base
static int coll_to_base(int c, int base){

    int op = 0;
    if(c-base>5){
       int n = (c-base)/5;
       op +=n;
       c = c - (5*n); 
    }
    switch(c-base){
        case 0:
            return op;
        case 1:
        case 2:
        case 5:
            return op+1;
        case 4:
        case 3:
            return op+2;
    }
    return -1;
}

static int min(vector<int> v){
    int m = v[0];
    for(int i = 0;i<v.size();i++){
        if(v[i]<m){
            m = v[i];
        }
    }
    return m;
}

int min_ops(vector<int> coll){
    
    int m = min(coll);
    
    ops[0] = ops[1] = ops[2] = ops[3] = 0;
    
    for(int i=0;i<4;i++){
        //cout<<coll.size()<<"\n";
        for(int c_idx=0;c_idx<coll.size();c_idx++){
            int t = coll_to_base(coll[c_idx],m-i);
            //if(t == -1)
            //    std::cout <<i<<" "<<c_idx<<" "<<t<<"bug\n";//TODO -remove!!
            ops[i]+=t;
        }
    }
    return min(ops);
}
int main() {

    int t;
    
    cin >> t;
    //std::cout<<t<<"\n";
    for(int i = 0;i<t;i++){

        int ncoll;
        cin >> ncoll;
        vector<int> coll(ncoll);
        //std::cout<<ncoll<<" "<<i<<" "<<coll.size()<<"\n";
        
        
        for(int j = 0;j<ncoll;j++){
            int c;
            cin >> c;
            coll[j] = c;
        }       
        std::cout<<min_ops(coll)<<"\n";
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}

