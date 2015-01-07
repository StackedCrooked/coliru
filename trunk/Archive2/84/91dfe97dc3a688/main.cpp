#include <iostream>
#include <string>

using namespace std;

string name()
{   
    string fname;
    cout << "Please type your full name: ";
    getline(cin, fname);
    return fname;
}

int score()
{   
    int points;
    cout << "Please type your score: ";
    cin >> points;
    return points;
}

void result(string fname, int points)
{   
    cout << "Ok " << fname << ", your score of " << points << " is ";
    if (points > 100)
    {   
        cout << "Impossible";
    }
    else if (points == 100)
    {   
        cout << "Perfect!!!";
    }
    else if (points >= 85 && points < 100)
    {   
        cout << "Amazing!!";
    }
    else if (points >= 70 && points < 85)
    {   
        cout << "Good!";
    }
    else if (points >= 50 && points < 70)
    {   
        cout << "Ok.";
    }
    else if (points < 50)
    {   
        cout << "Bad...";
    }
    else
    {   
        cout << "Incorrect input";
    }
}
int main()
{   
    result(name(), score());
    return 0;
}
