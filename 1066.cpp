#include <cstdio>

using namespace std;

char name[2001];
int pr[26];
int M,N;

char get(int index)
{
	if(index < 0 || index >= M) return '\0';
	return name[index];
}

int diff(int l, int r, int ll, int rr)
{
}

int main()
{
	scanf("%d%d",&N,&M);
	scanf("%s",name);
	for(int i = 0; i < N; i++)
	{
		char ch[2],a,b;
		scanf("%s%d%d",ch,&a,&b);
		pr[ch[0]-'a'] = (a>b?b:a);
	}
	return 0;
}
