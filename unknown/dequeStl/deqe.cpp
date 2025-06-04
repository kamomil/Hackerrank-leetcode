
#include <iostream>
#include <deque>
using namespace std;

void printKMax(int arr[], int n, int k){
  std::deque<int> dq(k);

  for(int i = 0;i<n;i++){
    while(!dq.empty() && arr[i] >= arr[dq.back()]){
      //cout << "i = " << i << "poping " <<dq.back() << "\n";

      dq.pop_back();
    }
    dq.push_back(i);

    if(i>=k-1){
      printf("%d",arr[dq.front()]);
      if(i<n-1)
        printf(" ");
    }
    if(dq.front() == i-k+1){
      dq.pop_front();
    }
  }
  printf("\n");

}

int main(){

  int t;
  cin >> t;
  while(t>0) {
    int n,k;
    scanf("%d %d",&n,&k);
    int i;
    int arr[n];
    for(i=0;i<n;i++)
      scanf("%d",&arr[i]);
    printKMax(arr, n, k);
    t--;
  }
  return 0;
}
