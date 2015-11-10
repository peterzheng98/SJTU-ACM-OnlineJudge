#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int N;
	cin >> N;
	int m[150][150];
	int l=0,r=N,u=0,d=N;
	int i=0,j=0,k=1,b=0;
	while(true)
	{
		if(j<l || j>=r || i<u || i>=d) break;
		m[i][j] = k;
		k++;
		if(b==0)
		{
			j++;
			if(j>=r)
			{
				j--;
				i++;
				b=1;
				u++;
			}
		}
		else if(b==1)
		{
			i++;
			if(i>=d)
			{
				i--;
				j--;
				b=2;
				r--;
			}
		}
		else if(b==2)
		{
			j--;
			if(j<l)
			{
				j++;
				i--;
				b=3;
				d--;
			}
		}
		else
		{
			i--;
			if(i<u)
			{
				i++;
				j++;
				b=0;
				l++;
			}
		}
	}
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			cout << setw(6) << m[i][j];
		}
		cout << endl;
	}
	return 0;
}

