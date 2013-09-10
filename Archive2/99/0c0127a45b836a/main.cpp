#include <iostream>

using namespace std;


int main()
{

const int num = 5;
string t[num], name;
int m[num], score;

for(int i=0; i < num; i++)
{
    cout << "Enter the name for score # " << i+1 << " :";
    //cin >> name;
    name = "Player " + i;
    t[i] = name;

    cout << "Enter the score for score # " << i+1 << " :";
    //cin >> score;
    score = i;
    m[i] = score;
    
}

for(int i=0; i < num; i++)
    cout << m[i] << endl;

}