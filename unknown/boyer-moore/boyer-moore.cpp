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

int z_algorithm(char* str, int n,int** z){

  *z = new int[n];

  (*z)[0] = n;
  int l,r;
  l = r = -1;

  for(int i=1;i<n;i++){
    cout << "i = "<<i<<" l ="<<l<< " r ="<<r<<"\n";
    if(i>=r){
      int j;
      for(j=0;i+j<n && str[j]==str[i+j];j++)
	;
      (*z)[i] = j;
      if(j == 0){
	l = r = -1;
      }
      else{
	l = i;
	r = i+j;
      }
    }
    else if(i-l+(*z)[i-l]<r-l){
      cout <<"here\n";
      (*z)[i] = (*z)[i-l];
    }
    else{
      cout <<"there\n";
      int k;
      for(k=r;k<n && str[k] == str[k-l-1];k++)
	;
      
      (*z)[i] = k-i;
      l = i;
      r = k;
    }
  }
  return 0;
}

int get_good_suffix_tables(char* string,int n,int** L,int** H){

  *L = new int[n];
  if(!(*L))
    return -1;
  memset(*L,-1,sizeof(int)*n);
  char* str_reverse = new char[n+1];

  if(!str_reverse)
    return -1;

  for(int i = 0;i<n;i++)
    str_reverse[n-i-1] = string[i];

  str_reverse[n]='\0';
  cout <<"str reverse: "<< str_reverse <<"\n";
  int* z_vals;

  z_algorithm(str_reverse, n, &z_vals);

  for(int i=0;i<n;i++)
    cout <<"z["<<i<<"] = "<<z_vals[i]<<"\n";

  for(int i=n-1;i<-1;i--){
    if(z_vals[i]>0)
      (*L)[n-z_vals[i]] = i;
  }
  for(int i=0;i<n;i++)
    cout <<"L["<<i<<"] = "<<(*L)[i]<<" ";
  cout << "\n";
 
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
  int* L;
  int* H;
  get_good_suffix_tables(str,strlen(str),&L,&H);
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
