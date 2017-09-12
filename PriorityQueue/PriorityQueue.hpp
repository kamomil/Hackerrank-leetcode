#include <functional>
#include <vector>

template <class T,class Compare = std::less<T>>
class PriorityQueue{

private:
  int heap_sz;
  std::vector<T>* queue;
  const Compare& compare;
  int parent(int i){return (i-1)/2;};
  
public:
  PriorityQueue(int sz,const Compare& compare = Compare());
  ~PriorityQueue();

  T top();
  bool empty();
  
  void push(T t);
  void pop();
};

#include "PriorityQueue.cpp"
