#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;
struct Node
{
	float value;
	Node *next;
	Node();
};
Node::Node()
{
	next = 0;
}
//目前还没有考虑释放申请的空间
void bucketSort(float a[],int n)
{
	Node* node = new Node[n];
	for(int i=0;i<n;i++)
	{
		Node* temp = &node[(int)(10*a[i])];
		while(temp->next!=0 && temp->next->value<a[i])
		{
			temp = temp->next;
		}
		Node* newnode = new Node;
		newnode->value = a[i];
		newnode->next = temp->next;
		temp->next = newnode;
	}
	int j = 0;
	for(int i=0;i<n;i++)
	{
		Node* temp =  node[i].next;
		while(temp != 0)
		{
			a[j++] = temp->value;
			temp = temp->next;
		}
		//释放指针
		Node* now = node[i].next;
		while(now != 0)
		{
			temp = now->next;
			delete now;
			now = temp;
		}		
	}
	delete node;
}

int main()
{
	char s;
	do{
		int N = 10;
		float *a = new float[N];
		//int *a = new int[N];
		srand(time(0));
		for(int i=0;i<N;i++)
		{
			a[i] = (float)(rand()%10)/N;
			printf("%6.3f",a[i] );
			//printf("%5f",a[i] );
		}   
		cout<<endl;
		long long begin = clock();
		bucketSort(a,N);//
		long long end = clock();
		cout<<"time:"<<(end-begin)/(float)CLOCKS_PER_SEC*1000<<"ms"<<endl;

		for(int i=0;i<N;i++)
			//printf("%5f",a[i] );
			printf("%6.3f",a[i] );
		cout<<endl<<"please input y or Y to continue,any other means quit:"<<endl;
		cin>>s;
	}while(s == 'y' || s == 'Y');
	return 0;
}