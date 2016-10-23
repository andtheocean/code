#include "StdAfx.h"
#include <iostream>  
#include <vector>
using namespace std;  
void optimal_bst(vector<double>&p,vector<double>&q,vector<vector<double>>&e,vector<vector<double>>&w,vector<vector<int>>&root)
{
	int n = p.size() - 1;
	for(int i=1;i<=n+1;i++)
	{
		e[i][i-1] = q[i-1];
		w[i][i-1] = q[i-1];
	}
	for(int l=1;l<=n;l++)
	{
		for(int start = 1;start<=n-l+1;start++)
		{
			int end = start + l -1; 
			w[start][end] = w[start][end-1] + p[end] + q[end];
			e[start][end] = 1000;
			for(int r = start;r<=end;r++)
			{
				double t = e[start][r-1] + e[r+1][end]  + w[start][end];
				if(t<e[start][end])
				{
					e[start][end] = t;
					root[start][end] = r;
				}
			}
		}
	}
}

void print(vector<vector<int>>root,int a,int b,int p)
{
	if(p == -1)
		printf("k%d为根\n",root[a][b]);

	int r = root[a][b];
	//左子树
	if(r == a)
	{
		printf("d%d是k%d的左孩子\n",a-1,a);
	}
	else
	{
		printf("k%d是k%d的左孩子\n",root[a][r-1],r);	
		print(root,a,r-1,0);
	}
	//右子树
	if(r == b)
	{
		printf("d%d是k%d的右孩子\n",b,b);
	}
	else
	{
		printf("k%d是k%d的右孩子\n",root[r+1][b],r);	
		print(root,r+1,b,0);
	}
}
int main()
{
	//只需要修改这个数组便能运行不同的例子
	//算法导论第三版 p231 15.5-2
	double p1[] = {0,   0.04,0.06,0.08,0.02,0.10,0.12,0.14};
	double q1[] = {0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};
	//算法导论第三版 p227页例子
	//double p1[] = {0,   0.15,0.10,0.05,0.10,0.20};
	//double q1[] = {0.05,0.10,0.05,0.05,0.05,0.10};
	vector<double>p;
	vector<double>q;
	for(int i=0;i<sizeof(p1)/sizeof(double);i++)
	{
		p.push_back(p1[i]);
		q.push_back(q1[i]);
	}
	int n = p.size()-1;
	vector<vector<double>>e(n+2);
	vector<vector<int>>root(n+2);
	vector<vector<double>>w(n+2);
	for(int i=0;i<n+2;i++)
	{
		e[i].resize(n+2);
		root[i].resize(n+2);
		w[i].resize(n+2);
	}
	optimal_bst(p,q,e,w,root);
	print(root,1,n,-1);
	return 0;
}
