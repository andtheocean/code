//算法导论第七章思考题7-5三数取中划分  
//当需要排序的数达到一定的规模之后  三数取中划分具有明显的速度优势
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;
typedef struct Par_result
{
    int q;
    int t;
};
Par_result PARTITIONChooseThree(int a[],int p,int r)
{
    int y[3], x;
    y[0] = rand()%(r-p+1)+p;
    y[1] = rand()%(r-p+1)+p;
    y[2] = rand()%(r-p+1)+p;
    if(y[0] > y[1])
    {
        int temp = y[1];
        y[1] = y[0];
        y[0] = temp;
    }
    if(y[2] < y[0])
        x = a[y[0]];
    else if(y[2] < y[1])
        x = a[y[2]];
    else
        x = a[y[1]];
    //int x = a[r];
    int i = p - 1;
    int t = p - 1;
    for(int j=p;j<=r;j++)
    {
        if(a[j] < x)//or <=?
        {
            i++;
            t++;
            int  temp = a[t];
            if(t == j)
            {
                a[t] = a[i];
                a[i] = temp;
            }
            else
            {
                a[t] = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
        else if(a[j] == x)
        {
            t++;
            int temp = a[t];
            a[t] = a[j];
            a[j] = temp;
        }
    }
    Par_result par_result = {i,t};
    return par_result;
}

void quickSortChooseThree(int a[],int p,int r)
{
    while(p<r)
    {
        Par_result par_result = PARTITIONChooseThree(a,p,r);
        quickSortChooseThree(a,p,par_result.q);
        p = par_result.t + 1;
    }
}



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



int main()
{
    char s;
    int N = 10000000;
    int *a = new int[N];
    int *b = new int[N];
    srand(time(0));
    for(int i=0;i<N;i++)
    {
        a[i] = b[i] = rand()%N;
    }   
    long long begin = clock();
    quickSort(a,0,N-1);
    long long end = clock();
    cout<<"time:"<<(end-begin)/(float)CLOCKS_PER_SEC*1000<<"ms"<<endl;

    begin = clock();
    quickSortChooseThree(b,0,N-1);
    end = clock();
    cout<<"time:"<<(end-begin)/(float)CLOCKS_PER_SEC*1000<<"ms"<<endl;
    return 0;
}