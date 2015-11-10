#include <iostream>

typedef long int Int;

using namespace std;

int main()
{
	int n;
	cin >> n;
	Int l[100000];
	for(int i = 0; i < n; i++)
		cin >> l[i];
	Int max = 0;
	for(int i = 0; i < n; i++)
	{
		Int min = l[i];
		if(i > 0 && l[i] < l[i-1]) continue;
		for(int j = i; j < n; j++)
		{
			if(l[j] < min) min = l[j];
			Int s = min*(j-i+1);
			if(s > max) max = s;
			if(max > min*(n-i)) break;
		}
	}
	cout << max << endl;
	return 0;
}
