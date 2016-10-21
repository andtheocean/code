#include <stdio.h>
#include<iostream>
#include<cstdio>
#include<malloc.h>
#include <string.h>
#include<vector>
using namespace std;

struct Edge
{
    int next;
    int c;
};
int main( void ) 
{
vector<Edge> path[30];
int newp = 2;
Edge temp1 ={newp,0};
// temp1.next = 2;
// temp1.c = 0;
path[newp].push_back(temp1);
cout<<path[newp][0].next<<","<<path[newp][0].c;
  return 0;
}