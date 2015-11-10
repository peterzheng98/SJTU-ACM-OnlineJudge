#include <cstdio>
#include <cstdlib>

using namespace std;

void sort(int *a, int l, int r)
{
	if(l > r-2) return;
	int p=rand()%(r-l)+l;
	int tmp=a[l];a[l]=a[p];a[p]=tmp;
	int q=r-1;
	p=l;
	while(p < q)
	{
		if(a[p+1]<a[p]){tmp=a[p];a[p]=a[p+1];a[p+1]=tmp;p++;}
		else{tmp=a[p+1];a[p+1]=a[q];a[q]=tmp;q--;}
	}
	sort(a,l,p);
	sort(a,p+1,r);
}

int main()
{
	int n;
	scanf("%d",&n);
	int a[10000];
	for(int i = 0; i < n; i++)
		scanf("%d",&a[i]);
	sort(a,0,n);
	for(int i = 0; i < n; i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
