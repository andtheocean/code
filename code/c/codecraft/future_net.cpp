#include "stdio.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    char topo[5000];
    char *demand;
    int demand_num;

    char *topo_file = argv[1];
    file *edge_num;
    edge_num = fopen(topo, 'r');
    cout<<topo[0]<<endl;
    return 0;
}

