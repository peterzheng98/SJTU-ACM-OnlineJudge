#include <iostream>

using namespace std;

int main()
{
	int M,T,U,F,D;
	cin >> M >> T >> U >> F >> D;
	int ud = U+D;
	int ff = 2*F;
	int s = 0;
	for(int i = 0; i < T; i++)
	{
		char c;
		cin >> c;
		int ss = s;
		switch(c)
		{
		case 'u': case 'd': ss+=ud; break;
		case 'f': ss+=ff; break;
		}
		if(ss > M)
		{
			cout << i << endl;
			return 0;
		}
		s = ss;
	}
	cout << T << endl;
	return 0;
}
