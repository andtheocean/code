#include "StdAfx.h"
#include <iostream>  
#include <vector>
using namespace std;  
vector<vector<int>>m(10);
vector<vector<int>>s(10);
void matrix_chain_order(vector<int>p)
{
	int length = p.size()-1;//p元素的个数比矩阵个数多1
	for(int l=2;l<= length;l++)//矩阵长度
	{
		for(int start=1;start<=length-l+1;start++)//矩阵链起点
		{
			int end = start + l - 1;//矩阵链终点
			m[start][end] = INT_MAX;
			for(int k=start;k<=end-1;k++)
			{
				int q = m[start][k] + m[k+1][end] + p[start-1]*p[k]*p[end]; 
				if(q < m[start][end])
				{
					m[start][end] = q;
					s[start][end] = k;
				}
			}
		}
	}
}

void print(int i,int j)
{
	if(i==j)
		printf("A%d",i);
	else
	{
		cout<<"(";
		print(i,s[i][j]);
		print(s[i][j]+1,j);
		cout<<")";
	}
}
int main()
{
	//int p1[]={30,35,15,5,10,20,25};
	int p1[]={5,10,3,12,5,50,6};
	vector<int>p;
	for(int i=0;i<sizeof(p1)/4;i++)
		p.push_back(p1[i]);
	for(int i=0;i<10;i++)
	{
		m[i].resize(10);
		m[i][i] = 0;
	}
	for(int i=0;i<10;i++)
		s[i].resize(10);
	// m[1][2] = 3;
	// int a = m[1][2];
	matrix_chain_order(p);
	int len = p.size()-1;
	cout<<"最少次数："<<m[1][len]<<endl;
	cout<<"结合方式：";
	print(1,len);
	cout<<endl;
	return 0;
}
