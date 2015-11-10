#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cstdlib>
using namespace std;
////////////////////////////////////////
//Judge whether a charactor is a digit//
////////////////////////////////////////
bool isDigit(char ch)
{
	return ch>='0' && ch<='9';
}
///////////////////////////////////////////////////
//Judge whether one string is prefix of the other//
///////////////////////////////////////////////////
bool isPrefix(std::string larger,std::string shorter)
{
	if( larger.size()>=shorter.size() && (!shorter.empty()) )
		if( larger.substr(0,shorter.size())==shorter )
			return true;
	return false;
}





///////////////////////////////////////////////////////////////////////////////////////////////////////
//Read the first double or operator of a string////////////////////////////////////////////////////////
//If the string has been read through, return 1; //////////////////////////////////////////////////////
//else if read a double, return 2; else if read an operator return 3; /////////////////////////////////
//else if the string is not proper, return -1//////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
int read_string(const std::string& str,//The string to be read
				int& value,std::string& oper,unsigned int& pos,//To return the value or the operator, 
				//at least one of them is empty, Place the position to the new place
 				const std::vector<std::string>&opers)//The collection of all operators
{
	if(pos>=str.size())//If the position is after the end of the string,
		return 1;//The string has been read through, return 1
	else if(isDigit(str[pos]))//The first char is a digit, then the return value is a double
	{
		value=0;
		do
			value=value*10+str[pos]-'0';//Transform the char into number, and add it to the double
		while((++pos)<str.size() && isDigit(str[pos]));//Read until the current char is not a digit or the string is end
		if( pos>=str.size() )return 2;//If the string has been read through, return 2
		
		if( str[pos]=='.' )//If the current char is a point, then judge whether the next char is a digit
			if( (++pos)<str.size() && isDigit(str[pos]))//The next is a digit, the same as the previous(read until end of digits)
			{
				int tmp=0;
				int count=0;
				do
				{
					tmp=tmp*10+str[pos]-'0';//Transform the char into number, and add it to tmp
					++count;//Count the number of the 
				}while((++pos)<str.size() && isDigit(str[pos]));//Read until the current char is not a digit or the string is end
				value+=(tmp/pow(10,count));//Combine the two parts
				return 2;//Return 2
			}
			else
				return -1;//The string is end with a point '.', or a point is followed by a nondigit, it's not a proper string, return -1
		else//The string is not end, and the next is not a point or a digit
			return 2;//Return 2(read a double successfully)
	}
	//The first char is not a digit
	for(int i=0; i<opers.size(); ++i)
		if(isPrefix(str.substr(pos),opers[i]))//Search through the collection of operators to find if there is one that is the prefix of the string									
		{
			oper=opers[i];
			pos+=oper.size();
			return 3;
		}
	return -1;//Failure to find a proper operator means the string is not proper;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//Return a vector given an array//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
template<typename eleType>
std::vector<eleType>vec_array( eleType* array, eleType endMark, int max=1000 )
{
	std::vector<eleType>nvec;
	for( int i=0; i<max && *(array+i)!=endMark; ++i )
		nvec.push_back(*(array+i));
	return nvec;
}
//////////////////////////////////////////////////////
//Transform all the "-" as unary operators into "_"///
//////////////////////////////////////////////////////
std::string trans(std::string str)
{
	std::string newstr;
	for(int i=0;i<str.size();++i)
		if(str[i]=='-' && ( i==0 || (!isDigit(str[i-1]) && str[i-1]!=')')))//This '-' should be unary
			newstr+='_';
		else
			newstr+=str[i];
	return newstr;
}

////////////////////////////////////////////////////////////
//Return the number of parameters the operator should take//
////////////////////////////////////////////////////////////
bool is_binary(const std::string oper)
{
	return (oper=="+" || oper=="-" || oper=="*" || oper=="/" || oper=="^");
}
///////////////////////////////////////////////////////////////////////////////
//Rewrite the function read_string, it just returns a string///////////////////
//If the string has been read through, return 1;///////////////////////////////
//else if read a double, return 2(but the double is passed as a string); //////
//else if read an operator return 3; //////////////////////////////////////////
//else if the string is not proper, return -1//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int read_string(const std::string& str,//The string to be read
				std::string& value,//To return the value
				unsigned int& pos,//Place the position to the new place
				const std::vector<std::string>&opers//The set of all operators
 				)
{
	if(pos>=str.size())//If the position is after the end of the string,
		return 1;//The string has been read through, return 1

	//The first char is a digit, 
	//then the return value is a double(return as string)
	else if(isDigit(str[pos]))
	{
		value="";//Empty the return value
		do
			value+=str[pos];//Add the current charactor(digit) to value
		while((++pos)<str.size() && isDigit(str[pos]));
		//Read until the current char is not a digit or the string is end
		
		//If the string has been read through, return 2
		if( pos>=str.size() )return 2;
		
		//If the current char is a point, 
		//then judge whether the next char is a digit
		if( str[pos]=='.' )
			if( (++pos)<str.size() && isDigit(str[pos]))
			{//The next is a digit, the same as the previous
			//(read until end of digits or end of string)
				value+='.';
				do
					value+=str[pos];//Add the current char(digit) to value
				while((++pos)<str.size() && isDigit(str[pos]));
				//Read until the current char is not a digit or the string end
				return 2;//Return 2
			}
			//The string is end with a point '.', 
			//or a point is followed by a nondigit, 
			//it's not a proper string, return -1
			else return -1;
				
				
		else//The string is not end, and the next is not a point or a digit
			return 2;//Return 2(read a double successfully)
	}
	//The first char is not a digit
	for(int i=0; i<opers.size(); ++i)
		if(isPrefix(str.substr(pos),opers[i]))
		{//Search through the collection of operators 
		//to find if there is one that is the prefix of the string									
			value=opers[i];
			pos+=value.size();
			return 3;
		}
		
	return -1;
	//Failure to find a proper operator means the string is not proper;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////////Another ReadString function: Read a string and put all the///////////
//////////substrings into a vector/////////////////////////////////////////////
//////////Successful reading returns 1, or -1//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int read_string(const std::string& str, 
				std::vector<std::string>& vct,
				const std::vector<std::string>&opers)
{
	unsigned int pos=0;//Locate the Postion to read next
	int state;//The integer to keep the return value of read_string function
	std::string read;//The string to keep the returned string
	vct.clear();//Clear the vector
	while( (state=read_string(str,read,pos,opers))!=1 && state!=-1 )
		vct.push_back(read);//Push the returned string into vector
	return state;//If string is read through successfully, return 1;
	//Any error happened, return -1;
}
///////////////////////////////////////////////////////////////////////////////
//Substitude function//////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
std::string subs_str(const std::string str, 
					std::string orig, std::string nchars)
{
	std::string nstr;
	std::string::size_type start=0,next=0;
	while((next=str.find(orig,start))!=std::string::npos)
	//Find the target successfully(the first from start)
	{
		nstr=nstr+str.substr(start,next-start)+nchars;
		start=next+orig.size();
	}
	nstr=nstr+str.substr(start);
	return nstr;
}
////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Return the rank of an operator: the larger the integer, the lower the rank///
///////////////////////////////////////////////////////////////////////////////
int rank( 	std::string oper,
			const std::vector<std::string>& opers,
			std::string RankDown)
{
	//////////////////////variables////////////////////////////////////////////
	int r=0;//The return value
	/////////////////////Main//////////////////////////////////////////////////
	for( int i=0; i<opers.size(); ++i )
	{
		if( opers[i]==oper ) return r;//Oper found, return the rank
		if( opers[i]==RankDown ) ++r;//RankDown mark, add the rank
	}
	/////////////////////return////////////////////////////////////////////////
	//Fail to find //
	return -1;
}

