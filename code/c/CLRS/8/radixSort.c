#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;

//d是排序的依据，根据排序结果去改变a中元素的顺序，将结果存储在b中
int* countSort(int d[],int a[],int n,int k)//n means the length of a,k means the max of a[i]+1
{
	int *b = new int[n];
	int *c = new int[k];
	for(int i=0;i<k;i++)
		c[i] = 0;
	for(int i=0;i<n;i++)
		c[d[i]] ++;
	for(int i=1;i<k;i++)
		c[i] = c[i] + c[i-1];
	for(int i=n-1;i>=0;i--)
	{
		b[c[d[i]]-1] = a[i];//必须用一个新数组去存储  如果直接在a上原址操作会互相覆盖，不能得到正确结果
		c[d[i]] --;
	}
	delete c;
	return b;
}

void radixSort(int a[],int n,int k)//k表示元素最多的位数
{
	int *d = new int[n];//保存当前要排序的位
	for(int i=1;i<=k;i++)//有多少位就进行多少次排序
	{
		for(int j=0;j<n;j++)//获得每一个元素对应的位的值
		{
			int x = (int)pow((float)10,(float)(i-1));
			d[j] = a[j]/x%10;
		}
		int *b = countSort(d,a,n,n);
		for(int l=0;l<n;l++)
			a[l] = b[l];
		delete b;
	}
}
int main()
{
	char s;
	do{
		int N = 10;
		int *a = new int[N];
		srand(time(0));
		for(int i=0;i<N;i++)
		{
			a[i] = rand()%1000;
			printf("%5d",a[i] );
		}   
		cout<<endl;
		long long begin = clock();
		radixSort(a,N,3);//3表示元素最多有三位数
		long long end = clock();
		cout<<"time:"<<(end-begin)/(float)CLOCKS_PER_SEC*1000<<"ms"<<endl;

		for(int i=0;i<N;i++)
			printf("%5d",a[i] );
		cout<<endl;
		cin>>s;
	}while(s == 'y' || s == 'Y');
	return 0;
}