#include <iostream>

using namespace std;

int main()
{
	int s = 0;
	int t = 0;
	for(int i = 1; i <= 12; i++)
	{
		int b;
		cin >> b;
		t += 300;
		t -= b;
		if(t < 0)
		{
			cout << -i << endl;
			return 0;
		}
		s += t/100;
		t %= 100;
	}
	cout << s*120+t << endl;
	return 0;
}
