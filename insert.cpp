/*************************************************************************
  > File Name: mysql_test.cpp
  > Created Time: 2014年05月06日 星期二 20时35分16秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<string.h>
#include<stack>
#include<mysql.h>
using namespace std;

//work for insert values,change int into string
string intToString(int i)
{
	if(i==0)
		return "0";
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

void insertRecord(string name,int score)
{
	MYSQL mysql;
	mysql_init(&mysql);
	if(NULL==mysql_real_connect(&mysql,"localhost","leo","123","db_2048",0,NULL,0))
		cout<<"Connection has been estabilashed."<<endl;


	string myQuery;
	if(name=="")
	{
		myQuery="insert into tb_record(score) values(";
	}	
	else
	{
		myQuery="insert into tb_record(user,score) values('";
		myQuery+=name;
		myQuery+="',";
	}
	myQuery+=intToString(score);
	myQuery+=")";
	if(mysql_real_query(&mysql,myQuery.c_str(),strlen(myQuery.c_str())))
	{
		cout<<"Insert error!"<<endl;
		cout<<mysql_error(&mysql)<<endl;
	}

}

