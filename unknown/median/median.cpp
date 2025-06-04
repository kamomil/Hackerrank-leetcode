
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

std::map<int,int> mymap;
int rm_idx = 0;
int add_idx = 0;

/* 
    The algorithm in the first submit of this solution was  ok the problem was with the printing , need to deal both with overflow - convert to long
    and case the median is not integer - instead of converting to double I print the ".5" as a string
    Passes all tests!

    The alg is so complecated I forgot what I did in detail - in general: mymap - keys are the input values and the values of mymap are the number of time the key was enterd

*/
void dump_all(bool is_even,int key_idx,map<int,int>::iterator median_key){
    cout<<"== DUMP ==\n";
    cout<<"is even" << is_even <<'\n';
    cout<<"key_idx" << key_idx <<'\n';
    cout<<"median first" << median_key->first <<'\n';
    for (auto it = mymap.begin(); it != mymap.end(); ++it) {
    std::cout << it->first << ", " << it->second << '\n';
  }
    cout<<"== DUMP DONE==\n";
    
}
string fix( double x, int p )
{
    ostringstream strout ;
    strout << fixed << setprecision(p) << x ;
    string str = strout.str() ;
    size_t end = str.find_last_not_of( '0' ) + 1 ;
    return str.erase( end ) ;
}

void print_median(bool is_even,int idx,std::map<int,int>::iterator median_key){
    
     
    if(mymap.empty()){
        cout << "Wrong!"<<endl;
        return;
    }
   
    if(!is_even){
        cout << median_key->first << endl;
        return;
    }
    if(median_key->second>idx)
        cout << median_key->first << endl;
    else{
        median_key++;
        long v2 = (long)median_key->first;
        median_key--;
        long v1 = (long)median_key->first;
        if((v1+v2)%2 == 0){
            cout << ((v1+v2)/2) << endl;
        }
        else{
            long avg  =(v1+v2)/2;

            if(avg == 0){
                if(v1+v2 == 1)
                    cout <<"0.5"<<endl;
                else
                    cout <<"-0.5"<<endl;
            }
            else
                cout << avg<<".5" << endl;
        }
    }
}

void dec_median_key(std::map<int,int>::iterator& median_key,int *key_idx){
    if(*key_idx > 1)
        (*key_idx)--;
    else{
        
        median_key--;
        if(median_key != mymap.end() )
            *key_idx = median_key->second;
        else
            *key_idx = 1;
    }
    
}
void inc_median_key(std::map<int,int>::iterator& median_key,int *key_idx){
    
     if(median_key->second > *key_idx)
        (*key_idx)++;
     else{
        median_key++;
        *key_idx = 1;
     }
    
}
void remove_median(bool is_even, map<int,int>::iterator& median_key,int* key_idx, map<int,int>::iterator eit){
    
    
    if(is_even){    
        if(*key_idx == eit->second){//the median points to the last occurence 
            median_key++;
            *key_idx = 1;
        }
    }
    else
        dec_median_key(median_key,key_idx);
}

void remove_gt_median(bool is_even, std::map<int,int>::iterator& median_key,int* key_idx){
    if(!is_even)
        dec_median_key(median_key,key_idx);
}

void remove_lt_median(bool is_even, std::map<int,int>::iterator& median_key,int* key_idx){
    if(is_even)    
       inc_median_key(median_key,key_idx);
}

void insert_median(bool is_even, std::map<int,int>::iterator& median_key,int* key_idx){
    //if(add_idx == 3)
    //    cout<<"insert_med even "<<is_even<<" key_idx "<<*key_idx<<'\n';
    if(is_even)
       (*key_idx)++;
}

void insert_gt_median(bool is_even, std::map<int,int>::iterator& median_key,int* key_idx){
   
    if(is_even)
        inc_median_key(median_key,key_idx);
    
    //if(add_idx == 4)
          //  dump_all(is_even,*key_idx,median_key);
}

void insert_lt_median(bool is_even, std::map<int,int>::iterator& median_key,int* key_idx){
    if(!is_even)    
        dec_median_key(median_key,key_idx);
}


map<int,int>::iterator insert_and_update(bool* is_even, std::map<int,int>::iterator median_key,int* key_idx,int val){
    std::map<int, int>::iterator f = mymap.find(val); 
    bool was_empty = mymap.empty();   
    if (f != mymap.end()){
   
        f->second++;
    }
    else{
        mymap[val] = 1;
    }
    if(was_empty){
        median_key  = mymap.find(val); 
    }
    else if(median_key->first == val){
        insert_median(*is_even,median_key,key_idx);
        
    }
    else if(median_key->first < val){
        
        
        insert_gt_median(*is_even, median_key,key_idx);    
        
    }
    else{
        insert_lt_median(*is_even, median_key,key_idx);          
    }
    *is_even = !*is_even;
    return median_key;
    
}

map<int,int>::iterator erase_and_update(bool* is_even, map<int,int>::iterator median_key,int* key_idx, map<int,int>::iterator eit){
   
    int v = eit->first;
     
    if(median_key->first == v){
        remove_median(*is_even, median_key, key_idx, eit);          
    }
    else if(median_key->first < v){
            remove_gt_median(*is_even,median_key,key_idx);    
    }
    else{
        remove_lt_median(*is_even,median_key,key_idx);          
    }
    
    if(eit->second == 1){
        mymap.erase(eit);
        if(mymap.empty())
            median_key = mymap.begin();
    }
    else
        eit->second--;
    *is_even = !*is_even; 
return median_key;
    
}

void median(vector<char> s,vector<int> X) {
    
    
    bool is_even = true;
    int key_idx = 1;
    std::vector<char>::iterator its = s.begin();
    std::vector<int>::iterator itX = X.begin();
    std::map<int,int>::iterator median_key = mymap.begin();
    while(its != s.end()){
        
    if(*its == 'a'){
            add_idx++;
        //if(add_idx == 4)
           // dump_all(is_even,key_idx,median_key);
                
           median_key = insert_and_update(&is_even, median_key, &key_idx, *itX);
           print_median(is_even,key_idx,median_key);
       }
       else{
           rm_idx++;
            
           std::map<int,int>::iterator f =  mymap.find( *itX );
           
           if(f != mymap.end()){//elemnt exist
               
               median_key = erase_and_update(&is_even, median_key,&key_idx, f);
               print_median(is_even,key_idx,median_key);
                   
           }
           else
            cout << "Wrong!" << endl;
       }
        
        its++;
        itX++;
    }
}

int main(void){

//Helpers for input and output

   int N;
   cin >> N;
   
   vector<char> s;
    vector<int> X;
   char temp;
    int tempint;
   for(int i = 0; i < N; i++){
      cin >> temp >> tempint;
        s.push_back(temp);
        X.push_back(tempint);
   }
   
   median(s,X);
   return 0;
}

