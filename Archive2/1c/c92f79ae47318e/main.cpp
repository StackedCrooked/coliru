#include <iostream>
#include <cstdio>
#include <cstdlib>

using std::cout ;
using std::cin ;

int main()
{
    int p1,p2,p3;
    
    p3 = (rand() % 3) + 1;
    
    printf(" ---------------------------------------------------------------");
    printf("\n WELCOME TO JACK EN POY");
    printf("\n This Filipino game needs two player that \n Enter thier ROCK,PAPER,SCCISOR");
    printf("\n Player can input");
    printf("\n 0=Rock");
    printf("\n 1=Scissor");
    printf("\n 2=Paper"); 
    cout<<"\n ---------------------------------------------------------------\n\n";
    
    cout<<"Player 1 turns: \n";
    cin>>p1;
    cout<<"Player 2 Turns: \n";
    cin>>p2;
    
    if(p1==p2)
    printf("\n It's a Draw!\n\n");
    else if(p1==0&&p2==1)
    printf("\n Player 1 Wins!\n\n");
    else if(p1==2&&p2==0)
    printf("\n Player 1 Wins!\n\n");
    else if(p1==1&&p2==2)
    printf("\n Player 1 Wins!\n\n");
    else if(p1==1&&p2==0)
    printf("\n Player 2 Wins!\n\n");
    else if(p1==2&&p2==1)
    printf("\n Player 2 Wins!\n\n");
    else if(p1==0&&p2==2)
    printf("\n Player 2 Wins!\n\n");
    
    //system("pause");
    return 0;
}