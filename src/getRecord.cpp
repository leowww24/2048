/*************************************************************************
    > File Name: mysql_test.cpp
    > Created Time: 2014年05月06日 星期二 20时35分16秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<mysql.h>
using namespace std;

int main()
{
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_FIELD *field;
	MYSQL_ROW row;

	mysql_init(&mysql);
	mysql_real_connect(&mysql,"localhost","leo","123","db_2048",0,NULL,0);
	mysql_query(&mysql,"select *from tb_record order by score desc");
	result=mysql_use_result(&mysql);
	
	cout<<"\n\t\t---------------GAME RECORD----------------"<<endl;;
	cout<<"  -------------------------------------------------------------------"<<endl;
	string sep="\t|\t";
	int attribute_cnt=1;
	cout<<"  ";
	while((field=mysql_fetch_field(result))!=NULL)
	{
		cout<<field->name;
		if(attribute_cnt<4)
			cout<<sep;
		++attribute_cnt;
	}
	cout<<endl;
	cout<<"  -------------------------------------------------------------------"<<endl;
	int rank=1;
	//bug! if there is a data named 'NULL' in db,there will apear a bug.
	while((row=mysql_fetch_row(result)))
	{
		cout<<"  "<<rank<<sep<<row[1]<<sep<<row[2]<<sep<<row[3]<<endl;
		cout<<"  -------------------------------------------------------------------"<<endl;
		++rank;
	}
	
	mysql_free_result(result);
	mysql_close(&mysql);
}

