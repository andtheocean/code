// #include <stdio.h>
// #include <string.h>
// #include <iostream>
// using namespace std;
// int main()
// {
//    int a = 1;
//    a += ++(a++);
//    cout<<a<<endl;
//         return -1;
// }
int accm = 0;
int sum(int x,int y)
{
    int t = x + y ;
    accm += t;
    return t;
}
