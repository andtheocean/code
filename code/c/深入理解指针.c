#include <stdio.h>
#include<iostream>
#include<cstdio>
#include<malloc.h>
#include <string.h>
using namespace std;

void GetMemory( long p )
{
  *((char **)p) = (char*) malloc( 100 );
}

int main( void ) 
{
  char*str = NULL;
  GetMemory( (long)(&str) ); 
  strcpy( str, "hello world" );
  printf( str );
}