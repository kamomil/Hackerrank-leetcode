#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

/*
  Solution to https://www.hackerrank.com/challenges/yet-another-minimax-problem/problem
*/

// we get to arrays as input: (begin1,end1) , (begin2,end2) and a mask that has 0's in the beginnig and then 1's
// the values of the bits left to the mask don't interest us.
// let I be the index of the left most bit that interest us.
// then the arrays is sorted such that all the numbers with 0 in the Ith bit are before all numbers with 1 int the Ith bit
// the function returns that smallest xor of a masked number from the first array with a masked number from the second array
unsigned int recursive_min_xor(unsigned int* begin1, unsigned int* end1 ,unsigned int* begin2, unsigned int* end2,unsigned int mask){

  //if one of the arrays is empty return hieghst uint
  if(begin1 == end1 || begin2 == end2)
    return 0xffffffff;
  
  unsigned int bit = mask - (mask >> 1);

  //if one array has only one number, just iterate the other array to find the smallest xor
  if(end1-begin1 == 1){
    unsigned int minxor = 0xffffffff;
    for(unsigned int* it=begin2;it<end2;it++){
      if(minxor > (((*it) & mask) ^ ((*begin1) & mask))){	
	minxor = ((*it) & mask) ^ ((*begin1) & mask);
      }
    }
    return minxor;
  }

  if(end2-begin2 == 1){
    unsigned int minxor = 0xffffffff;
    for(unsigned int* it=begin1;it<end1;it++)
      if(minxor> (((*it) & mask) ^ ((*begin2) & mask)))
	minxor = ((*it) & mask) ^ ((*begin2) & mask);
    return minxor;
    
  }
  //mask == 1 means we are interested only in the last bit
  if(mask == 1){
    //first array has both 1s and 0s - one of them will return 0 when xored with bit from the second array
      if(*begin1 == 0 && *(end1-1) == 1)
              return 0;
      //first array has only 0s - return 0 only if the second array has at list one 0
      if(*begin1 == 0 && *begin2 == 0)
              return 0;
      //first array has only 1s - return 0 only if the second array has at list one 1
      if(*begin1 == 1 && *(end2-1) == 1)
              return 0;
      return 1;
      
  }
  unsigned int* it1 = begin1;
  unsigned int v1 = *begin1 & bit;

  //loop until it1 point to the first number whos "bit" is different or end1 if there is no such
  while( (it1 != end1) && (v1 == (*it1 & bit)))
    it1++;


  unsigned int* it2 = begin2;
  unsigned int v2 = *begin2 & bit;

  //loop until it2 point to the first number whos "bit" is different or end2 if there is no such
  while( (it2 != end2) && (v2 == (*it2 & bit)))
    it2++;

  unsigned int m = 0xffffffff;


  
  if(v1 == v2){
    
    unsigned int m1 = recursive_min_xor(begin1,it1,begin2,it2,mask>>1);
    unsigned int m2 = recursive_min_xor(it1,end1,it2,end2,mask>>1);
    m = m1 < m2 ? m1 : m2;
    return m;
  }
  
  else if( (it2 != end2) && (v1 == (*it2 & bit))   ){
  
    return recursive_min_xor(begin1,end1,it2,end2,mask>>1);
  }
  else if( (it1 != end1) && (v2 == (*it1 & bit))   ){
    
    return recursive_min_xor(it1,end1,begin2,end2,mask>>1);
  }
  
  //bit is different
  return bit + recursive_min_xor(begin1,end1,begin2,end2,mask>>1); 
}



unsigned int minxor(unsigned int* start,unsigned int* end){

  for(unsigned int bit = 0x80000000;bit>0;bit =bit>>1){
    //cout <<"bit is "<<bit<<"\n";
    for(unsigned int* it = start;it<end-1;it++){
      if( (*it & bit) != (*(it+1) & bit) ){
	
	return bit+recursive_min_xor(start,it+1,it+1,end,bit-1);
      }

    }	
  }
  return 0;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    unsigned int n;
    cin >> n;
    unsigned int* A = (unsigned int*) malloc(sizeof(unsigned int)*n);
    vector<unsigned int>* vec = new vector<unsigned int>(n,0);
    for(unsigned int i = 0;i<n;i++)
      cin >> (*vec)[i];

    sort(vec->begin(),vec->end());

    unsigned int k  =0;
    for(auto i = vec->begin(); i != vec->end();i++)
      A[k++] = *i;

   
    //cout << "\n";
    cout << minxor(A,A+n);
    
    return 0;
}
