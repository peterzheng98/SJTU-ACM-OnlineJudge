#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int A = 0;
const int B = 1;
const int C = 2;
const int S = 3;

bool DFS(char *buf, int d, int p, int s)
{
	char c = buf[p];
	if(s==A)
	{
		if(d==0) return false;
		if(c=='{')
		{
			bool t = DFS(buf,d+1,p+1,A);
			if(t) return true;
			return DFS(buf,d,p+1,B);
		}
		else if(c=='}')
		{
			bool t = DFS(buf,d,p+1,B);
			if(t) return true;
			return DFS(buf,d-1,p+1,B);
		}
		else if(c==',') return DFS(buf,d,p+1,B);
		else if(c=='\0') return false;
		else return DFS(buf,d,p+1,A);
	}
	else if(s==B)
	{
		if(d==0) return c=='\0';
		if(c=='{') return false;
		else if(c=='}') return DFS(buf,d-1,p+1,B);
		else if(c==',') return DFS(buf,d,p+1,C);
		else if(c=='\0') return d==0;
		else return DFS(buf,d,p+1,s);
	}
	else if(s==C)
	{
		if(d==0) return false;
		if(c=='{')
		{
			bool t = DFS(buf,d+1,p+1,A);
			if(t) return true;
			return DFS(buf,d,p+1,B);
		}
		else if(c=='}') return DFS(buf,d,p+1,B);
		else if(c==',') return DFS(buf,d,p+1,B);
		else if(c=='\0') return false;
		else return DFS(buf,d,p+1,s);
	}
	else if(s==S)
	{
		if(c=='{') return DFS(buf,d+1,p+1,A);
		else if(c=='}') return false;
		else if(c==',') return false;
		else if(c=='\0') return false;
		else return DFS(buf,d,p+1,s);
	}
	return false;
}

int main()
{
	int T;
	scanf("%d",&T);
	for(register int i = 0; i < T; i++)
	{
		char buf[300];
		scanf("%s",buf);
		if(DFS(buf,0,0,S)) printf("Word #%d: Set\n",i+1);
		else printf("Word #%d: No Set\n",i+1);
	}
	return 0;
}
