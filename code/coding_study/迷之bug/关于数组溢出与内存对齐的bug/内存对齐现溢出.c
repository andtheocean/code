// test.cpp : 定义控制台应用程序的入口点。
//

// #include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include<string.h>

using namespace std; 
                    // 7 1 2 4 6 9 3 5 8
                    // 3 6 5 2 8 7 1 9 4
                    // 4 9 8 5 1 3 6 7 2
                    // 9 2 4 1 5 6 8 3 7
                    // 5 7 6 3 9 8 2 4 1
                    // 1 8 3 7 2 4 9 6 5
                    // 2 3 1 9 7 5 4 8 6
                    // 6 4 7 8 3 2 5 1 9
                    // 8 5 9 6 4 1 7 2 3
//unsigned char arr[9][9]=;
int arr[10][10]={   {7, 1, 2, 0, 6, 0, 3, 5, 8},
                    {0, 6, 5, 2, 0, 7, 1, 0, 4},
                    {0, 0, 8, 5, 1, 3, 6, 7, 2},
                    {9, 2, 4, 0, 5, 6, 0, 3, 7},
                    {5, 0, 6, 0, 0, 0, 2, 4, 1},
                    {1, 0, 3, 7, 2, 0, 9, 0, 5},
                    {0, 0, 1, 9, 7, 5, 4, 8, 6},
                    {6, 0, 7, 8, 3, 2, 5, 1, 9},
                    {8, 5, 9, 0, 4, 0, 0, 2, 3},
                }; 
                
bool raw_number[9][9]={0};//if the number x exists  in the raw y,then raw_number[y][x] = 1
bool list_number[9][9]={0}; 
bool nineGrid_number[9][9]={0};
// bool raw_number[10][10]={0};//if the number x exists  in the raw y,then
// bool list_number[10][10]={0}; 
// bool nineGrid_number[10][10]={0};
//int count = 0;
// int temp= 0;
//int count = 0; 
unsigned char count;
bool ok;
struct node//storge the point need to search 
{
    int x;
    int y;
}target[81];


int get_nineGrid_num(int i, int j)
{
    return i/3*3 + j/3;//really fantastic
}

bool check(int i,int j,int key)
{
    int t = get_nineGrid_num(i,j);
    if(raw_number[i][key] || list_number[j][key] 
        || nineGrid_number[t][key] )
        return 0;
    return 1;
}

void print_result()
{
    // for(int i=0;i<9;i++)
    // {
    //     for(int j=0;j<9;j++)
    //     {
    //         cout<<arr[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
        for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
            if(j != 8) printf("%d ", arr[i][j]);
            else printf("%d\n", arr[i][j]);
}

void DFS(int k)
{

    if(k==count){

        //cout<<int(count)<<count<<endl;
        ok = 1;
        print_result();
        return;
    }
    int t = get_nineGrid_num(target[k].x,target[k].y);
    for(int i=1;i<=9;++i){
        if(check(target[k].x,target[k].y,i))
        {
            raw_number[target[k].x][i] = 1;
            list_number[target[k].y][i] = 1;
            nineGrid_number[t][i] = 1;
            arr[target[k].x][target[k].y] = i;

            DFS(k+1);

            if(ok==1)return;

            raw_number[target[k].x][i] = 0;
            list_number[target[k].y][i] = 0;
            nineGrid_number[t][i] = 0; 
            arr[target[k].x][target[k].y] = 0; 
        }
    }
}
int main()
{
    // while(1)
    // {
        memset(raw_number,0,sizeof(raw_number));
        memset(list_number,0,sizeof(list_number));
        memset(nineGrid_number,0,sizeof(nineGrid_number));
        count = 0;
        for(int i=0; i<9;i++){
            for(int j=0;j<9;j++){
               //cin>>arr[i][j];
               if(arr[i][j]){
                    raw_number[i][arr[i][j]] = 1;
                    list_number[j][arr[i][j]] = 1;
                    nineGrid_number[get_nineGrid_num(i,j)][arr[i][j]] = 1;
               }
 //              else if( arr[i][j] == '?'){
               else if( arr[i][j] == 0){
                    target[count].x = i;
                    target[count].y = j;
                    cout<<target[count].x<<"," ;
                    cout<<target[count].y<<count<<int(count)<<"  " ;

                     count++; 

                    //cout<<count<<" ";
                    //return 0;
               }
               else{
                    cout<<"wrond input";
                    return 0;
               }
            }
        }
        ok = 0;

        DFS(0);
    // }
    return 0;
}