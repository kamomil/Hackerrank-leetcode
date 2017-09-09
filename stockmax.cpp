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

unsigned long profit(unsigned long* A, int n){
    
    int i = n-1;
    unsigned long max = A[n-1];
    unsigned long p = 0;
    while(i>-1){
        while(i > -1 && A[i]>=max){
            max = A[i];
            i--;
        }
        while(i > -1 && A[i]<max){
            p += max - A[i];
            i--;
        }
    }
    return p;
    
}
int main() {
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    cin >> t;
    for(int ti=0;ti<t;ti++){
        int n;
        cin >> n;
        unsigned long*  A = new unsigned long[n];
        for(int ni=0;ni<n;ni++){
            cin >> A[ni];
            
        }
        cout << profit(A,n)<<endl;
        
    }
    
    return 0;
}
