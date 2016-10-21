#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;
int* countSort(int a[],int n,int k)//n means the length of a,k means the max of a[i]
{
	int *b = new int[n];
	int *c = new int[k];
	for(int i=0;i<k;i++)
		c[i] = 0;
	for(int i=0;i<n;i++)
		c[a[i]] ++;
	for(int i=1;i<k;i++)
		c[i] = c[i] + c[i-1];
	for(int i=n-1;i>=0;i--)
	{
		b[c[a[i]]-1] = a[i];
		c[a[i]] --;
	}
	return b;
}
int main()
{
	char s;
	do{
		int N = 10;
		int *a = new int[N];
		//int a[10]= {1,4,5,6,4,2,7,4,8,4};
		//int a[10] = {   8   , 8   , 9 ,   5  ,  9 ,   9,    5,    4,    3,    2};
		srand(time(0));
		for(int i=0;i<N;i++)
		{
			a[i] = rand()%N;
			printf("%5d",a[i] );
		}   
		cout<<endl;
		long long begin = clock();
		int* b = countSort(a,N,N);
		long long end = clock();
		cout<<"time:"<<(end-begin)/(float)CLOCKS_PER_SEC*1000<<"ms"<<endl;

		for(int i=0;i<N;i++)
			printf("%5d",b[i] );
		cout<<endl;
		cin>>s;
	}while(s == 'y' || s == 'Y');
	return 0;
}