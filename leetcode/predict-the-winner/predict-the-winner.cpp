/*
Solution to https://leetcode.com/problems/predict-the-winner/description/
*/
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define P1 0
#define P2 1


class Solution {
  
public:


  int max(int a, int b){
    if(a>b)
      return a;
    return b;
  }
  bool PredictTheWinner(vector<int>& nums) {
    
    int sz = nums.size();
    
    //the sum of p1 for the arry nums[i..j] according to turn (last idx in M)
    int M[20][20][2];
    int S[20][20];
    
    
    memset(M,0,sizeof(M));
    
    for(int i = 0;i<sz;i++){
      for(int j = i;j>-1;j--){
	if(j == i){
	  if(sz%2 == 1){
	    M[i][j][P1] = nums[i];
	    M[i][j][P2] = 0;
	  }
	  else{
	    M[i][j][P1] = 0;
	    M[i][j][P2] = nums[i];
	  }
	  S[i][j] = nums[i];
	  cout << "P1 : M"<<i<<","<<j<<" = "<<M[i][j][P1]<<"\n";
	  cout << "P2 : M"<<i<<","<<j<<" = "<<M[i][j][P2]<<"\n";
	}
	else{
	  S[i][j] = S[i][j+1]+nums[j];

	  if( (sz%2)  == ((i-j+1)%2) ){
	    M[i][j][P1] = max(nums[j]+M[i][j+1][P1],nums[i]+M[i-1][j][P1]);
	    M[i][j][P2] = S[i][j] - M[i][j][P1];
	  }
	  else{
	    M[i][j][P2] = max(nums[j]+M[i][j+1][P2],nums[i]+M[i-1][j][P2]);
	    M[i][j][P1] = S[i][j] - M[i][j][P2];   
	  }
	  cout << "P1 : M"<<i<<","<<j<<" = "<<M[i][j][P1]<<"\n";
	}
      }
    }
    
    if(M[sz-1][0][P1] > M[sz-1][0][P2])
      return true;
    return false;       
  }
};


int main(){

  Solution S;
  vector<int> v= {1,5,233,7};
  cout <<S.PredictTheWinner(v)<<"\n";
}
