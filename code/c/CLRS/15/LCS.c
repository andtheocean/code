#include "StdAfx.h"
#include <iostream>  
#include <vector>
using namespace std;  
void lcs_length(vector<char>p,vector<char>q,vector<vector<int>>&c)
{
	int m = p.size();
	int n = q.size();
	for(int i=0;i<=m;i++)
		c[i][0] = 0;
	for(int j=1;j<=n;j++)
		c[0][j] = 0;
	for(int i = 1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(p[i-1] == q[j-1])
			{
				c[i][j] = c[i-1][j-1] + 1;
			}
			else if(c[i-1][j] >= c[i][j-1])
			{
				c[i][j] = c[i-1][j];
			}
			else
				c[i][j] = c[i][j-1];
		}
	}
}
void lcs_print(int m,int n,vector<char>p,vector<char>q,vector<vector<int>>c)
{
	if(c[m][n] == 0)
		return;
	if(p[m-1] == q[n-1])
	{
		lcs_print(m-1,n-1,p,q,c);
		printf("%c",p[m-1]);
	}
	else if(c[m][n] == c[m-1][n])
		lcs_print(m-1,n,p,q,c);
	else
		lcs_print(m,n-1,p,q,c);
}
int main()
{
	//只需要修改这个数组便能运行不同的例子
	//算法导论第三版 p231 15-2  回文只需要将另一个字符串设为要求字符串的反序即可
	//懒得写代码反序  就手动反序输入了
	char p1[] = "character";
	char q1[] = "retcarahc";
	//char p1[] = "ABCBDAB";
	//char q1[] = "BDCABA";
	vector<char>p;
	vector<char>q;
	for(int i=0;i<sizeof(p1)/sizeof(char)-1;i++)
	{
		p.push_back(p1[i]);
	}
	for(int i=0;i<sizeof(q1)/sizeof(char)-1;i++)
	{
		q.push_back(q1[i]);
	}
	int m = p.size();
	int n = q.size();
	vector<vector<int>>c(m+1);
	for(int i=0;i<=m;i++)
	{
		c[i].resize(n+1);
	}
	lcs_length(p,q,c);
	lcs_print(m,n,p,q,c);
	return 0;
}
