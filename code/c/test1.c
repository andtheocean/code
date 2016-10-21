#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;


void quickSort(int p[],int a[], int left,int right)//begin from 0
{
	if(left == right)
		return;
	int x = left;
	int y = right;
	int mid = p[(left+right)/2];
	while(x < y)
	{
		while(p[y] > mid)
			y--;
		while(p[x] < mid)
			x++;
		if(x <= y)
		{
			int temp = p[x];
			p[x] = p[y];
			p[y] = temp;

			temp = a[x];
			a[x] = a[y];
			a[y] = temp;

			x++;
			y--;
		}
	}
	if(x < right) quickSort(p,a,x,right);
	if(y > left)   quickSort(p,a,left,y);
}

int main()
{
	srand(time(0));
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int p[10];
	for(int i=0;i<10;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	while(1)
	{
		for(int i=0;i<10;i++)
		{
			p[i]= rand()%(int)pow((double)10,(int)3);
			cout<<p[i]<<" ";
		}
		cout<<endl;
		quickSort(p,a,0,9);

		//检查p中是否有相同的元素 
		int begin,end;
		begin = -1;
		for(int i=0;i<9;i++)
		{
			if(p[i] == p[i+1])
			{
				if(begin == -1)
					begin = i;
			}
			else
			{
				if(begin != -1)
				{
					end = i;
					for(int i=begin;i<=end;i++)
					{
						p[i]= rand()%(int)pow((double)10,(int)3);
					}
					quickSort(p,a,begin,end);

					//重新从出现相同的数的地方开始扫描
					i = begin;
					begin = -1;
				}
			}
		}
		for(int i=0;i<10;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}