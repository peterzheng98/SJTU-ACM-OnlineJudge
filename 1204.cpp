#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Vector
{
public:
	Vector(){data = new string[2]; capacity=2; length=0;}
	~Vector(){delete []data;}

	void doubleSpace()
	{
		string* tmp = new string[capacity*2];
		capacity *= 2;
		for(int i = 0; i < length; i++)
			tmp[i] = data[i];
		delete []data;
		data = tmp;
	}

	void append(string s)
	{
		if(length == capacity)
			doubleSpace();
		data[length++] = s;
	}

	bool appendToEOL()
	{
		char buf[2001];
		cin.getline(buf,2000);
		string s(buf);
		if(s == "******") return false;
		append(s);
		return true;
	}

	void insertToEOL(int i, int j)
	{
		if(i < 1 || i > length)
		{
			cout << "Error!" << endl;
			return;
		}
		if(j < 1 || j > data[i-1].length()+1)
		{
			cout << "Error!" << endl;
			return;
		}
		char c;
		while((c=cin.get())==' ')
			;
		cin.putback(c);
		char buf[2001];
		cin.getline(buf,2000);
		string s(buf);
		string r = data[i-1].substr(0,j-1) + s + data[i-1].substr(j-1);
		data[i-1] = r;
	}

	void del(int i, int j)
	{
		if(i < 1 || i > j || j > length)
		{
			cout << "Error!" << endl;
			return;
		}
		for(int k = i; k < i+length-j; k++)
			data[k-1] = data[k+j-i];
		length -= j-i+1;
	}

	void print()
	{
		for(int i = 0; i < length; i++)
		{
			cout << data[i] << endl;
		}
	}

	void printline(int i, int j)
	{
		if(i < 1 || j < i || j > length)
		{
			cout << "Error!" << endl;
			return;
		}
		for(int k = i; k <= j; k++)
			cout << data[k-1] << endl;
	}

	string* data;
	int capacity;
	int length;
};

int main()
{
	Vector v;
	while(v.appendToEOL())
		;
	string cmd;
	while(true)
	{
		cin >> cmd;
		int i,j;
		if(cmd == "list")
		{
			cin >> i >> j;
			v.printline(i,j);
		}
		else if(cmd == "ins")
		{
			cin >> i >> j;
			v.insertToEOL(i,j);
		}
		else if(cmd == "del")
		{
			cin >> i >> j;
			v.del(i,j);
		}
		else if(cmd == "quit")
		{
			v.print();
			break;
		}
	}
	return 0;
}
