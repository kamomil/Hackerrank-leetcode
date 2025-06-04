#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long max(int i,int j,long long* A){
    long long m = A[i];
    for(int k=i;k<=j;k++){
        if(m < A[k] )
            m = A[k];
    }
    return m;
}
bool ab_nl_c(long long a,long long b, long long c){
    long long k = c/a;
    if (k>=b)
        return true;
    return false;

}
#define MAX(a,b) (a < b ? b : a)
int get_array_pairs(int n,long long* A){
    long long* M0;
    long long* M1;
    long long* Mcurr;
    long long* Mlast;

    int count = 0;
    M0 = new long long[n];
    M1 = new long long[n];
    if (!M1 || !M0)
        return 0;

    Mcurr = M0;
    Mlast = M1;
    for(int r=0;r<n;r++){
        long long last = Mcurr[0];
            long long last_k = last/A[r];
        for(int c=0;c<r;c++){

            if(r ==c+1){
                Mcurr[c] = MAX(A[r],A[c]);
                if(A[r] == 1 || A[c] == 1)
                    count++;
            }
            else{
                Mcurr[c] = MAX(Mlast[c],A[r]);

                if(Mcurr[c] != last){
                    last = Mcurr[c];
                    last_k = last/A[r];
                }
                if(last_k>=A[c]){
                //if(max(c,r,A) != M[n*r+c])
                  //  cout << c << " " << r << "\n";
             //cout << M[n*r+c] << " " << A[r]*A[c] << "\n";
                    count++;
                }
            }
        }
        long long* Mtmp = Mlast;
        Mlast = Mcurr;
        Mcurr = Mtmp;
    }

    return count;
}

int main() {
    int n;
    long long* A;
    cin >> n;
    A = new long long[n];
    for(int i=0;i<n;i++)
        cin >> A[i];
    cout << get_array_pairs(n,A);
    return 0;
}