int left_assoc(std::string oper1, std::string oper2)
{
	if(oper1 == "^" && oper2 == "^") return false;
	return true;
}
///////////////////////////////////////////////////////////////////////////////
//Find the corresponding right parenthesis of a left parenthesis///////////////
//If at the given position is not a parenthesis, return the corresponding//////
//right parenthesis of the right-nearest left parenthesis//////////////////////
///////////////////////////////////////////////////////////////////////////////
int right_pth( 	const std::vector<std::string>&vct,
			  	int start, int end )//The searching sphere
{
	//////////////////variables////////////////////////////////////////////////
	int r, counter=0;//Return value, parenthesis counter
	bool startcount=false;//Start count the parenthesis
	/////////////////Debug/////////////////////////////////////////////////////
	if( start<0 ) return -1;
	/////////////////Main//////////////////////////////////////////////////////
	for( r=start; r<=end && r<vct.size(); ++r )//Go through
	{
		if( vct[r]=="(" ) counter++;//Left parenthesis met, counter++
		else if( vct[r]==")" ) counter--;//Right parenthesis met, counter--
		if( vct[r]=="(" || vct[r]==")" ) startcount=true;//Start count
		//If left and right equal, return
		if( counter==0 && startcount ) return r;
		if( counter<0 ) return -2;//First meet right parenthesis, return 1
	}
	/////////////////Return////////////////////////////////////////////////////
	//Too many left parenthesises, return -1///////////////////////////////////
	//No parenthesis at all, return 1//////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	return startcount?-1:-2;
}
///////////////////////////////////////////////////////////////////////////////
//Find the corresponding left parenthesis of a right parenthesis///////////////
//If at the given position is not a parenthesis, return the corresponding//////
//left parenthesis of the right-nearest right parenthesis//////////////////////
///////////////////////////////////////////////////////////////////////////////
int left_pth( 	const std::vector<std::string>&vct,
			  	int start, int end )//The searching sphere
{
	//////////////////variables////////////////////////////////////////////////
	int l, counter=0;//Return value, parenthesis counter
	bool startcount=false;//Start count the parenthesis
	/////////////////Debug/////////////////////////////////////////////////////
	if( end>=vct.size() ) return -1;
	/////////////////Main//////////////////////////////////////////////////////
	for( l=end; l>=start && l>=0; --l )//Go through
	{
		if( vct[l]==")" ) counter++;//Right parenthesis met, counter++
		else if( vct[l]=="(" ) counter--;//Left parenthesis met, counter--
		if( vct[l]==")" || vct[l]=="(" ) startcount=true;//Start count
		//If left and right equal, return
		if( counter==0 && startcount ) return l;
		if( counter<0 ) return -2;//First meet left parenthesis, return -2
	}
	/////////////////Return////////////////////////////////////////////////////
	//Too many left parenthesises, return -1///////////////////////////////////
	//No parenthesis at all, return 1//////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	return startcount?-1:-2;
}


