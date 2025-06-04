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
    long T;
    long L;
};

struct customer_cmp_t{

  inline bool operator() (const Customer& e1, const Customer& e2){
      return e1.T < e2.T;
  }
};

struct customer_cmp_l{

  inline bool operator() (const Customer& e1, const Customer& e2){
      return e1.L > e2.L;
  }
};

int main() {
    long N;
    cin >> N;
    //;cout << N;


    long sum = 0;
    std::vector<Customer> customer = std::vector<Customer>(N);

    for(long i = 0;i<N;i++){
        Customer c;
        cin >> c.T;
        cin >> c.L;
        customer[i] = c;
    }

    std::priority_queue<Customer,vector<Customer>,customer_cmp_l> queue;

    std::sort(customer.begin(),customer.end(),customer_cmp_t());

    auto cp = customer.begin();//cp points to the first customer who is not yet in the pizzeria
    long time = 0;
    while(true){
      Customer dummy = {time,0};
      auto next = std::lower_bound(customer.begin(),customer.end(),dummy,customer_cmp_t());
      if(next != customer.end()){
        time=next->T;
        queue.push(*next);
        cp = next;
        //cout << cp->T <<"\n";
        cp++;
        //cout << cp->T <<"\n";
        while(!queue.empty()){
          Customer c = queue.top();
          queue.pop();
          time += c.L;
          //cout << "L is " << c.L << " T is "<<c.T <<" time "<<time <<"\n";
          sum += (time - c.T);
          for(;cp != customer.end() && (*cp).T<=time;cp++){
            queue.push(*cp);
          }
        }
      }
      else
        break;
    }

    //printf("avarage is %ld\n",sum/N);
    printf("%ld\n",sum/N);
    return 0;
}
