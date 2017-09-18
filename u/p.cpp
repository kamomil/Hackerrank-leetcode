#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
using namespace std;

enum state{
  READ_LEADING_BYTE,
  READ_10_BYTE
};

void pack_unicode_to_int(unsigned char* unicode,int bytes,unsigned int* unicode_int){

  //cout<< "pack_unicode_to_int bytes = "<<bytes<<"\n";
  
  //for(int i=0;i<bytes;i++)
  //  printf("0x%02x\n",unicode[i]);
    
  if(bytes == 1)
    *unicode_int = (unsigned int)unicode[0];
  else{
    int nbits = 2;
    *unicode_int = 0;
    int shift = 0;
    for(int i = bytes-1;i>0;i--){

      if(bytes == 4 && i == 1)
	nbits = 3;
      unsigned char mask = (1 << nbits) -1;//create a mask of last shift bits
      unsigned char last_nbits = (unicode[i-1] & mask);

      if(bytes == 4 && i == 1)
	unicode[i] |= (last_nbits << 4);
      else
	unicode[i] |= (last_nbits << 8-nbits);
      unicode[i-1] >>= nbits;
      nbits+=2;

      unsigned int unicode_i = (unsigned int)unicode[i];

      unicode_i = (unicode_i << shift);

      *unicode_int |= unicode_i;
      shift+=8;
      
    }
    if(bytes == 2){
      unsigned int u = (unsigned int) (unicode[0] & 0x07);
      
      *unicode_int |= (u<<8);
    }

    //printf("0x%04x\n",*unicode_int);

  }
    
  
}

int main(int argc, char* argv[]){

  char utf_byte = 0;

  unsigned char unicode[4] = {0,0,0,0};

  ofstream out_file;

  state st = READ_LEADING_BYTE;
  
  out_file.open ("data2.bin", ios::out | ios::binary);
    
  //11000010:10000000
  //11011111:10111111

  unsigned int pref = 0xfeff;
  out_file.write((char*)&pref,4);
  int nbytes = 0;
  int byte_idx = 0;
  int i = 0;
  ifstream infile (argv[1], ios::in|ios::binary);
  if( ! infile.is_open())
    return -1;
  
  while ( infile.read (&utf_byte, 1) ){

    cout <<i<<" ";
    printf("0x%02x\n",utf_byte);
    i++;
    //if(i==20)
    //  return 0;
    switch(st){

    case READ_LEADING_BYTE:

      if((utf_byte & 0x80) == 0){//if first bit is 0
	unicode[0]  = utf_byte;
	unsigned int unicode_int = 0;
	pack_unicode_to_int(unicode,1,&unicode_int);
	out_file.write((char*)&unicode_int,4);
	memset(unicode,0,4);
      }
      else if( ((utf_byte ^ 0xc0) & 0xe0) == 0){
	unicode[0]  = utf_byte & 0x01f;
	st = READ_10_BYTE;
	nbytes = 2;
	byte_idx = 1;
      }
      else if( ((utf_byte ^ 0xe0) & 0xf0) == 0){
	unicode[0]  = utf_byte & 0x0f;
	st = READ_10_BYTE;
	nbytes = 3;
	byte_idx = 1;
	
      }
      else if( ((utf_byte ^ 0xf0) & 0xf8) == 0){
	unicode[0]  = utf_byte & 0x07;
	st = READ_10_BYTE;
	nbytes = 3;
	byte_idx = 1;

      }
      else{
	//text corrupted
      }
      break;

    case READ_10_BYTE:      
      if( ((utf_byte ^ 0x80) & 0xc0) == 0){
	unicode[byte_idx] = utf_byte & 0x3f;
      
	byte_idx++;
	if(byte_idx == nbytes){
	  unsigned int unicode_int = 0;
	  pack_unicode_to_int(unicode,nbytes,&unicode_int);
	  out_file.write((char*)&unicode_int,4);
	  memset(unicode,0,4);
  

	  byte_idx = nbytes = 0;
	  st = READ_LEADING_BYTE;
	}
      }
      else{
	//text corrupted
	st =READ_LEADING_BYTE;
	byte_idx = nbytes = 0;
      }
      break;
    }
  }
  infile.close();
  
   return 0;
   
}

