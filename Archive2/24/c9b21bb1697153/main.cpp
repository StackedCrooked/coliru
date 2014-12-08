#include <stdio.h>
//#include <conio.h>
//#include <dos.h>
#include <stdlib.h>

void Board();
void PlayerX();
void PlayerO();
void Player_win();
void check();
int win=0,wrong_X=0,wrong_O=0,chk=0;

char name_X[30];
char name_O[30];
int pos_for_X[3][3];
int pos_for_O[3][3];
int pos_marked[3][3];

void main()
{
    int i,ch,j;
	char ans;
	do
	{
		clrscr();
		printf("\n\t\t\tTIC TAC TOE VERSION 1.0");
		printf("\n\t\t\t\t");
		for(i=1;i<=23;i++)
		{
			delay(100);
			printf("*");
		}
		printf("\n1.Start The Game");
		printf("\n2.Quit The Game");
		printf("\nEnter your choice (1-2) : ");
		scanf("%d",&ch);
		switch (ch)
		{
			case 1:
				chk=0;
				win=0;
				/* Page 1 - End */
				/* Page 2 - Start */
				for(i=1;i<=3;i++)
				{
					for(j=1;j<=3;j++)
					{
						pos_for_X[i][j]=0;
						pos_for_O[i][j]=0;
						pos_marked[i][j]=0;
					}
				}
				printf("\n\n");
				clrscr();
				printf("\nEnter the name of the player playing for \n'X': ");
				fflush(stdin);
				gets(name_X);
				printf("\nEnter the name of the player playing for \'O\': ");
				fflush(stdin);
				gets(name_O);
				Board();
				for(;;)
				{
					if(win==1)
						break;
					check();
					if(chk==9)
					{
						printf("\n\t\tMATCH DRAWS!!");
						printf("\nPress any key...");
						break;
					}
					else
						chk=0;
					printf("\nTURN FOR %s:",name_X);
					PlayerX();
					do
					{
						if(wrong_X!=1)
							break;
						wrong_X=0;
						printf("\nTURN FOR %s:",name_X);
						PlayerX();
						}while(wrong_X==1);
						check();
						if(chk==9)
						{
							printf("\n\t\t\tMATCH DRAWS");
							printf("\nPress any key....");
							break;
						}
						else
						/* Page 2 - End */
						/* Page 3 - Start */
							chk=0;
						printf("\nTURN FOR %s:",name_O);
						PlayerO();
						do
						{
							if(wrong_O!=1)
								break;
								wrong_O=0;
								printf("\nTURN FOR %s:",name_O);
								PlayerO();
								}while(wrong_O==1);

								}
							Board();
							if(win!=1)
							{
								printf("\n\t\t\tMATCH DRAWS!!");
								printf("\nPress any key......");
							}
							getch();
							break;
						case 2:
							printf("\n\n\n\t\t\tThank You For Playing The Game.");
							printf("\n");
							printf("\n\t\tCreated By: GFX Ryuzaki");
							getch();
							exit(1);
							break;
							}
							printf("\nWant To Play(Y/N) ? ");
							fflush(stdin);
							scanf("%c",ans);
							}while(ans=='y'||ans=='Y');
						}

						void Board()
						{
							int i,j;
							clrscr();
							printf("\n\t\t\tTIC TAC TOE BOARD");
							printf("\n\t\t\t\t***************");
							printf("\n\n\n");
							printf("\n\t\t\t	1\t	2\t	3");
							for(i=1;i<=3;i++)
							{
								printf("\n \t\t\t ____________________________");
								printf("\n \t\t\t�\t	�\t	�\t	�");
								printf("\n\t\t%d\t",i);
								/* Page 3 - End */
								/* Page 4 - Start */
								for(j=1;j<=3;j++)
								{
									if(pos_for_X[i][j]==1)
									{
										printf("     X");
										printf("      ");
									}
									else if(pos_for_O[i][j]==1)
									{
										printf("     O");
										printf("      ");
									}
									else
									{
										printf("          ");
										continue;
									}
									printf("\n\t\t\t�\t	�\t	�\t	�");
								}
								printf("\n\t\t\t---------------------------------------");
								Player_win();
							}

							void PlayerX()
							{
								int row,col;
								if(win==1)
									ret