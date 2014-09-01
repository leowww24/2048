/*************************************************************************
  > File Name: try.cpp
  > Created Time: 2014年05月07日 星期三 17时20分47秒
 ************************************************************************/

#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<stack>
using namespace std;

string intToString(int i)
{
	string res;
	stack<char> stk;
	while(i!=0)
	{
		char cur=i%10;
		stk.push('0'+cur);
		i/=10;
	}
	while(!stk.empty())
	{
		char cur=stk.top();
		res+=cur;
		stk.pop();
	}
	return res;
}

int main()
{
	string name="leo";
	string score="1111";
	string myQuery="insert into tb_record(user,score) values('";
	myQuery+=name;
	myQuery+="',";
	myQuery+=score;
	myQuery+=")";
	cout<<myQuery<<endl;

	int a=234;
	
	cout<<"input your name:";
	getline(cin,name);
	cout<<name<<endl;

	char cc[23]="NULL";
	cout<<cc<<endl;
}

