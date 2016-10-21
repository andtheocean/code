int simple(int *x,int y)
{
    int t = *x + y;
    *x = t;
    return t;
}