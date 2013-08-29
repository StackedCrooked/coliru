#include <iostream>
#include <string>
using namespace std;

int main() 
{
    string brackets = "[(])";
    int curly = 0, square = 0, round = 0;
    bool curlyStatus = true, squareStatus = true, roundStatus = true;
    vector<string> OpenOrder;
    for ( std::string::iterator it = brackets.begin(); it != brackets.end(); ++it )
    {
        string LastOpen = OpenOrder.size() - 1;
        if      (*it == '[')                                                { ++square; OpenOrder.insert("["); }
        else if (*it == ']' && LastOpen != 0 && OpenOrder.get(LastOpen).compare("[") == 0)   { --square; OpenOrder.remove(OpenOrder.size() - 1); }
        if      (*it == '{')                                                { ++curly; OpenOrder.insert("["); }
        else if (*it == '}' && LastOpen != 0 && OpenOrder.get(LastOpen).compare("{") == 0)   { --curly; OpenOrder.remove(OpenOrder.size() - 1); }
        if      (*it == '(')                                                { ++round; OpenOrder.insert("["); }
        else if (*it == ')' && LastOpen != 0 && OpenOrder.get(LastOpen).compare("(") == 0)   { --round; OpenOrder.remove(OpenOrder.size() - 1); }
    }
    if (curly == 0 && square == 0 && round == 0)
        cout << "balanced";
    else
        cout << "not balanced";    
}