///////////////////////////////////////////////////////////////////////////////
//Search for the operator that will be last operated in calculation////////////
///////////////////////////////////////////////////////////////////////////////
int last_operator( 	const std::vector<std::string>&vct,
					const std::vector<std::string>&opers,
					const std::string& RankDown,
					int start, int end )
{
	//////////////////////variables////////////////////////////////////////////
	int last=-1, min_rank=0;//The return value; the minimum rank
	//////////////////////Debug////////////////////////////////////////////////
	if( start<0 || end>=vct.size() ) return -1;
	/////////////////////Main//////////////////////////////////////////////////
	for( int i=start; i<=end; ++i )
	{
		if( find(opers.begin(),opers.end(),vct[i])!=opers.end()
			&& vct[i]!="(" && vct[i]!=")" )
		{//This is an operator
			int r=rank(vct[i],opers,RankDown);//Get the rank of the operator
			if(  last==-1 || (r>=min_rank && is_binary(vct[i])) )
			{//If present operator has lower or equal rank,
			//change the present lowest rank operator to new
			//Except that it is a unary operator, but if this is the first
			//operator, a unary operator also fits
				last=i;
				min_rank=r;
			}
		}
		else
		{//This is not an operator
			if( vct[i]=="(" )//If the present is left parenthesis
			{//Just jump to the corresponding right one
				i=right_pth(vct,i,end);
				if( i==-1 ) return -1;//If there is something wrong, return -1
			}
		}
	}
	/////////////////////return////////////////////////////////////////////////
	return last;//Return the value; if there is no operator found
				//the return value is -1
}
///////////////////////////////////////////////////////////////////////////////
//Operate an operator//////////////////////////////////////////////////////////
//Binary operator//////////////////////////////////////////////////////////////
int operate( 	std::string& outcome, const std::string& lvalue, 
				const std::string& oper, const std::string& rvalue )
{
	std::ostringstream os;
	std::istringstream lis(lvalue);
	std::istringstream ris(rvalue);
	int l,r;
	lis>>l;ris>>r;
	if(oper=="+") os<<l+r;
	else if(oper=="-") os<<l-r;
	else if(oper=="*") os<<l*r;
	else if(oper=="/") {if(r!=0) os<<l/r; else return -1;}
	else if(oper=="^") os<<pow(l,r);
	else return -1;//Operator unrecognized
	outcome=os.str();
	return 1;//Successfully
}
//Unary operator
int operate( 	std::string& outcome, const std::string& oper, 
				const std::string& value )
{
	std::ostringstream os;
	std::istringstream is(value);
	int v;
	is>>v;
	if( oper=="_" ) os<<-v;
	else if( oper=="Cos" ) os<<cos(v);
	else if( oper=="Sin" ) os<<sin(v);
	else if( oper=="Tan" ) os<<tan(v);
	else if( oper=="ArcSin" ) os<<asin(v);
	else if( oper=="ArcCos" ) os<<acos(v);
	else if( oper=="ArcTan" ) os<<atan(v);
	else if( oper=="Sinh" ) os<<sinh(v);
	else if( oper=="Cosh" ) os<<cosh(v);
	else if( oper=="Tanh" ) os<<tanh(v);
	else if( oper=="Abs" ) os<<fabs(v);
	else if( oper=="Sqrt" ) {if(v>=0) os<<sqrt(v); else return -1;}
	else return -1;//Operator unrecognized
	outcome=os.str();
	return 1;//Successfully
}



