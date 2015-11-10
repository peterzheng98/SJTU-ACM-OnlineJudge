#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int E = 1;
const int O = 2;
const int C = 4;
const int S = 8;

int main()
{
	int T;
	scanf("%d",&T);
	for(register int i = 0; i < T; i++)
	{
		char buf[300];
		int flag[300];
		int stack[300];
		int d = 0;
		scanf("%s",buf);
		int l=strlen(buf);
		int p = 0;
		flag[0] = O;
		bool err=false;
		while(p<=l)
		{
			char c=buf[p];
			int f=flag[p];
			err = false;
			if(c == '{')
			{
				if(f&O)
				{
					stack[p]=O;
					flag[p+1]=E|O|C;
					d++;
				}
				else if(f&E)
				{
					stack[p]=E;
					flag[p+1]=C|S;
				}
				else
				{
					stack[p]=0;
					err = true;
				}
			}
			else if(c == '}')
			{
				if(f&C)
				{
					stack[p]=C;
					d--;
					if(d>0) flag[p+1]=C|S;
					else if(d==0)flag[p+1]=0;
					else err = true;
				}
				else if(f&E)
				{
					stack[p]=E;
					flag[p+1]=C|S;
				}
				else
				{
					stack[p]=0;
					err = true;
				}
			}
			else if(c == ',')
			{
				if(f&S)
				{
					stack[p]=S;
					flag[p+1]=E|O;
				}
				else if(f&E)
				{
					stack[p]=E;
					flag[p+1]=C|S;
				}
				else
				{
					stack[p]=0;
					err = true;
				}
			}
			else if(c=='\0')
			{
				stack[p]=0;
				if(d>0 || stack[p-1]!=C)
				{
					err = true;
					if(d==0) fprintf(stderr,"%s\n",buf);
				}
			}

			if(err)
			{
				if(stack[p] == O) d--;
				if(stack[p] == C) d++;
				p--;
				if(p<0) break;
				flag[p]&=(~stack[p]);
				if(stack[p] == O) d--;
				if(stack[p] == C) d++;
			}
			else p++;
		}
		#if 0
		for(int k=0;k<l;k++)
		{
			if(stack[k]==E) printf("*");
			if(stack[k]==O) printf("{");
			if(stack[k]==C) printf("}");
			if(stack[k]==S) printf(",");
		}
		printf("\n%s\n%d %d\n",buf,p,l);
		#endif
		if(d==0 && !err /*&& p==l+1 && stack[p-2]==C*/) printf("Word #%d: Set\n",i+1);
		else printf("Word #%d: No Set\n",i+1);
		/*
		if(d==0 && !err && (p!=l+1 || stack[p-2]!=C))
		{
			printf("%s\n%d %d %d\n",buf,p,l,stack[p-2]);
		}
		*/
	}
	return 0;
}
