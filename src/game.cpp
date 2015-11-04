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
bool full=false;	//boost up autoOperate speed
int moveTimes;
int actualMoveTimes;

void insertRecord(string name,int score);

void init();
void updateScore();
void yield();
void autoOperate(int cnt);

void moveGrids(char dir);
int getValue(char dir,int m,int n);
void changeValue(char dir,int (*G)[6],int m,int n,int value);

void printResult();
bool checkDeath();

void init()
{
	moveTimes=0;
	actualMoveTimes=-1;

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
	for(int i=1;i<5;++i)
	{
		for(int j=1;j<5;++j)
		{
			G[i][j]=0;
			emptyG.push_back(&G[i][j]);
		}
	}
	yield();
	printResult();
}

//creat 2 in empty grid randomly，update emptyG vector
void yield()
{
	if(emptyG.empty())
		cerr<<"Grids is full!Yield failed..."<<endl;

	int offset=emptyG.size()-1;	//caution offset=0 is special
	int randomOffset;
	if(offset==0)
		randomOffset=0;
	else
	{
		srand((unsigned)time(NULL));
		randomOffset=rand()%offset;
	}
	vector<int*>::iterator iter=emptyG.begin()+randomOffset;
	**iter=2;
	//emptyG.erase(iter);	//moveGrids will updte emptyG vector
	
	++actualMoveTimes;
}

//update Score
void updateScore()
{
	Score=0;
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
	updateScore();

	system("clear");

	cout<<"--------2048 C++ DEVISION HAVE FUN!!!-------\n"<<endl;
	cout<<"Current Score:"<<Score<<endl;
	cout<<"--------------------------------------------"<<endl;
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
	cout<<"--------------------------------------------"<<endl;
	cout<<endl;
}


//wait for operate
//before this emptyG.empty()=false should be promised
void waitOperate()
{
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
		int temp=m;
		m=n;
		n=temp;
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
		int temp=m;
		m=n;
		n=temp;
		n=5-n;
	}
	G[m][n]=value;	
}

//move the grids,dir is in(u d ,s r)
//caution:when checkDeath=false && emptyG.empty()=true,there is a direction we can't move,only the other 3 choices will make sense
void moveGrids(char dir)
{
	moveTimes++;
	for(int j=1;j<5;++j)
	{
		//sum operation,put the result into stk
		stack<int> stk;
		for(int i=1;i<5;++i)
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
					cur=cur+before;
				}
			}
			if(cur!=0)
				stk.push(cur);
		}
		//put the result into the current line
		int sz=stk.size();
		for(int i=sz+1;i<5;++i)
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
	for(int i=1;i<5;++i)
	{
		for(int j=1;j<5;++j)
		{
			if(G[i][j]==0)
				emptyG.push_back(&G[i][j]);
		}
	}
	//boost autoOperation
	if(emptyG.empty())
		full=true;
	else
		full=false;
}

//check the Grids to return dead or not
bool checkDeath()
{
	bool res=true;
	for(int j=1;j<5;++j)
	{
		if(!res)
			break;
		for(int i=1;i<5;++i)
		{
			if(G[i][j]==0)
			{
				res=false;
				break;
			}
			int t=G[i][j];
			if(t==G[i+1][j]||t==G[i-1][j]||t==G[i][j+1]||t==G[i][j-1])
			{
				res=false;
				break;
			}
		}
	}
	return res;
}

//auto operate cnt times
void autoOperate(int cnt)
{
	cout<<"Auto operating "<<cnt<<" times,please wait...\n"<<endl;
	char opt[4]={'u','d','l','r'};
	while(cnt--)
	{
		if(full)
		{
			if(checkDeath())
				break;
		}
		srand((unsigned)time(NULL));
		int randomIx=rand()%4;
		char dir=opt[randomIx];
		moveGrids(dir);
		if(full)
		{
			++cnt;
			continue;
		}
		yield();
		printResult();
	}
	printResult();
}

int main()
{
	init();
	bool quit=false;	//use to quit the program
	while(!checkDeath()&&!quit)
	{
		cout<<"----Input u (up) d(down) l(left) r(right) to move the Grids----"<<endl;
		cout<<"--Input n(number) to let the Grids move n times automaticlly --"<<endl;
		cout<<"-----Input q to quit the game,a(again) to restart the game-----"<<endl;
		cout<<"Input>>";
		char ch;
		while(cin>>ch)
		{
			if(ch=='u'||ch=='d'||ch=='l'||ch=='r')
			{
				moveGrids(ch);
				if(emptyG.empty())
					continue;
				yield();
				printResult();
				break;
			}
			else if(isdigit(ch))
			{
				int cnt=0;
				cin.putback(ch);
				cin>>cnt;
				autoOperate(cnt);
				break;
			}
			else if(ch=='q')
			{
				quit=true;
				break;
			}
			else if(ch=='a')
			{
				init();
				break;
			}
			else
			{
				//fflush(stdin);zo	//vc6.0	 not transplantable
				char t;
				while((t=getchar())!='\n')
					;
				cin.clear();
				cout<<"Undefined Input!"<<endl;
				cout<<"Input>>";
			}
		}
	}
	if(quit)
		cout<<"------------------BYE BYE-------------------\n"<<endl;
	else
		cout<<"---------GAME OVER!  STUPID MACHINE!--------\n"<<endl;
	cout<<"-------Attempted To Move "<<moveTimes<<" Times.-------\n"<<endl;
	cout<<"---Actual Moved "<<actualMoveTimes<<" Times. Final Score:"<<Score<<".---\n"<<endl;
	
	string name;
	string cleanStdin;	//Caution:clean the stdin first,otherwise getline will read '\n' into name
	getline(cin,cleanStdin);
	cout<<"\nInput your name:";
	getline(cin,name);
	//insertRecord(name,Score);
}
