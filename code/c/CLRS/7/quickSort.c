#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;

int PARTITION(int a[],int p,int r)
{
	int x = a[r];
	int i = p - 1;
	for(int j=p;j<=r-1;j++)
	{
		if(a[j] < x)//or <=?
		{
			i++;
			int  temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	a[r] = a[i+1];
	a[i+1] = x;
	return i+1;
}

void quickSort(int a[],int p,int r)
{
	if(p<r)
	{
		int q = PARTITION(a,p,r);
		quickSort(a,p,q-1);
		quickSort(a,q+1,r);
	}
}

int HOARE_PARTITION(int a[],int p,int r)
{
	int x = a[p];
	int i = p - 1;
	int j = r + 1;
	while(i<j)
	{
		do{
			j--;
		}while(a[j]>x);
		do{
			i++;
		}while(a[i]<x);
		if(i<j)
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	return j;
}

void HOARE_quickSort(int a[],int p,int r)
{
	if(p<r)
	{
		int q = HOARE_PARTITION(a,p,r);
		HOARE_quickSort(a,p,q);
		HOARE_quickSort(a,q+1,r);
	}
}

int main()
{
	char s;
	//do{
		int a[10];
		//int a[10]= {1,4,5,6,4,2,7,4,8,4};
		//int a[10] = {   8   , 8   , 9 ,   5  ,  9 ,   9,    5,    4,    3,    2};
		srand(time(0));
		for(int i=0;i<10;i++)
		{
			a[i] = rand()%10;
			printf("%5d",a[i] );
		}	
		cout<<endl;
		quickSort(a,0,9);
		for(int i=0;i<10;i++)
			printf("%5d",a[i] );
		cout<<endl;
		cin>>s;
	//}while(s == 'y' || s == 'Y');
	return 0;
}