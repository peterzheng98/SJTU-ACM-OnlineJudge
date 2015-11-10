#include <iostream>
 
using namespace std;
 
int main()
{
while(true)
{
int a,b;
cin >> a >> b;
cout << a+b << endl;
if(cin.eof()) break;
}
return 0;
}
