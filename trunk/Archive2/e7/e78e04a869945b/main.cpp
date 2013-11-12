#include <iostream>
#include <ctime>
#include <cstdlib>

class CGuessNumber
{
public:
    
    int GenerateNumber()
    {
        return rand() % 100 + 1;
    }

void checkNumber(int guess, int answer, int &attempts)
{

    if (guess < answer)
    {
        std::cout << "TOO LOW, TRY AGAIN"  << "\n" << "TRYS LEFT: " << attempts  << "\n";
        attempts--;
    }else if(guess > answer)
    {
        std::cout << "TOO HIGH, TRY AGAIN"  << "\n" << "TRYS LEFT: " << attempts  << "\n";
        attempts--;
    }else if(guess ==  answer)
    {
        std::cout << "YOU WON!"  << "\n" << "TRYS LEFT: " << attempts  << "\n";
    }

    if (attempts <= 0)
    {
        std::cout << "YOU LOST!"  << "\n" << "TRYS LEFT: " << attempts  << "\n";
    }
}
};

class CGAME
{
public:

    CGAME(CGuessNumber &pNumber) : m_number(pNumber)
    {
    }
    void init(int &answer, int &attempts)
    {
        answer = m_number.GenerateNumber();
        attempts = 5;
    };

    void newGame()
    {
        srand (time(NULL));
        int intAnswer, playerGuess, trys;

        init(intAnswer, trys);

        while(intAnswer != playerGuess and trys > 0)
        {
            std::cin >> playerGuess;
            m_number.checkNumber(playerGuess, intAnswer, trys);
        }
    };
    
    private:
        CGuessNumber &m_number;
};

int main()
{
    CGuessNumber pGnum;
    CGAME ONewGame(pGnum);
    ONewGame.newGame();
    return 0;
}