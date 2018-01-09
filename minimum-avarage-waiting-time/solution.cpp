#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

//https://www.hackerrank.com/challenges/minimum-average-waiting-time/problem

class Customer{
public:
    int T;
    int L;
};

struct customer_cmp_t{

  inline bool operator() (const Customer& e1, const Customer& e2){
      return e1.T < e2.T;
  }
};

struct customer_cmp_l{

  inline bool operator() (const Customer& e1, const Customer& e2){
      return e1.L < e2.L;
  }
};

int main() {
    int N;
    cin >> N;
    cout << N;


    long sum = 0;
    std::vector<Customer> customer = std::vector<Customer>(N);

    for(int i = 0;i<N;i++){
        Customer c;
        cin >> c.T;
        cin >> c.L;
        customer[i] = c;
    }

    std::priority_queue<Customer,vector<Customer>,customer_cmp_l> queue;

    std::sort(customer.begin(),customer.end(),customer_cmp_t());

    auto cp = customer.begin();//cp points to the first customer who is not yet in the pizzeria
    int time = 0;
    while(true){
      Customer dummy = {time,0};
      auto next = std::lower_bound(customer.begin(),customer.end(),dummy,customer_cmp_t());
      if(next != customer.end()){
        queue.push(*next);
        while(!queue.empty()){
          Customer c = queue.top();
          queue.pop();
          time += c.L;
          sum += (time - c.T);
          for(;cp != customer.end() && (*cp).T<=time;cp++){
            queue.push(*cp);
          }
        }
      }
      else
        break;
    }

    printf("avarage is %ld\n",sum/N);
    return 0;
}
