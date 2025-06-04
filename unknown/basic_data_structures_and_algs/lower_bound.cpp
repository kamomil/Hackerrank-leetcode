#include <iostream>
#include <stdlib.h>
#include <time.h>

/*
template <class cmp> void add_key(int key,std::multimap<int,int,cmp>& m){
    m.emplace(std::make_pair(key,key));
}
*/

template <class T>  T* naive_lower_bound(T* start, T* end, T val){

  if(end <= start)
    return end;

  T* it = start;
  for(;it!=end && val > *it; it++)
    ;
  return it;
}

// for an array of length 2 with start[0] = 3 start[1] = 8, and val = 4
// we get to endless loop where m = start and start is update to itself
template <class T>  T* buggy_lower_bound(T* start, T* end, T val){


  std::cout << "starting lower baound\n";
  if(!end || !start)
    return NULL;
  
  if(end <= start)
    return end;

  if(val > *(end-1))
    return end;

  while(end > start){
    std::cout <<"end -start = "<<end-start<<"\n";
    std::cout <<" (end -start)/2 = "<< (end-start)/2<<"\n";
    
    T* m = start + ((end-start) / 2);

    if(val <= *m)
      end = m;
    
    else if(val > *m)
      start = m;
  }
  return end;

}


template <class T>  T* lower_bound(T* start, T* end, T val){


  std::cout << "starting lower baound\n";
  if(!end || !start)
    return NULL;
  
  if(end <= start)
    return end;

  //if(val > *(end-1))
  //  return end;

  while(end - start > 1){
    std::cout <<"end -start = "<<end-start<<"\n";
    std::cout <<" (end -start)/2 = "<< (end-start)/2<<"\n";
    
    T* m = start + ((end-start) / 2);

    if(val <= *m)
      end = m;
    
    else if(val > *m)
      start = m;
  }

  if(end == start)
      return end;
  else{
    if(val <= *start)
      return start;
    return end;
  }
}

#define M 20
#define MOD 7


void print(int* start, int* end, int val){

  std::cout << "printing arra with "<<end-start<<" elements and val is "<<val<<"\n";
  for(int* i = start;i<end;i++)
    std::cout << *i<<" ";
  std::cout<<"\n";

}

int main(){

  int* a[M];
  for(int i=0;i<M;i++)
    a[i] = new int[i+1];

  srand(time(NULL));

  for(int i=0;i<M;i++){
    for(int j=0;j<i+1;j++){

      int r = rand()%MOD;
      if(j == 0)
	a[i][j] =r;
      else if (r%3 == 0) 
	a[i][j] = a[i][j-1];
      else
	a[i][j] = a[i][j-1]+r;
    }
  }
    
  for(int i=0;i<M;i++){

    std::cout << "i = "<<i<<"\n";
    for(int k=0;k< (2*MOD) ;k++){

      std::cout << "k = "<<k<<"\n";
      
      int r = rand()%MOD;
      int* naive_pos = naive_lower_bound(a[i],a[i]+i+1,r);

      std::cout << "after naive "<<k<<"\n";

      print(a[i],a[i]+i+1,r);
      int* pos = lower_bound(a[i],a[i]+i+1,r);

      if(pos != naive_pos){
	std::cout << "ERROR!!\n"<< std::flush;
	exit(1);
      }
      

    }

  }

  
  /*
  int [] = {1};

  std::cout << "start: "<< a << " end: "<<a + sizeof(a)/sizeof(int)<<"\n";
  
  int* lower_bound(a, a + sizeof(a)/sizeof(int),1);

  */
  return 0;
}
