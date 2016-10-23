#include "StdAfx.h"
#include <iostream>  
#include <vector>
using namespace std;  
#define max_value   10000
typedef struct Point
{
	double x;
	double y;
};

double get_dis(Point p1,Point p2)
{
	return sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
}

//Double the Euclidean traveling salesman problem（双调欧几里得旅行商问题）
void DP(Point p[],double** dist,int n,int* c)
{
	for(int i=0;i<n;i++)
	{
		//case1: j=i和j=i+1
		int j;
		for(j=i;j<=i+1&&j<n;j++)
		{
			for(int k=0;k<i;k++)
			{
				if(dist[k][i] + get_dis(p[k],p[j]) < dist[i][j])
				{
					dist[i][j] = dist[k][i] + get_dis(p[k],p[j]);
					c[j] = k;//令c[i]=k是错的，令c[j]=k是一个不错的做法
				}
			}
		}
		//case3:j > i+1
		for(j=i+2;j<n;j++)
		{
			dist[i][j] = dist[i][j-1] + get_dis(p[j-1],p[j]);
		}
	}
}
void DP_print(Point*p,int* c,int n)
{
	bool* flag = new bool[n];
	for(int i=0;i<n;i++)
		flag[i] = 0;
	int i = n-1;
	cout<<"first path from n-1 to 0:"<<endl;
	while(i != 0)
	{
		printf("(%.2f,%.2f)->",p[i].x,p[i].y);
		i = c[i];
		flag[i] = 1;//放到i = c[i]后面  让flag[j]不被置1
	}
	printf("(%.2f,%.2f)\n",p[0].x,p[0].y);

	cout<<"second path from n-1 to 0:"<<endl;
    for(int j=n-1;j>0;j--)
	{
		if(flag[j] != 1)
			printf("(%.2f,%.2f)->",p[j].x,p[j].y);
	}
	printf("(%.2f,%.2f)\n",p[0].x,p[0].y);	
}
int main()
{
	double p1[][2] = {{0,6},{1,0},{2,3},{5,4},{6,1},{7,5},{8,2}};
	//double p1[][2] = {{1,1},{2,3},{3,1},{4,2}};  //result = 7.89
	int n = sizeof(p1)/2/sizeof(double);
	Point* p = new Point[n];
	for(int i=0;i<n;i++)
	{
		p[i].x = p1[i][0];
		p[i].y = p1[i][1];
	}
	double** dist = new double*[n];
	for(int i=0;i<n;i++)
		dist[i] = new double[n];
	
	int*   c = new int[n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			dist[i][j] = max_value;
	dist[0][0] = 0;
	dist[0][1] = get_dis(p[0],p[1]);
	DP(p,dist,n,c);
	printf("%.2f\n",dist[n-1][n-1]);
	DP_print(p,c,n);
}
