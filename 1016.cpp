#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int getDigit(const string &s1, int index)
{
	if(index < 0) return -1;
	if(index >= s1.length()) return 0;
	return s1.at(s1.size()-index-1)-'0';
}

string getString(int s)
{
	ostringstream os;
	os << s;
	return os.str();
}

string uadd(const string &s1, const string &s2)
{
	string res = "";	
	string tmp = "";
	int p = 0, c = 0;
	while(true)
	{
		int d1 = getDigit(s1,p), d2 = getDigit(s2,p);
		int d = d1+d2+c;
		if(d==0 && p >= s1.size() && p >= s2.size()) break;
		c = d/10;
		d %= 10;
		tmp = getString(d)+tmp;
		if(d > 0) res = tmp;
		p++;
	}
	return res;
}

string compliment(const string &s1)
{
	string res = "";
	for(int i = 0; i < s1.size(); i++)
		res += 9-(s1.at(i)-'0')+'0';
	return uadd(res,"1");
}

bool ulessthan(const string &s1, const string &s2)
{
	if(s1.size() < s2.size()) return true;
	if(s1.size() > s2.size()) return false;
	for(int i = 0; i < s1.size(); i++)
	{
		if(s1.at(i) < s2.at(i)) return true;
		if(s1.at(i) > s2.at(i)) return false;
	}
	return false;
}

string minus10power(const string &s, unsigned int p)
{
	int c = 0;
	string res = "";
	for(int i = 0; i<s.size() || i<=p; i++)
	{
		if(i == p) c=-1;
		int d = getDigit(s,i) + c;
		if(d < 0)
		{
			d += 10;
			c = -1;
		}
		else c=0;
		res = getString(d)+res;
	}
	return uadd(res,"0");
}

string uminus(const string &s1, const string &s2)
{
	if(ulessthan(s1,s2)) return "-"+uminus(s2,s1);
	if(s1 == s2) return "0";
	string res = uadd(s1,compliment(s2));
	return minus10power(res,s2.size());
}

string neg(const string &s)
{
	if(s.at(0) == '-') return s.substr(1);
	return "-"+s;
}

bool isnegative(const string &s)
{
	return s.at(0) == '-';
}

string add(const string &s1, const string &s2)
{
	if(isnegative(s1) && isnegative(s2))
		return neg(uadd(neg(s1),neg(s2)));
	if(isnegative(s1)) return uminus(s2,neg(s1));
	if(isnegative(s2)) return uminus(s1,neg(s2));
	return uadd(s1,s2);
}

string minus(const string &s1, const string &s2)
{
	return add(s1,neg(s2));
}

string udivide(const string &s1, const string &s2)
{
	string res = "0";
	string adder = s2;
	string suber = s1;
	int power = 0;
	string powerof10 = "1";
	while(true)
	{
		if(ulessthan(suber,adder))
		{
			if(power > 0)
			{
				power = 0;
				powerof10 = "1";
				adder = s2;
				if(ulessthan(suber,adder)) return res;
			}
			else return res;
		}
		string next = adder+"0";
		while(!ulessthan(suber,next))
		{
			adder = next;
			power++;
			powerof10 += "0";
			next = adder+"0";
		}
		while(!ulessthan(suber,adder))
		{
			suber = uminus(suber,adder);
			res = uadd(res,powerof10);
		}
	}
}

int main()
{
	string a,b;
	cin >> a >> b;
	string c = udivide(a,b);
	cout << c << endl;
	return 0;
}
