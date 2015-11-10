#include <cstdio>
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
	int p = 0, c = 0;
	while(true)
	{
		int d1 = getDigit(s1,p), d2 = getDigit(s2,p);
		int d = d1+d2+c;
		if(d==0 && p >= s1.size() && p >= s2.size()) break;
		c = d/10;
		d %= 10;
		res = getString(d)+res;
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

int main()
{
	int n;
	scanf("%d",&n);
	string d[10003];
	string e[10003];
	d[0] = "0";
	d[1] = "0";
	d[2] = "1";
	d[3] = "0";
	d[4] = "0";
	for(int i = 1; i < n; i++)
	{
		for(int j = 1; j <= i+2; j++)
			e[j] = uadd(d[j-1],d[j+1]);
		for(int j = 1; j <= i+2; j++)
			d[j] = e[j];
		d[i+4] = "0";
	}
	string sum = "0";
	for(int i = 1; i <= n+1; i++)
		sum = uadd(sum,d[i]);
	printf("%s\n",sum.c_str());
	return 0;
}
