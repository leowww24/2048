/*************************************************************************
  > File Name: a.cpp
  > Created Time: 2014年05月04日 星期日 22时10分06秒
 ************************************************************************/

#include<iostream>
#include<vector>
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
void operate();
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
	cout<<"Current Grig:"<<endl;
	cout<<"-------------------------"<<endl;
	for(int i=1;i!=5;++i)
	{
		for(int j=1;j!=5;++j)
		{
			if(j==1)
				cout<<"\t";
			cout<<G[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"-------------------------"<<endl;
	cout<<endl;
}


//
void operate()
{
	cout<<"--Use u (up) d(down) l(left) r(right) to move the grids--"<<endl;
	cout<<"Move deriction:";
	char ch;
	bool complete=true
	while(cin>>ch)
	{
		if(ch=='u'||ch=='d'||ch=='l'||ch=='r')
		{
			moveGrid(ch);
		}
		else
		{
			fflush(stdin);
			cin.clear();
			cout<<"Unknow input!"<<endl;
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
	printResult();
	operate();
	printResult();
	updateScore();
	cout<<Score<<endl;
}
