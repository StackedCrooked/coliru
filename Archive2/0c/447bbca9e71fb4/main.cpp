bool straightFlush(int card1, int card2, int card3, char color1, char color2, char color3){

        if(card1+1 == card2 && card1 + card1+2 == card3 && color1 == color2 && color1 == color3)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
int main() {
    if(straightFlush == true)
                {
                    return 1;
                }   
}