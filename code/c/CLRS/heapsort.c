#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;

void MAX_HEAPIFY(int a[],int i,int n)//n是堆中元素的总数 from 1 to n
{
	int left = i<<1;
	int right = left+1;
	int largest;
	if(left<=n && a[left-1] > a[i-1])
		largest = left;
	else
		largest = i;
	if(right<=n && a[right-1] > largest)
		largest = right;
	if(largest != i)
	{
		int temp = a[i-1];
		a[i-1] = a[largest];
		a[largest-1] = temp;
		MAX_HEAPIFY(a,largest,n);
	}
}


void BUILD_MAXHEAP(int a[],int n)//n是堆中元素的总数 from 1 to n
{
	for(int i=n/2;i>=1;i--)
		MAX_HEAPIFY(a,i,n);
}

void HEAP_SORT(int a[],int n)
{
	BUILD_MAXHEAP(a,n);
	for(int i=n;i>1;i--)
	{
		int temp = a[1-1];
		a[1-1] = a[i];
		a[i-1] = temp;
		MAX_HEAPIFY(a,1,n);
	}
}

int main()
{
	int a[10];
	//srand(time(0));
	for(int i=0;i<10;i++)
		a[i] = rand()%1000;
	for(int i=0;i<10;i++)
		printf("%5d",a[i] );
	cout<<endl;
	HEAP_SORT(a,10);
	for(int i=0;i<10;i++)
		printf("%5d",a[i] );
	cout<<endl;
	return 0;
}


// #include "stdafx.h"
// #include <stdio.h>
// #include <iostream>
// #include <string>
// #include <math.h>
// #include <time.h>
// using namespace std;

// void MAX_HEAPIFY(int a[],int i,int n)//n是堆中元素的总数 from 1 to n
// {
// 	int left = i<<1;
// 	int right = left+1;
// 	int largest;
// 	if(left<=n && a[left] > a[i])
// 		largest = left;
// 	else
// 		largest = i;
// 	if(right<=n && a[right] > largest)
// 		largest = right;
// 	if(largest != i)
// 	{
// 		int temp = a[i];
// 		a[i] = a[largest];
// 		a[largest] = temp;
// 		MAX_HEAPIFY(a,largest,n);
// 	}
// }

// void BUILD_MAXHEAP(int a[],int n)//n是堆中元素的总数 from 1 to n
// {
// 	for(int i=n/2;i>=1;i--)
// 		MAX_HEAPIFY(a,i,n);
// }

// void HEAP_SORT(int a[],int n)
// {
// 	BUILD_MAXHEAP(a,n);
// 	for(int i=n;i>1;i--)
// 	{
// 		int temp = a[0];
// 		a[0] = a[i];
// 		a[i] = temp;
// 		MAX_HEAPIFY(a,0,n);
// 	}
// }

// int main()
// {
// 	int a[10];
// 	//srand(time(0));
// 	for(int i=0;i<10;i++)
// 		a[i] = rand()%1000;
// 	for(int i=0;i<10;i++)
// 		printf("%5d",a[i] );
// 	cout<<endl;
// 	HEAP_SORT(a,10);
// 	for(int i=0;i<10;i++)
// 		printf("%5d",a[i] );
// 	cout<<endl;
// 	return 0;
// }