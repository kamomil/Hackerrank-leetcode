

/*
class Anagrams{
  char word[26];
  list<char*> anagrams;
};
*/
/*
  allocate a hash

  for each a in ana:
  asort = sort(a)
  if not H[hash(asort)]
   add a list that contain only a to H[hash[a]]
  else
   add a to the list of a


*/

/*
  ana[0] = "123"
  and[1] = "dafna"
  ana[2] = "231"
  ana[3] = "312"
  ana[4] = "nfaad"
*/

#include <list>
#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <string.h>

/*
struct hashing_func {
  unsigned long operator()(const string& key) const {
    unsigned long hash = 0;
    for(size_t i=0; i<key.size(); i++)
      hash += (71*hash + key[i]) % 5;
    return hash;
  }
};

struct key_equal_fn {
  bool operator()(const string& t1, const string& t2) const {
    return !(t1.compare(t2));
  }
};
*/


/*
template <> bool key_equal_fn<char*>(char* t1, char* t2)
{
  for(int i=0;i<26;i++)
    if(t1[i] != t2[i])
      return False;
  return True;
}
*/
/*
std::unordered_map<char*,
                   std::list<char*>,
                   std::hash<char*>,
                   std::function<bool(char*, char*)> > map;
*/

//std::unordered_map<char*, std::list<char*>> map;

struct hashing_func {
  unsigned long operator()(const char* key) const {
    unsigned long hash = 0;
    for(int i=0; i<26; i++)
      hash += (71*hash + key[i]) % 5;
    return hash;
  }
};

struct key_equal_fn {
  bool operator()(const char* t1, const char* t2) const {
    for(int i=0;i<26;i++)
      if(t1[i] != t2[i])
        return false;
    return true;
  }
};

std::unordered_map<char*, std::list<char*>,hashing_func, key_equal_fn> map;


/*
  unordered_map<string, string> mymap(n, (const std::hash<string> &)hashing_func,
  (const std::equal_to<string> &)(function<bool(string,string)>(key_equal_fn<string>))) ;

 */

int print_anagrams(char* ana[],int sz){


  for(int i=0;i<sz;i++){
    char iword[26] = {0};
    memset(iword,0,26);
    for(int j=0;ana[i][j];j++){
      iword[ana[i][j]-'a']++;
    }
    if(map.find(iword) == map.end()){
      std::list<char*> lst = {ana[i]};
      map[iword] = lst;
    }
    else{
      map[iword].push_back(ana[i]);
    }
  }
  for(auto it = map.begin(); it != map.end() ; it++){
    std::list<char*> l = it->second;
    for(auto lit = l.begin(); lit != l.end() ; lit++){
      std::cout << *lit << " ";
    }
    std::cout << "\n";
  }
}

int main(){

  char* ana[10];
  ana[0] = "blu";
  ana[1] = "dafna";
  ana[2] = "ulb";
  ana[3] = "aafnd";
  ana[4] = "lub";
  ana[5] = "bua";
  ana[6] = "ytia";
  ana[7] = "aity";
  ana[8] = "itay";
  ana[9] = "fnaad";

  print_anagrams(ana,10);

}