///////////////////////////////////////////////////////////////////////////////
//////////////////The main function: evaluate//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//Evaluate vector first////////////////////////////////////////////////////////
int evaluate_vector(	std::string& outcome,
					 	const std::vector<std::string>&vct,
						const std::vector<std::string>&opers,
						const std::string& RkDn,
						int start, int end )
{
	//for( int i=start; i<=end; i++ )
	//	std::cout<<vct[i];
	//std::cout<<std::endl;
	if( start>end ) return -1;
	if( start==end ) outcome=vct[start];//If start==end just return it
	else
	{
		
		int l=last_operator(vct,opers,RkDn,start,end);//Find last operator
		if( l==-1 )
			if( vct[start]=="(" && vct[end]==")" && start<end-1 )
				//The operation is parenthetical
				//invoke the function recursively
				return evaluate_vector(outcome,vct,opers,RkDn,start+1,end-1);
			else
				return -1;//If the operation is not parenthetical	
		 //and there is no operator found, error, return -1
		 
		if( is_binary(vct[l]) )//If this is a binary operator
		{
			std::string lvalue,rvalue;
			if(evaluate_vector(lvalue,vct,opers,RkDn,start,l-1)==-1) return -1;
			if(evaluate_vector(rvalue,vct,opers,RkDn,l+1,end)==-1) return -1;
			return operate(outcome,lvalue,vct[l],rvalue);
		}
		else//this is a unary operator
		{
			std::string value;
			if( evaluate_vector(value,vct,opers,RkDn,l+1,end)==-1 ) return -1;
			return operate(outcome,vct[l],value);
		}
	}
	return 1;
}
///////////////////////////////////////////////////////////////////////////////
//Final function: evaluate string//////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
std::string evaluate(std::string equation)
{
	std::vector<std::string>vct;//The equation transformed from the string
	std::vector<std::string>opers;//To store the operators
	std::string RankDown("RankDown");//The rank down mark
	std::string endmark("#");//End mark
	std::string oper_array[]={"(","_","Sinh","Cosh","Tanh","Abs","Cos","Sin","Tan","Arcsin","Arccos","Arctan",
						"Sqrt","RankDown","^","RankDown","*","/","RankDown",
						"+","-","RankDown",")",endmark};//Operators array
	opers=vec_array(oper_array,endmark);//Put operators into vector
	std::string outcome;//
	int state;//State, judge whether succeed
	read_string(trans(equation),vct,opers);//Read the string into vector
	//Evaluate
	state=evaluate_vector(outcome,vct,opers,RankDown,0,vct.size()-1);
	if( state==-1 ) outcome="Error";
	return outcome;
}

int main()
{
	char buf[200];
	char ss[200];
	cin.getline(buf,200);
	int c=0;
	for(int i = 0; buf[i]!='\0'; i++)
		if(buf[i]!=' ') ss[c++] = buf[i];
	string s(ss);
	cout << evaluate(s) << endl;
	return 0;
}
