#include <stdio.h>
#include <vector>

//https://leetcode.com/problems/container-with-most-water/description/

int min(int a,int b){
  if(a<b)
    return a;
  return b;
}

int min_idx(int a,int b,int i,int j){
  if(a<b)
    return i;
  return j;
}

int step_from_min(int a,int b){
  if(a<b)
    return 1;
  return -1;
}

int max(int a,int b){
  if(a>b)
    return a;
  return b;
}





class Solution {
public:
int maxInRange(std::vector<int>& height,int i,int j) {
  int m = min(height[i],height[j]);
  int m_idx = min_idx(height[i],height[j],i,j);
  int M_idx = i+j-m_idx;
  int step = step_from_min(height[i],height[j]);
  int current_max = m*(j-i);
  if(i == j)
    return 0;
  if(j == i+1)
    return min(height[i],height[j]);

    int idx = m_idx;
    while(idx != M_idx && height[idx]<=m)
      idx +=step;

    if(idx == M_idx)
      return current_max;
    printf("i = %d, j = %d, idx = %d\n",i,j,idx);
    return max(current_max, maxInRange(height,idx<M_idx ? idx : M_idx , idx > M_idx ? idx : M_idx));
  }

int maxArea(std::vector<int>& height) {
    return maxInRange(height,0,height.size()-1);
  }
};

int main(){
  std::vector<int> height = {1,6,2,8,0,3,5,2,2};
  Solution s;

  printf("max container has %d\n",s.maxArea(height));

}
