#include <list>
#include <unordered_map>

#include <stdio.h>
typedef struct val_pos{
  int val;
  std::list<int>::iterator pos;
}val_pos;

#define EXIST(val,map) (val != map.end())

class LRUCache {
private:
  int cap;
  int m;

  std::unordered_map<int, val_pos> map;
  std::list<int> list;

public:
  LRUCache(int capacity) : map(capacity),cap(capacity),m(0){}

  void debug_list_snapshot(){
    for (auto it = list.begin(); it != list.end(); ++it) {
      printf("%d ",*it);
    }
    printf("\n");

  }
  int get(int key) {

    auto valiter = map.find(key);
    if( EXIST(valiter,map) ) {
      val_pos vp = valiter->second;
      list.erase(vp.pos);
      std::list<int>::iterator pos = list.insert( list.end(), key );
      vp.pos = pos;
      map[key]=vp;
      return vp.val;
    }
    return -1;
  }

  void put(int key, int value) {
    auto valiter = map.find(key);
    if( EXIST(valiter,map) ) {
      val_pos vp = valiter->second;
      list.erase(vp.pos);
    }
    else if(m==cap){
      int key = list.front();
      list.pop_front();
      map.erase(key);
    }
    else{
      m++;
    }
    std::list<int>::iterator pos = list.insert( list.end(), key );
    val_pos vp;
    vp.pos = pos;
    vp.val = value;
    map[key] = vp;
  }
};

int main(){
 LRUCache obj = LRUCache(2);

 //obj.put(1,1);
 //obj.debug_list_snapshot();
 //obj.put(2,2);
 //obj.debug_list_snapshot();
 //printf("a: %d\n",obj.get(1));
 //obj.put(3,3);
 //printf("b: %d\n",obj.get(2));
 //obj.put(10,13);
obj.put(3,17);
obj.put(6,11);
obj.put(10,5);
obj.put(9,10);
obj.get(13);
obj.put(2,19);
obj.get(2);
obj.get(3);
obj.put(5,25);
obj.get(8);
obj.put(9,22);
obj.put(5,5);
obj.put(1,30);
obj.get(11);
obj.put(9,12);
obj.get(7);
obj.get(5);
obj.get(8);
obj.get(9);

 obj.put(4,30);
obj.put(9,3);
obj.get(9);
obj.get(10);
obj.get(10);
obj.put(6,14);
obj.put(3,1);
obj.get(3);
obj.put(10,11);
obj.get(8);
obj.put(2,14);
obj.get(1);
obj.get(5);
 printf("%d\n",obj.get(4));
/*
obj.put(11,4);
obj.put(12,24);
obj.put(5,18);
obj.get(13);
obj.put(7,23);
obj.get(8);
obj.get(12);
obj.put(3,27);
obj.put(2,12);

obj.get(5);
 obj.debug_list_snapshot();

 obj.put(2,9);
 obj.put(13,4);

 obj.put(8,18);

 obj.put(1,7);
obj.get(6);
obj.put(9,29);
obj.put(8,21);
obj.get(5);

 obj.put(6,30);
obj.put(1,12);
obj.get(10);
obj.put(4,15);
obj.put(7,22);
obj.put(11,26);
obj.put(8,17);
obj.put(9,29);

 obj.get(5);
obj.put(3,4);
obj.put(11,30);
obj.get(12);
obj.put(4,29);
obj.get(3);
obj.get(9);
obj.get(6);
obj.put(3,4);
obj.get(1);
obj.get(10);
obj.put(3,29);
obj.put(10,28);
obj.put(1,20);
obj.put(11,13);
obj.get(3);
obj.put(3,12);
obj.put(3,8);
obj.put(10,9);
obj.put(3,26);
obj.get(8);
obj.get(7);
obj.get(5);
obj.put(13,17);
obj.put(2,27);
obj.put(11,15);
obj.get(12);
obj.put(9,19);
obj.put(2,15);
obj.put(3,16);
obj.get(1);


 obj.put(12,17);
obj.put(9,1);
obj.put(6,19);
obj.get(4);
obj.get(5);
obj.get(5);
obj.put(8,1);
obj.put(11,7);
obj.put(5,2);
obj.put(9,28);
obj.get(1);
obj.put(2,2);
obj.put(7,4);
obj.put(4,22);
obj.put(7,24);
obj.put(9,26);
obj.put(13,28);
obj.put(11,26);
*/
}
