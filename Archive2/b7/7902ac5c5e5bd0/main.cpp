#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void shuffle(int [][4]);
int main()
{
    char comma, ans = 'y';
    int r1, c1, r2, c2, cards[4][4], i(0);
    bool cardstatus[4][4];  // array to store whether card is flipped or not, you can use char if bool doesn't work for you.    
    bool gameover = false; // if bool doesn't work for you, use char in same way I told for cardstatus.
    int moves;    
    do
    {
        moves = 0;
        //shuffle
        shuffle(cards); // I think shuffling cards is better idea than shuffling base start array.
        //display board
        cout<<"    1 2 3 4\n";
        cout<<"  ";
        for (int i=0; i<=8; i++)
        {
            cout<<"-";
        }
        cout<<endl;
        for (int r=0; r<4; r++)
        {
            cout<<r+1<<" | ";
            for (int c=0; c<4; c++)
            {
                cout<<"* ";
                cardstatus[r][c] = false; // use 0 for false and 1 for true if true/false is not supported.
            }
            cout<<endl;
        }
        cout<<endl;
        do // game starts from here as user will do moves here onwards.
        {
            do
            {
                //selection
                cout<<"Please insert the first card row and column seperated by a comma.\n";
                cin>>r1>>comma>>c1;
                if(cardstatus[r1-1][c1-1] == true) // check if the card is flipped.
                { 
                    cout << "This card is already flipped! Select another card.";
                }
            }while(cardstatus[r1-1][c1-1]!= false);
            do
            {
                cout<<"Please insert the second card row and column separated by a comma.\n";
                cin>>r2>>comma>>c2;
                if(cardstatus[r2-1][c2-1] == true) // check if the card is flipped.
                { 
                    cout << "This card is already flipped! Select another card.";
                }
                if((r1==r2)&&(c1==c2))
                {
                    cout << "You can't select same card twice!";
                    continue;
                }
            }while(cardstatus[r2-1][c2-1]!= false);
            //fix
            r1--;
            c1--;
            r2--;
            c2--;
            //reveal
            cout<<"    1 2 3 4\n";
            cout<<"  ";
            for (int i=0; i<=8; i++)
            {
                cout<<"-";
            }
            cout<<endl;
            for (int r=0; r<4; r++)
            {
                cout<<r+1<<" | ";
                for (int c=0; c<4; c++)
                {
                    if ((r==r1)&&(c==c1))
                    {
                        cout<<cards[r][c]<<" ";
                    }
                    else if((r==r2)&&(c==c2))
                    {
                        cout<<cards[r][c]<<" ";
                    }
                    else if (cardstatus[r][c] == true)
                    {
                        cout<<cards[r][c]<<" ";
                    }
                    else
                    {
                        cout<<"* ";
                    }
                }
                cout<<endl;
            }                        
            //match?
            if (cards[r1][c1]==cards[r2][c2]) // if cards match, keep them flipped.
            {
                cout << "Cards Matched!"<<endl;
                
                cardstatus[r1][c1] = true;                             
                cardstatus[r2][c2] = true;                            
            }
            cin.get();
            cin.get();
            //this pushes the next board onto a blank screen
            for (int b=0; b<=20; b++)
                cout<<endl;
                
            for (int r=0; r<4; r++) // reprint the board, makes it easy for user to put a new guess.
            {
                cout<<r+1<<" | ";
                for (int c=0; c<4; c++)
                {                
                    if (cardstatus[r][c] == true)
                    {
                        cout<<cards[r][c]<<" ";
                    }
                    else
                    {
                        cout<<"* ";
                    }
                }
                cout<<endl;
            }            
            gameover = true;
            for (int r=0; r<4; r++) // check all card status, they all should be true/flipped to end the game.
            {
                for (int c=0; c<4; c++)
                {
                    if(cardstatus[r][c]==false)
                    {
                      gameover = false;
                      break;
                    }
                }
                if(gameover == false)
                {
                    break;
                }
            }
            moves++; // counting moves here.
            //repeat
        }while(gameover != true); // loop, the only way to get out is to finish the game!
        cout << "Congratulations, You won!!!"<<endl;
        cout << "It Required " << moves << " moves to finish it."<<endl<<endl;
        cout << "Would you like to play again? (y=Yes/n=No) : ";
        ans = cin.get();
    }while(ans == 'y' || ans == 'Y'); // If user wants to play game again.
    cin.get();
    return 0;
}
void shuffle(int cards[][4])
{
    int start[16]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
    for (int s=0; s<=20; s++)
    {
        for (int x=0; x<16; x++)
        {
            srand((unsigned)time(NULL));
            int i=rand()%15+1;
            int temp=start[x];
            start[x]=start[i];
            start[i]=temp;
        }
    }    
    int i=0;
    for (int r=0; r<4; r++) // put values in cards here
        {
            for (int c=0; c<4; c++)
            {
                cards[r][c]=start[i];
                cout<<cards[r][c];                
                i=i+1;
            }
            cout<<endl;
        }
}


