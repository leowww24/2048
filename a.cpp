/*************************************************************************
  > File Name: a.cpp
  > Created Time: 2014年05月04日 星期日 22时10分06秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<stack>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<cmath>
using namespace std;

int G[6][6];
int Score;
vector<int*> emptyG;

void init();
void updateScore();
void yield();
void waitOperate();

void moveGrids(char dir);
int getValue(char dir,int m,int n);
void changeValue(char dir,int (*G)[6],int m,int n,int value);

void printResult();
bool checkDeath();

void init()
{
	//set border
	for(int i=0;i!=6;++i)
	{
		G[0][i]=-1;
		G[i][0]=-1;
		G[5][i]=-1;
		G[i][5]=-1;
	}

	emptyG.clear();
	//inital grid and emptyGrid
	for(int i=1;i!=5;++i)
	{
		for(int j=1;j!=5;++j)
		{
			G[i][j]=0;
			emptyG.push_back(&G[i][j]);
		}
	}
	yield();
}

//creat 2 in empty grid randomly，update emptyG vector
void yield()
{
	int offset=emptyG.size()-1;	
	srand((unsigned)time(NULL));
	int randomOffset=rand()%offset;
	vector<int*>::iterator iter=emptyG.begin()+randomOffset;
	**iter=2;
	emptyG.erase(iter);
}

//update Score
void updateScore()
{
	for(int i=1;i!=5;++i)
	{
		for(int j=1;j!=5;++j)
		{
			if(G[i][j]!=0&&G[i][j]!=2)
			{
				int temp=G[i][j];
				Score+=temp*(log(temp)/log(2)-1);
			}
		}
	}
}

//print current grids
void printResult()
{
	cout<<"--------2048 C++ DEVISION HAVE FUN!!!-------\n"<<endl;
	cout<<"Current Score:"<<Score<<endl;
	cout<<"-------------------------"<<endl;
	for(int i=1;i!=5;++i)
	{
		for(int j=1;j!=5;++j)
		{
			if(j==1)
				cout<<"\t";
			if(G[i][j]!=0)
				cout<<G[i][j]<<"\t";
			else
				cout<<"[]"<<"\t";
			if(j==4)
				cout<<endl;
		}
		cout<<endl;
	}
	cout<<"-------------------------"<<endl;
	cout<<endl;
}


//
void waitOperate()
{
	cout<<"--Use u (up) d(down) l(left) r(right) to move the grids--"<<endl;
	cout<<"Move deriction:";
	char ch;
	while(cin>>ch)
	{
		if(ch=='u'||ch=='d'||ch=='l'||ch=='r')
		{
			moveGrids(ch);
			break;
		}
		else
		{
			fflush(stdin);
			cin.clear();
			cout<<"Unknow Deriction!"<<endl;
		}
	}
}

//belongs to moveGrids,help to handle the deriction
int getValue(char dir,int m,int n)
{
	if(dir=='l')
	{
		int temp=m;
		m=n;
		n=temp;
	}
	if(dir=='d')
	{
		m=5-m;
	}
	if(dir=='r')
	{
		n=5-n;
	}
	return G[m][n];
}
void changeValue(char dir,int (*G)[6],int m,int n,int value)
{
	if(dir=='l')
	{
		int temp=m;
		m=n;
		n=temp;
	}
	if(dir=='d')
	{
		m=5-m;
	}
	if(dir=='r')
	{
		n=5-n;
	}
	G[m][n]=value;	
}

//move the grids,dir is in(u d ,s r)
void moveGrids(char dir)
{
	for(int j=1;j<=4;++j)
	{
		//sum operation,put the result into stk
		stack<int> stk;
		for(int i=1;i<=4;++i)
		{

			//int cur=G[i][j];
			int cur=getValue(dir,i,j);
			while(!stk.empty())
			{
				int before=stk.top();
				if(before!=cur)
				{
					break;
				}
				else
				{
					stk.pop();
					cur*=2;
				}
			}
			if(cur!=0)
				stk.push(cur);
		}
		//put the result into the current line
		int sz=stk.size();
		for(int i=sz+1;i<=4;++i)
		{
			//G[i][j]=0;
			changeValue(dir,G,i,j,0);
		}
		while(sz)
		{
			//G[sz][j]=stk.top();
			changeValue(dir,G,sz,j,stk.top());
			stk.pop();
			--sz;
		}

	}
	//update emptyG vector
	emptyG.clear();
	for(int i=1;i!=5;++i)
	{
		for(int j=1;j!=5;++j)
		{
			if(G[i][j]==0)
				emptyG.push_back(&G[i][j]);
		}
	}
}

//
bool checkDeath()
{

}


int main()
{
	init();
	system("clear");
	printResult();
	while(true)
	{
		waitOperate();
		updateScore();
		yield();
		system("clear");
		printResult();
	}
}
