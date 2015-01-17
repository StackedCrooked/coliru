#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define SIZE 4







void getColor(int value, char *color, size_t length)
{
    int c = 40;
	if (value > 0)
	{
		while (value >>= 1)
		{
			c++;
		}
	}
	snprintf(color,length,"\033[0;41;%dm",c);
}

void drawBoard(int board[SIZE][SIZE]) {
	int x,y;
	char color[20], reset[] = "\033[0m";
	printf("\033[2J");
	
	for (x=0;x<SIZE;x++)
	{
		printf(" ______");
	}
	printf(" \n");
	
	for (y=0;y<SIZE;y++)
	{
		for (x=0;x<SIZE;x++)
		{
			getColor(board[x][y],color,20);
			printf("%s",color);
			printf("|      ");
			printf("%s",reset);
		}
		printf("|\n");
		
		for (x=0;x<SIZE;x++)
		{
			getColor(board[x][y],color,20);
			printf("%s",color);
			
			if (board[x][y]!=0)
			{
				char s[7];
				int t;
				int b = board[x][y];
				snprintf( s, 7, "%u", b );
				t = (int)(6-strlen(s));
				printf("|%*s%s%*s",t-t/2,"",s,t/2,"");
			}
			else
			{
				printf("|      ");
			}
			printf("%s",reset);
		}
		printf("|\n");
		
		for (x=0;x<SIZE;x++)
		{
			getColor(board[x][y],color,20);
			printf("%s",color);
			printf("|______");
			printf("%s",reset);
		}
		printf("|\n");
	}
	printf("\nPress arrow keys or 'q' to quit\n\n");
}

int findTarget(int array[SIZE],int x,int stop)
{
	int t;
	
	if (x==0)
	{
		return x;
	}
	for(t=x-1;t>=0;t--)
	{
		if (array[t]!=0)
		{
			if (array[t]!=array[x])
			{
				return t+1;
			}
			return t;
		}
		else {
			if (t==stop)
			{
				return t;
			}
		}
	}
	return x;
}

bool slideArray(int array[SIZE])
{
	bool success = false;
	int x,t,stop=0;

	for (x=0;x<SIZE;x++)
	{
		if (array[x]!=0)
		{
			t = findTarget(array,x,stop);
			
			if (t!=x)
			{
				if (array[t]!=0)
				{
					stop = t+1;
				}
				array[t]+=array[x];
				array[x]=0;
				success = true;
			}
		}
	}
	return success;
}

void rotateBoard(int board[SIZE][SIZE])
{
	int i,j,n=SIZE;
	int tmp;
	
	for (i=0; i<n/2; i++)
	{
		for (j=i; j<n-i-1; j++)
		{
			tmp = board[i][j];
			board[i][j] = board[j][n-i-1];
			board[j][n-i-1] = board[n-i-1][n-j-1];
			board[n-i-1][n-j-1] = board[n-j-1][i];
			board[n-j-1][i] = tmp;
		}
	}
}

bool moveUp(int board[SIZE][SIZE])
{
	bool success = false;
	int x;
	
	for (x=0;x<SIZE;x++)
	{
		success |= slideArray(board[x]);
	}
	return success;
}

bool moveLeft(int board[SIZE][SIZE])
{
	bool success;
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	return success;
}

bool moveDown(int board[SIZE][SIZE])
{
	bool success;
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	return success;
}

bool moveRight(int board[SIZE][SIZE])
{
	bool success;
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	return success;
}

bool findPairDown(int board[SIZE][SIZE])
{
	bool success = false;
	int x,y;
	
	for (x=0;x<SIZE;x++)
	{
		for (y=0;y<SIZE-1;y++)
		{
			if (board[x][y]==board[x][y+1])
			{
				return true;
			}
		}
	}
	return success;
}

int countEmpty(int board[SIZE][SIZE])
{
	int x,y;
	int count=0;
	
	for (x=0;x<SIZE;x++)
	{
		for (y=0;y<SIZE;y++)
		{
			if (board[x][y]==0)
			{
				count++;
			}
		}
	}
	return count;
}

bool gameEnded(int board[SIZE][SIZE])
{
	bool ended = true;
	
	if (countEmpty(board)>0)
	{
		return false;
	}
	if (findPairDown(board))
	{
		return false;
	}
	rotateBoard(board);
	
	if (findPairDown(board))
	{
		ended = false;
	}
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	return ended;
}

void addRandom(int board[SIZE][SIZE])
{
	static bool initialized = false;
	int x,y;
	int r,len=0;
	int n,list[SIZE*SIZE][2];

	if (!initialized)
	{
		initialized = true;
	}

	for (x=0;x<SIZE;x++)
	{
		for (y=0;y<SIZE;y++)
		{
			if (board[x][y]==0)
			{
				list[len][0] = x;
				list[len][1] = y;
				len++;
			}
		}
	}

	if (len>0)
	{
		r = rand()%len;
		x = list[r][0];
		y = list[r][1];
		n = ((rand()%10)/9+1)*2;
		board[x][y]=n;
	}
}

int main(int argc, char *argv[]) {
	int board[SIZE][SIZE];
	char c;
	bool success;
	memset(board,0,sizeof(board));
	addRandom(board);
	addRandom(board);
	drawBoard(board);

	do {
		c=getchar();
		switch(c) {
			case 75 :
				success = moveLeft(board);  break; 
			case 77 :
				success = moveRight(board); break; 
			case 72 :
				success = moveUp(board);    break; 
			case 80 :
				success = moveDown(board);  break; 
			default: success = false;
		}
		if (success) {
			drawBoard(board);
			usleep(150000);
			addRandom(board);
			drawBoard(board);
			if (gameEnded(board)) break;
		}
	} while (c!='q');

	printf("GAME OVER\n");

	return EXIT_SUCCESS;
}

