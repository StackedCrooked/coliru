#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string> 
using namespace std;
int main()
{
    ifstream player1;
    ifstream player2;
    char user1_Play, user2_Play;
    int cnt1 = 0, cnt2 = 0;
    string player1_name, player2_name;

    cout << "Welcome to PRS game player 1,what is your name?";
    cin >> player1_name;
    cout << "Welcome to PRS game player 2, what is your name?";
    cin >> player2_name;

    player1.open("player1.txt");
    if (player1.fail())
    {
        cout << "File opening failed./n";
        exit(1);
    }

    player2.open("player2.txt");
    if (player2.fail())
    {
        cout << "File opening failed./n";
        exit(1);
    }
    player1 >> user1_Play;
    player2 >> user2_Play;

    while (!player1||!player2 .eof)
        cout << player1 << "played:" << user1_Play << "and" << player2 << "played"     << user2_Play << endl;

    if (user1_Play == user2_Play)
    {
        cout << "nobody wins!!" << endl;
    }
    else if ((user1_Play == 'P') && (user2_Play == 'R'))
    {
        cout << player1_name << "wins...Paper covers Rock!!/n";
        cnt1++;
    }
    else if ((user1_Play == 'R') && (user2_Play == 'S'))
    {
        cout << player1_name << "wins...Rock crushes Scissors!!/n";
        cnt1++;
    }
    else if ((user1_Play == 'S') && (user2_Play == 'P'))
    {
        cout << player1_name << "wins...Scissors cuts Paper!!/n";
        cnt1++;
    }
    else if ((user2_Play == 'P') && (user1_Play == 'R'))
    {
        cout << player2_name << "wins...Paper covers Rock!!/n";
        cnt2++;
    }
    else if ((user2_Play == 'R') && (user1_Play == 'S'))
    {
        cout << player2_name << "wins...Rock crushes Scissors!!/n";
        cnt2++;
    }
    else if ((user2_Play == 'S') && (user1_Play == 'P'))
    {
        cout << player2_name << "wins...Scissors cuts Paper!!/n";
        cnt2++;
    }
    player1 >> user1_Play;
    player2 >> user2_Play;

    cout << "Number of wins for" << player1 << "" << cnt1 << endl;
    cout << "Number of wins for" << player2 <<""<<cnt2<<endl;

    player1.close();
    player2.close();
}