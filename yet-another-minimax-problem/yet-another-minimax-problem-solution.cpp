#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int get_elem_change(int* A,int n,int bit){
    int i =0;
    int b = 1 << bit;
    while(i<n && ( A[i] & b) ) 
        i++;
    return i;
}

/*
A we are interested only of the bits 0 to bit_idx
*/
int minxor(int* A, int na, int* B, int nb, int bit_idx){

    int mask = (0xffffffff >> 32-bit_idx-1);
    int bit = 1 << bit_idx;
    
    int ai = get_elem_change(A,na,bit_idx);
    int bi = get_elem_change(B,nb,bit_idx);
    
    bool are_a_b_diff = ( (ai == 0 && bi == nb) || (ai == na && bi == 0));
    if(bit_idx == 0){
        if(are_a_b_diff)
            return 1;
        return 0;
    }
    
    if(are_a_b_diff)
        return bit | minxor(A,na,B, nb, bit_idx-1);
        
    else if(ai == 0){//A has only 0 in the bit_idx'th bit
       return minxor(A,na,B+bi,nb-bi, bit_idx-1);
    }
    else if(ai == na){//A has only 1 in the bit_idx'th bit
       return minxor(A,na,B,bi, bit_idx-1);
    }
    else if(bi == 0){//B has only 0 in the bit_idx'th bit
       return minxor(A+bi,na-bi,B,nb, bit_idx-1);
    }
    else if(bi == nb){//B has only 1 in the bit_idx'th bit
       return minxor(A,ai,B,nb, bit_idx-1);
    }
    
    int m1  = minxor(A+ai,na-ai,B+bi,nb-bi,bit_idx-1);
    int m2  = minxor(A+ai,na-ai,B+bi,nb-bi,bit_idx-1);
    return m2 < m1 ? m2 : m1;
}

int min_perm_score(int* A,int n){
    
    if(n == 0)
        return -1;
    if(n == 1)
        return A[0];
    if(n == 2)
        return A[0] ^ A[1]; 
    
    std::sort(A ,A+n,std::greater<int>());
    
    int* d = (int*) malloc(sizeof(int)*sizeof(int)*8);//int for every bit in int
    
    if(!d)
        return -1;
    
    for(int i= 0 ;i<n;i++)
        d[i] = n;
    
    
    int first_idx = 0;
    
    //fill d
    for(int i =0;i<n-1;i++){
        
        int a = A[i] ^ A[i+1];
        int j = 0;
        
        int bit = 0;
        for(bit = 1;bit<=0x80000000;){
            if(a & bit && d[j] == -1){
                d[j] = i+1;
                if(j > first_idx)
                    first_idx = j;
            }
            if(bit == 0x80000000)
                break;
            else
                bit = bit << 1;
        }
        
    }
    
    
    
    return minxor(A,d[first_idx]+1, A+d[first_idx]+1,n-d[first_idx]-1,first_idx);
    
    
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    int* A = (int*) malloc(sizeof(int)*n);
    for(int i = 0;i<n;i++)
        cin >> A[i];
    
    return 0;
}
