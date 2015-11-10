#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s;
	int S[4000];
	int k = 0;
	int IF = 0, THEN = 1, ELSE = 2, BEGIN = 3, END = 4;
	while(!cin.eof())
	{
		cin >> s;
		if(!cin.eof()) break;
		if(s == "if")
		{
			S[k++] = IF;
		}
		else if(s == "then")
		{
			if(k <= 0 || S[k-1] != IF)
			{
				cout << "Error!" << endl;
				return -1;
			}
			else
			{
				S[k-1] = THEN;
			}
		}
		else if(s == "else")
		{
			if(k <= 0 || S[k-1] != THEN)
			{
				cout << "Error!" << endl;
				return -1;
			}
			else
			{
				k--;
			}
		}
		else if(s == "begin")
		{
			S[k++] = BEGIN;
		}
		else if(s == "end")
		{
			while(k > 0 && S[k-1] == THEN) k--;
			if(k <= 0 || S[k-1] != BEGIN)
			{
				cout << "Error!" << endl;
				return -1;
			}
			else
			{
				k--;
			}
		}
	}
	while(k > 0 && S[k-1] == THEN) k--;
	if(k > 0) cout << "Error!" << endl;
	else cout << "Match!" << endl;
	return 0;
}
