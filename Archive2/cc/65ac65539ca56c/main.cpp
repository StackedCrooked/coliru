#include <iostream>
using namespace std;

class Board
{
public:

    void fillBoard()
    {
        for (int i = 0; i < 22; i++)
        {
            for (int k = 0; k < 78; k++)
            {
                board[i][k] = ' ';
            }
        }
    }

    void drawBoard()
    {
        for (int i = 0; i < 22; i++)
        {
            for (int k = 0; k < 78; k++)
            {
                cout<<board[i][k];
            }
            cout<<"\n";
        }
    }

    void addView(int width, int height, char img, int tallness = 0)
    {
        /// board[height][width] = img;
        for (int i = 0; i <= tallness; i++, height++)
        {
            board[height][width] = img;
        }
    }

private:
   char board[78][22];
};


int main()
{
    Board board;
    board.fillBoard();

    ///board.addView(x, y, 'O');
    board.addView(0, 10, '|', 5); 
    board.drawBoard();

    return 0;
}