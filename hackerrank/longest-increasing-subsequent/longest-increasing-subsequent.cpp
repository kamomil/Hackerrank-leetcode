#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
Solution to https://www.hackerrank.com/challenges/longest-increasing-subsequent/problem

based on: https://stackoverflow.com/questions/2631726/how-to-determine-the-longest-increasing-subsequence-using-dynamic-programming

 */



int main() {
    int n;
    cin >> n;
    
    //smallest[k] - the smallest in that ends a sequence of length k+1 from what was scanned so far
    vector<int> smallest = vector<int>(n);
    
    cin >> smallest[0];
    auto true_end = smallest.begin();
    true_end++;//point to the true end of the vector
    for(int i=1;i<n;i++){
        int num;
        cin >> num;
        if( *prev(true_end, 1) < num){
            *true_end = num;
            true_end++;
        }
        else{
            auto lower = lower_bound(smallest.begin(),true_end, num);
            *lower = num;
        }
    }
    cout << true_end-smallest.begin();
    
}
