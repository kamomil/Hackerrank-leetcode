#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* Solution to https://www.hackerrank.com/challenges/crush/problem */
int main() {
    long int N,K,p,q,sum,i,j,max=0,x=0;

    cin>>N>>K;
    long int *a=new long int[N]();

    for(i=0;i<K;i++)
    {
        cin>>p>>q>>sum;
        a[p-1]+=sum;
        if((q)<=N) a[q]-=sum;
    }

    for(i=0;i<N;i++)
    {
       x=x+a[i];
       if(max<x) max=x;

    }

    cout<<max;
    return 0;
}
