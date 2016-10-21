void quickSort(int a[],int left,int right)//begin from 0
{
	if(left == right)
		return;
	int x = left;
	int y = right;
	int mid = a[(left+right)/2];
	while(x < y)
	{
		while(a[y] > mid)
			y--;
		while(a[x] < mid)
			x++;
		if(x <= y)
		{
			int temp = a[x];
			a[x] = a[y];
			a[y] = temp;
			x++;
			y--;
		}
	}
	if(x < right) quickSort(a,x,right);
	if(y > left) quickSort(a,left,y);
}