#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <string.h>
#include <stdio.h>

using namespace std;


int boyer_more_preprocessing(char* string,int n, int** L, int** H,int** B){

  return 0;
}


int get_bad_char_table(char* string,int n,int** B){

  //cout <<n;
 
  int* Bnew = new int[256*n];
  if(!Bnew)
    return -1;
  for(int c = 0;c<256;c++){

    int i = n-1;
    do{
      while(i>-1 && string[i] == c){
	Bnew[c*n+i] = 0;
	i--;
      }
      
      int k = i;
      while(i> -1 && string[i] !=c)
	i--;

      while(k>i){
	char cc = (char) c;
	Bnew[c*n+k] = i;
	//if(cc<='z' && cc>='a')
	//  printf("B[%c][%d] = %d\n",cc,k,Bnew[c*n+k]);
	k--;
      }
    }while(i>-1);
  }
  *B = Bnew;
  return 0;
}

int grep(char* str,int ns,const char* text, int nt,list<int>& matches,int* bad_char_t){

  if(nt<ns)
    return 0;

  //cout <<"text:"<<text <<"\n";

  int shift = ns-1;
    
  while(shift<nt){

    int i = ns-1;
    while(i>-1 && str[i] == text[shift+i+1-ns]){
      i--;
    }
    if(i==-1){
      matches.push_back(shift);
      shift++;
    }
    else{
      int c = (int) text[shift+i+1-ns];
      int s = bad_char_t[c*ns+i];
      shift += i - s;
    }
    
  }
  return 0;

}

int main( int argc, char *argv[] ){


  char* str = argv[1];
  char* file = argv[2];

  int* B;
  get_bad_char_table(str,strlen(str),&B);

  cout << str << "B created \n";
  //return 0;
  string line;
  ifstream myfile (file);
  if (myfile.is_open()){
    while ( getline (myfile,line) ){
      list<int> l;
      cout << line<<"\n";
      const char *cline = line.c_str();
      grep(str,strlen(str),cline,strlen(cline),l,B);
      if(!l.empty()){
	char* m = new char[strlen(cline)];
	memset(m,'0',strlen(cline));
	
	for(auto it = l.begin();it != l.end();it++)
	  m[*it]='1';
	cout <<m<<"\n";
      }
    
      myfile.close();
    }
  }

  else cout << "Unable to open file"; 

  
  return 0;
  

  


}
