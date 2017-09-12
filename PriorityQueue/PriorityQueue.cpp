
//#include <functional>
//#include <vector>
/*
template <class T,class Compare = std::less<T>>
class PriorityQueue{

private:
  int heap_sz;
  std::vector<T>* queue;
  const Compare& compare;
public:
  PriorityQueue(int sz,const Compare& compare = Compare());
  ~PriorityQueue();

  T top();
  bool empty();
  
  void push(T t);
  void pop();
};
*/

template <class T,class Compare>
PriorityQueue<T,Compare>::PriorityQueue(int sz,const Compare& compare): compare(compare){
  queue = new std::vector<T>(sz);
  heap_sz = 0; 
}
template <class T,class Compare>
PriorityQueue<T,Compare>::~PriorityQueue(){
  if(queue)
    delete queue;
}

template <class T,class Compare>
T PriorityQueue<T,Compare>::top(){

  return (*queue)[0];
}

template <class T,class Compare>
bool PriorityQueue<T,Compare>::empty(){
  return heap_sz == 0;
}

template <class T,class Compare>
void PriorityQueue<T,Compare>::push(T t){

  (*queue)[heap_sz++] = t;
  int idx = heap_sz-1;
  while(idx > 0 && !compare((*queue)[idx],(*queue)[parent(idx)] )){

    T tmp = (*queue)[idx];
    (*queue)[idx] = (*queue)[parent(idx)];
    (*queue)[parent(idx)] = tmp;
    idx = parent(idx);
      
  }
  
}

template <class T,class Compare>
void PriorityQueue<T,Compare>::pop(){
  (*queue)[0] = (*queue)[--heap_sz];

  int i = 0;
  int n = i;
  do{
    int l = 2*i+1;
    int r = 2*i+2;
    n = i;
    if(l<heap_sz && compare((*queue)[l],(*queue)[i]))
      n = l;
    else if(r<heap_sz && compare((*queue)[r],(*queue)[i]))
      n = r;

    T tmp = (*queue)[i];
    (*queue)[i] = (*queue)[n];
    (*queue)[n] = tmp;
    
  }while(n != i);
}
