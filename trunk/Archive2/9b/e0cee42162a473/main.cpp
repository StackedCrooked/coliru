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
									return;
								printf("\nEnter the row no.: ");
								fflush(stdin);
								scanf("%d",&row);
								printf("Enter the coloumn no.: ");
								fflush(stdin);
								scanf("%d",&col);
								if(pos_marked[row][col==1 || row<1 || row>3 || col<1 || col>3)
								{
									printf("\nWRONG POSITION!! Press any key.....");
									wrong_X=1;
									getch();
									Board();
								}
								else
								{
									pos_for_X[row][col]=1;
									pos_marked[row][col]=1;
									Board();
								}
								/* Page 4 - End */
								/* Page 5 - Start */
							}

								void PlayerO()
								{
									int row,col;
									if(win==1)
										return;
									printf("\nEnter the row no. : ");
									scanf("%d",&row);
									printf("Enter the coloumn no. : ");
									scanf("%d",col);
									if(pos_marked[row][col]==1 || row<1 || row>3 || col<1 || col>3)
									{
										printf("\nWRONG POSITION!! Press any key...");
										wrong_O=1;
										getch();
										Board();
									}
									else
									{
										pos_for_O[row][col]=1;
										pos_marked[row][col]=1;
									}
								}
								void Player_win()
								{
									int i;
									for(i=1;i<=3;i++)
									{
										if(pos_for_X[i][1]==1 && pos_for_X[i][2]==1&&pos_for_X[i][3]==1)
										{
											win=1;
											printf("\n\nRESULT: %s wins!!",name_X);
											printf("\nPress any key............");
											return;
										}
									}
									for(i=1;i<=3;i++)
									{
										if(pos_for_X[1][i]==1 && pos_for_X[2][i]==1 && pos_for_X[3][i]==1)
										{
											win=1;
											printf("\n\nRESULT: %s wins!!",name_X);
											printf("\nPress any key.............");
											return;
										}
									}
									/* Page 5 - End */
									/* Page 6 - Start */
									if(pos_for_X[i][1]==1 && pos_for_X[2][2]==1 &&
									pos_for_X[3][3]==1)
									{
										win=1;
										printf("\n\nRESULTL: %s wins!!",name_X);
										printf("\Press any key.....");
										return;
									}
									else if (pos_for_X[1][3]==1 && pos_for_X[2][2]==1 &&
									pos_for_X[3][1]==1)
									{
										win=1;
										printf("\n\nRESULT: %s wins!!",name_X);
											printf("\nPress any any key.....");
										return;
									}
									for (i=1;i<=3;i++)
									{
										if(pos_for_O[i][1]==1 && pos_for_O[i][2]==1 && pos_for_O[i][3]==1)
										{
										win=1;
										printf("\n\nRESULT: %s wins!!",name_O);
											printf("\nPress any key.....");
										return;
									}
									}
									for(i=1;i<=3;i++)
									{
										if(pos_for_O[1][i]==1 && pos_for_O[2][i]==1 && pos_for_O[3][i]==1)
										{
											win=1;
											printf("\n\nRESULT: %s wins!!",name_O);
												printf("\nPress any key.....");
											return;
										}
										if (pos_for_O[1][1]==1 && pos_for_O[2][2]==1 && pos_for_O[3][3]==1)
										{
											win=1;
											printf("\n\nRESULT: %s wins!!",name_O);
											printf("\nPress any key.....");
											return;
										}
										else if(pos_for_O[1][3]==1 && pos_for_O[2][2]==1 && pos_for_O[3][1]==1)
										{
											win=1;
											/* Page 6 - End */
											/* Last Page - Start */
											printf("\n\nRESULT: %s wins!!",name_O);
												printf("\nPress any key.....");
											return;
										}
									}
									void chec()
									{
										int i,j;
										for(i=1;i<=3;i++)
										{
											if(pos_marked[i][j]==1)
												chk++;
												else
													continue;
										}
									}
							} /*End of Code */