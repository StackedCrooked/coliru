#include <stdio.h>
#include <string.h>
#include <string>
#include <set>

const int countP = 6;
const int countT = 7;
int Fp[countP][countT] =
{
    0, 0, 1, 1, 1, 0, 0,
    0, 0, 1, 1, 0, 0, 0,
    0, 0, 0, 0, 1, 2, 0,
    0, 0, 0, 0, 0, 0, 1,
    0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0
};
int Ft[countT][countP] =
{
    1, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0,
    0, 0, 1, 0, 1, 0,
    0, 0, 0, 1, 1, 0,
    0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 2
};
int M0[countP]= {2,1,1,1,1,2};

bool isPossibleToTransit(int M[countP], int j) //Переход j сработает в том случае, если для каждого элемента множества Pj
{                               // выполняется условие M0[i] - Fp[i][j] >= 0
    bool isPossible = true;
    for (int i = 0; i < countP; i++)
        if (Fp[i][j] > 0)
            if (M[i] - Fp[i][j] < 0)
                isPossible = false;
    return isPossible;
}
void printInfoAboutTransition(int j)
{
    printf("\nДля перехода %d: ", j+1);
    printf("\nВходные позиции:");
    for (int i = 0; i < countP; i++)
        if (Fp[i][j] > 0)
            printf("\n\tПозиция %d(%d)", i+1, Fp[i][j]);
    printf("\nВыходные позиции:");
    for (int i = 0; i < countP; i++)
        if (Ft[j][i] > 0)
            printf("\n\tПозиция %d(%d)", i+1, Ft[j][i]);
}

void transit(int (&M)[countP], int j) //срабатывает переход j при маркировке M
{
    if (isPossibleToTransit(M, j))
    {
        for (int i = 0; i < countP; i++)
            if (Fp[i][j] > 0)
                M[i] = M[i] - Fp[i][j] + Ft[j][i];
        for (int i = 0; i < countP; i++)
            if (Ft[j][i] > 0)
                M[i] = M[i] + Ft[j][i];
    }
}

std::set<std::string> makeDictonary(int M[countP], int time, std::string word="")
{
    std::set<std::string> words;
    if (time > 0 && time < 5)
    {
        for (int i = 0; i < countT; i++)
            if (isPossibleToTransit(M, i))
            {
                std::string newWord = word + std::to_string(i+1);
                words.insert(newWord);
                int M1[countP];
                for (int k = 0; k < countP; k++)
                    M1[k] = M[k];
                transit(M1, i);
                std::set<std::string> anotherWords = makeDictonary(M1, time+1, newWord);
                words.insert(anotherWords.begin(), anotherWords.end());
                /*if (M1[0]+M1[1]+M1[2]+M1[3]+M1[4]+M1[5] > 10)
                {
                    printf("\n Sum = %d", M1[0]+M1[1]+M1[2]+M1[3]+M1[4]+M1[5]);
                }*/
            }
    }
    return words;
}

int main()
{
    std::set<std::string> words = makeDictonary(M0, 1);;

    for (std::set<std::string>::const_iterator it = words.begin(); it != words.end(); it++)
        printf("\n%s", (*it).c_str());

    return 0;
}
