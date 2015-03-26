// random practice on conversation
#include <iostream>
#include <string>
using namespace std;

int main ()
{
    string str;
    string bad;

    cout << "How has your day been?  \n";
    cin >> str;
    if (str = "good") {
        cout << "Thats good to hear!\n";
    }
    else if (str = "bad") {
        cout << "That's too bad, what happened?  \n";
        cin >> bad;
        cout << "I'm sorry to hear that...\n";
    }
    else {
        cout << "I'm sorry, I couldn't understand you...\n";
    }
}