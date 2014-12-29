#include<iostream>
using namespace std;
#define N 4
int tab[N][N];
void fill_with_zeros();
void display_array();
bool is_move_correct(int nx,int ny);
bool try_moving(int x,int y,int &nx,int &ny,int option);
bool knights_tour(int x,int y,int move_number);

int main()
{
    fill_with_zeros();
    knights_tour(0,0,1); //Passing coordinates and number of moves
    std::cout << "finished";
    return 0;
}



bool is_move_correct(int nx,int ny) //This functions checks if coordinates are valid
{
    if(nx<N && ny<N && nx>=0 && ny>=0 && tab[nx][ny] == 0) return true;

    return false;
}


bool try_moving(int x,int y,int &nx,int &ny,int option)
{
    switch(option)
    {
    case 1 :  { if(is_move_correct(x+2,y+1)==true)  { nx = x +2,ny = y+ 1;return true;}}

    case 2 :  { if(is_move_correct(x+2,y-1)==true)  { nx = x +2,ny = y- 1;return true;}}

    case 3 :  { if(is_move_correct(x-2,y+1)==true)  { nx = x -2,ny = y + 1;return true;}}

    case 4 :  { if(is_move_correct(x-2,y-1)==true)  { nx = x -2,ny = y - 1;return true;}}

    case 5 :  { if(is_move_correct(x+1,y+2)==true)  { nx = x +1,ny = y +2;return true;}}

    case 6 :  { if(is_move_correct(x+1,y-2)==true)  { nx = x +1,ny = y -2;return true;}}

    case 7 :  { if(is_move_correct(x-1,y+2)==true)  { nx = x -1,ny = y +2;return true;}}

    case 8 :   { if(is_move_correct(x-1,y-2)==true)  { nx = x -1,ny = y -2;return true;}}

    }

    return false;
}


bool knights_tour(int x,int y,int move_number)
{
    tab[x][y] = move_number;

    if(move_number == N*N-1)
    {
        cout<<"Here is the knight's path : "<<endl;
        display_array();
        return true;
    }

// ******************************************************************************
//PROBLEM MUST BE IN THIS PART OF FUNCTION BUT I'M NOT ABLE TO TELL WHERE EXACTLY 
    else
    {
        //cout<<"Current move number : "<<move_number<<endl;
        int nx = 0,ny = 0;

        for(int w = 1; w<=8; w++)
        {
            if (    try_moving(x,y,nx,ny,w) == true )
            {
                if( knights_tour(nx,ny,move_number+1) == true )
                {
                    return true;
                }
            }
        }
    tab[x][y] = 0;
    }
    return false;
}
// ******************************************************************************
// These functions don't need any commentary : 

void fill_with_zeros()
{
    for(int i =0; i<N; i++)
    {
        for(int j = 0; j<N; j++)
        {
            tab[i][j] = 0;
        }
    }
}

void display_array()
{
    for(int i =0; i<N; i++)
    {
        for(int j = 0; j<N; j++)
        {
            cout<<tab[i][j]<<" ";
        }
        cout<<endl;
    }
}