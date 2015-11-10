#include <cstdio>

using namespace std;

int main()
{
	char c;
	int count = 0;
	int sum = 0;
	while(c=getchar())
	{
		count++;
		if(c>='A' && c<='Z') sum+=count*(c-'A'+1);
		else if(c>='a' && c<='z') sum+=count*(c-'a'+27);
		else if(c==' '){}
		else break;
	}
	printf("%d\n",sum);
	return 0;
}
