#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;
void sort_WithLinerCost_InOriginPlace(int a[],int n,int k)//所有的元素都属于1到k
{
	int *c = new int[k+1];
	int *p = new int[k+1];
	for(int i=0;i<=k;i++)
	{
		c[i] = 0;
		p[i] = 0;
	}	
	for(int i=0;i<n;i++)
	{
		c[a[i]] ++;
		p[a[i]] ++;
	}
	for(int i=2;i<=k;i++)
	{
		c[i] += c[i-1];
		p[i] += p[i-1];
	}
	int j = 0;
	p[0] = -1;
	while(j<n)
	{
		//这个元素已经放到了合适的位置  则直接跳过
	    //  由于a[j] 属于1到k  所以当a[j] == 1的时候 p[a[j]-1] = -1 这个时候必然满足 j>p[a[j]-1]
		//所以不用再对a[j] =1的时候进行特殊判断
		if(j>(p[a[j]-1]-1) && j <= (p[a[j]]-1))
			j++;
		else
		{ 	
			int temp = a[c[a[j]]-1];
			a[c[a[j]]-1] = a[j];
			c[a[j]] --;
			a[j] = temp;
		}
	}
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
			a[i] = rand()%N+1;
			printf("%5d",a[i] );
		}   
		cout<<endl;
		long long begin = clock();
		sort_WithLinerCost_InOriginPlace(a,N,N);
		long long end = clock();
		cout<<"time:"<<(end-begin)/(float)CLOCKS_PER_SEC*1000<<"ms"<<endl;

		for(int i=0;i<N;i++)
			printf("%5d",a[i] );
		cout<<endl;
		cin>>s;
	}while(s == 'y' || s == 'Y');
	return 0;
}