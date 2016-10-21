// test.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<stdio.h>  
#include<iostream>
#include<vector>  
using namespace std;  

struct Edge{  
     int next;  
     int c;  
};  
vector<Edge> edge[502]; 
vector<Edge>  path[30]; 
unsigned short edge_input[502][3] ={{0,13,15},                                 
                                    {0,8,17},
                                    {0,19,1},
                                    {0,4,8},
                                    {1,0,4},
                                    {2,9,19},
                                    {2,15,8},
                                    {3,0,14},
                                    {3,11,12},
                                    {4,1,15},
                                    {4,5,17},
                                    {5,8,18},
                                    {5,9,14},
                                    {5,6,2},
                                    {6,17,4},
                                    {7,13,1},
                                    {7,16,19},
                                    {8,6,1},
                                    {8,12,17},
                                    {9,14,11},
                                    {10,12,1},
                                    {11,7,12},
                                    {11,4,7},
                                    {12,14,5},
                                    {13,17,12},
                                    {13,4,2},
                                    {14,19,9},
                                    {15,10,14},
                                    {15,18,2},
                                    {16,8,1},
                                    {17,9,14},
                                    {17,19,3},
                                    {17,18,10},
                                    {18,15,8},
                                    {18,3,8},
                                    {19,18,12},
                                    {2,3,20},
                                    {3,5,20},
                                    {5,7,20},
                                    {7,11,20},
                                    {11,13,20},
                                    {17,11,20},
                                    {11,19,20},
                                    {17,5,20},
                                    {5,19,20}};

int   dis[502];  
bool mark[502];  
int paths[502];  //paths[]是记录起点到各个点的最短路径数目的  
int  point_must_gothrough[502] = {3,5,7,11,13,17};   //nums[]是当前城市（点）的救援队伍数目的  
//int all_nums[502];   //all_nums[]是记录从起点到当前点的总救援队伍数目的  

int n = 20;
int m = 45;
int s = 2;
int e = 19;

bool is_point_must_gothrough(int a)
{
    for(int i=0;i<6;i++)
    {
        if(a == point_must_gothrough[i]){return true;}
    }
    return false;
}

int main()
{
    for(int i=0;i<30;i++)
    {
        path[i].clear();
    }
    for(int i=0;i<502;i++)
    {

        edge[i].clear(); 
        mark[i]     = false;
        dis[i]      = -1;
        //all_nums[i] = 0;
    }
    for(int i=0;i<m;i++)//save the edge information
    {
        Edge temp;


        // if(is_point_must_gothrough(edge_input[i][0]) || is_point_must_gothrough(edge_input[i][1]) )///////////////////need to consern
        // {    
        //     temp.c    = edge_input[i][2];
        // }
        //else{temp.c    = edge_input[i][2] + 1000;}
        temp.c    = edge_input[i][2] + 1000;

        temp.next = edge_input[i][1];
        edge[edge_input[i][0]].push_back(temp);

        // temp.next =  edge_input[i][0];
        // edge[edge_input[i][1]].push_back(temp);
    }

   
    int newp   = s;
    mark[newp] = true;
    dis[newp]  = 0;
    Edge temp1 ={newp,0};path[newp].push_back(temp1);
    //cout<<path[newp][0].next<<","<<path[newp][0].c;
    for(int i=0;i<n;i++)
    {
        for(int k=0;k<edge[newp].size();k++)
        {
            int t = edge[newp][k].next;
            int c = edge[newp][k].c;
            if( mark[t] == true) {continue;}
            if( dis[t] == -1 || (dis[t] > dis[newp] + c) )
            {
                dis[t]    = dis[newp] + c;                
                Edge temp;
                temp.c = c;
                temp.next = t;//just as a point to record the path
                path[t] = path[newp];                
                path[t].push_back(temp);
            }
        }
        int min = 1 << 30;
        for(int j=0;j<n;j++)
        {
            if(mark[j] == true) continue;
            if( dis[j] == -1) continue;
            if( dis[j] < min)
            {
                newp = j;
                min  = dis[j];
            }
        }
        mark[newp] = true;////////////maybe need to fix the path[]
        cout<<newp<<endl;
    }
    int total = 0;
    for(int i=0;i<path[e].size();i++)
    {
        if(path[e][i].c > 1000)
            total = total + path[e][i].c - 1000;
        else
            total = total + path[e][i].c;
        cout<<path[e][i].next<<"->";
    }
    cout<<endl<<total<<endl;
   // printf("%d %d\n",paths[e], all_nums[e] + nums[e]);
    return 0;
}



