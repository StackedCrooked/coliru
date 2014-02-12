#include <stdio.h>
#include <stddef.h>

typedef struct {
    int xpos;
    int ypos;
} BRDPOS;

void printBoard(int brd_size,char board[][brd_size]){
    int i,j;
    for(i = 0;i < brd_size;i++){
        for(j = 0;j < brd_size;j++){
            if(j == 0) printf("| ");
            printf("%c |",(char)board[i][j]);
            if(j == (brd_size - 1)){
                printf("\n");
            }
        }
    }   
}

BRDPOS getPosition(int brd_size,char board[][brd_size]){
    //Enter Positions X and Y
    BRDPOS pos;
    int x,y;
    do{
        printf("Enter the x-position:");
        scanf("%d",&x);
        printf("\nEnter the y-position:");
        scanf("%d",&y);
        printf("\n");               
    }while(board[x][y] != ' ');
    pos.xpos = x;
    pos.ypos = y;
    return pos;
}

void updateBoard(int brd_size,char board[][brd_size],BRDPOS pos,int player){
    if(player == 0){
        board[pos.xpos][pos.ypos] = 'X';
    }else{
        board[pos.xpos][pos.ypos] = 'O';
    }
}

int isWinningPosition(BRDPOS position,int brd_size,char brd[][brd_size],int player){
    char posChar = (player == 0)? 'X':'Y';
    int xPos = position.xpos;
    int yPos = position.ypos;
    char yStatus = brd[0][0];
    char majDiag = brd[0][0];
    char minDiag = brd[0][brd_size-1];
    int xstatus = 0;
    int ystatus = 0;
    int majdiag = 0; 
    int mindiag = 0;
    int i,j,k,l;
    for(i=0;i< brd_size;i++){
        if(brd[xPos][yPos] == brd[xPos][i]){
            xstatus = 1;
        }else{
            xstatus = 0;
            break;
        }
    }
    //Check if the horizontal has the same characters
    for(j=0;j<brd_size;j++){
        if(brd[xPos][yPos] == brd[j][yPos]){
            ystatus = 1;
        }else{
            ystatus = 0;
            break;
        }
    }
    //Check if the major diagonal has the same characters
    if(xPos == yPos){
        for(k=0;k < brd_size;k++){
            if(majDiag == brd[k][k]){
                majdiag = 1;
            }else{
                majdiag = 0;
                break;
            }
        }
    }
    //Check if the minor diagonal has the same characters
    if(xPos == (brd_size - 1 - yPos)){
            for(l = 1;l < brd_size;l++){
                if(minDiag == brd[l][(brd_size-1) - l]){
                    mindiag = 1;
                } else {
                    mindiag = 0;
                    break;
                }
        }
    }
    return xstatus|ystatus|majdiag|mindiag; 
}

int main()
{
    //Flag to indicate the current player 0 for A, 1 for B. Default to A
    int player = 0;
    //Flag to indicate the winner, -1 for no winner, 0 for A, 1 for B
    int winner = -1;
    //Counter to indicate the total number of turns
    int counter = 0;
    //Tic-Tac-Toe board
    char board[4][4];
    int i,j;
    for(i = 0;i<4;i++){
        for(j = 0;j<4;j++){
            board[i][j] = ' ';
        }
    }
    //Keep iterating until a winner is found and the cell count is less than 16 
    while((winner == -1) && (counter < 16)){
        //Print the tic-tac-toe board
        printBoard(4,board);
        //Ask position to place the X for player 1
        //getPosition keeps asking for the position until a legal position has been entered
        printf("Enter positions for PlayerA:\n");
        BRDPOS positionA = getPosition(4,board);
        //Update board with positionA
        printf("Updating the board:\n");
        updateBoard(4,board,positionA,0);
        //Check if the updated position is a winning position
        if(isWinningPosition(positionA,4,board,0)){
            //Mark player A as the winner
            printf("Marking player A as the winner \n");
            winner = 0;
            break;
        }
        //update the move counter
        counter++;
        //print updated board
        printBoard(4,board);
        //Ask position to place the 'O' for player 2
        printf("Enter position for PlayerB:\n");
        BRDPOS positionB = getPosition(4,board);
        //Update board with positionB
        updateBoard(4,board,positionB,1);
        //Check if the updated position is a winning position       
        if(isWinningPosition(positionB,4,board,1)){
            winner = 1;
            break;
        }
        //update the move counter
        counter++;
    }
    //print the final board configuration
    printBoard(4,board);
    switch(winner){
        case -1: printf("The game is a draw!\n");
             break;
        case 0: printf("Player 1 has won the game\n");
             break;
        case 1: printf("Player 2 has won the game\n");
            break;

    }
    return 0;
}