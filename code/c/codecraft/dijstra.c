#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;


struct Edge//save edge information
{
    int next;   //the next node
    int c;      //the cost   
};
vector<Edge> edge[502]; 

int n = 5;
int m = 6;
int s = 0;
int e = 2; 

bool mark[502] = {0};//whether get the shortest path
int  dis[502] = {-1};   
int  paths[502] = {0};  //paths[]是记录起点到各个点的最短路径数目的  
int  nums[502] = {1, 2, 1, 5, 3};   //nums[]是当前城市（点）的救援队伍数目的  
int  all_nums[502] = {0};   //all_nums[]是记录从起点到当前点的总救援队伍数目的 
unsigned short edge_input[502][3] ={{0, 1, 1},
                                    {0, 2, 2},
                                    {0, 3, 1},
                                    {1, 2, 1},
                                    {2, 4, 1},
                                    {3, 4, 1},
                                    };

int main()
{
    for(int i=0;i<502;i++)
    {
        edge[i].clear(); 
        mark[i]     = false;
        dis[i]      = -1;
        paths[i]    = 0;
        all_nums[i] = 0;
    }
    for(int i=0;i<m;i++)//save the edge information
    {
        Edge temp;
        temp.c    = edge_input[i][2];

        temp.next = edge_input[i][1];
        edge[edge_input[i][0]].push_back(temp);

        temp.next =  edge_input[i][0];
        edge[edge_input[i][1]].push_back(temp);
    }

   
    int newp   = s;
    mark[newp] = true;
    dis[newp]  = 0;
    paths[newp]= 1;
    for(int i=0;i<n;i++)
    {
        for(int k=0;k<edge[newp].size();k++)
        {
            int t = edge[newp][k].next;
            int c = edge[newp][k].c;
            if( mark[t] == true) {continue;}
            if( dis[t] == -1 || (dis[t] > dis[newp] + c) )
            {
                dis[t]      = dis[newp] + c;
                paths[t]    = paths[newp];
                all_nums[t] = all_nums[newp] + nums[newp];
            }
            else if( dis[t] == dis[newp] + c )
            {
                paths[t] = paths[t] + paths[newp];
                if(all_nums[t] < all_nums[newp] + nums[newp])
                    all_nums[t] = all_nums[newp] + nums[newp];
            }
        }
        int min = 1 << 30;
        for(int j=0;j<n;j++)
        {
            if(mark[j] == true) continue;
            if(dis[j]  == -1) continue;
            if(dis[j] < min)
            {
                newp = j;
                min  = dis[j];
            }
        }
        mark[newp] = true;
    }
    printf("%d %d\n",paths[e], all_nums[e] + nums[e]);
    return 0;
}



