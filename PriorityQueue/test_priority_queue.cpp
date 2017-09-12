#include "PriorityQueue.hpp"
#include <iostream>


int main(){

  PriorityQueue<int,std::less<int>> q(10);

  std::cout << q.empty()<<"\n";

  q.push(7);
  q.push(11);
  q.push(3);
  q.push(9);
  q.push(8);
  q.push(3);
  

  std::cout << "top is: "<<q.top()<<"\n";
  q.pop();
  std::cout << "top is: "<<q.top()<<"\n";
  q.pop();
  std::cout << "top is: "<<q.top()<<"\n";
  q.pop();
  std::cout << "top is: "<<q.top()<<"\n";
  q.pop();
  
  return 0;
}
