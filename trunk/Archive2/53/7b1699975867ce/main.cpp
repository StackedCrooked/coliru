#include <stdio.h>
//#include <conio.h>
struct point
{
    int x,y;
}m;
char me,grid[50][50];
int r,c,ngrid[50][50];
void getinput();
int analysis();
int main()
{
	int i,j;
	getinput();
	if(analysis()==-1)
	{
		printf("dead");
		return 0;
	}
	for(i=0;i<r+1;i++)
	{
		for(j=0;j<c+1;j++)
			printf("%d\t",ngrid[i][j]);
		printf("\n");
	}
	//getch();
	return 0;
}
void getinput()
{
	int i;
	scanf("%c",&me);
	scanf("%d%d",&r,&c);
	for(i=0;i<r;i++)
		scanf("%s",grid[i]);
}
int analysis()
{
	char opp,c;
	int i,j,flag=0;
	switch(me)
	{
		case 'A': opp='B'; break;
		case 'B': opp='A'; break;
	}
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			c=grid[i][j];
			if(c=='#'||c=='Y'||c=='X'||c==opp)
				ngrid[i+1][j+1]=-1;
			else if(c=='*')
				ngrid[i+1][j+1]=1000;
			else if(c=='.')
				ngrid[i+1][j+1]=9999;
			else if(c==me)
			{
				ngrid[i+1][j+1]=0;
				flag=1;
				m.x=i+1;
				m.y=j+1;
			}
		}
	if(flag==0)
		return -1;
	for(j=1;j<=c;j++)
	{
		ngrid[0][j]=-1;
		ngrid[r+1][j]=-1;
	}
	for(i=1;i<=r;i++)
	{
		ngrid[i][0]=-1;
		ngrid[i][c+1]=-1;
	}
	return 0;
}