#include <iostream>

using namespace std;

int getsqr(int i,int j)
{
	return i/3*3+j/3;
}

bool solvecase()
{
	bool row[9][9];
	bool col[9][9];
	bool sqr[9][9];
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			row[i][j] = false;
			col[i][j] = false;
			sqr[i][j] = false;
		}
	bool r = true;
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			int d;
			int s = getsqr(i,j);
			cin >> d;
			if(row[i][d-1]) r = false;
			if(col[j][d-1]) r = false;
			if(sqr[s][d-1]) r = false;
			row[i][d-1] = col[j][d-1] = sqr[s][d-1] = true;
		}
	return r;
}

int main()
{
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		bool r = solvecase();
		if(r) cout << "Right" << endl;
		else cout << "Wrong" << endl;
	}
	return 0;
}
