#include <iostream>
#include <cmath>

using namespace std;

typedef long long Int;

int main()
{
	Int N, NN;
	cin >> N;
	NN = N;
	bool p[50000];
	for(int i = 0; i < 50000; i++)
		p[i] = true;
	for(int i = 2; i < 240; i++)
	{
		if(!p[i]) continue;
		for(int j = 2*i; j < 50000; j += i)
			p[j] = false;
	}
	int s = sqrt(N);
	int pp[40], e[40], k = 0;
	for(int i = 2; i <= s; i++)
	{
		if(!p[i]) continue;
		if(N%i==0) {pp[k++] = i;e[k-1]=0;}
		while(N%i==0) {e[k-1]++;N/=i;}
	}
	if(N!=1) {pp[k++]=N;e[k-1]=1;}
	cout << NN << "=";
	for(int i = 0; i < k; i++)
	{
		cout << pp[i] << "(" << e[i] << ")";
	}
	cout << endl;
	return 0;
}
