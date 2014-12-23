#include <iostream>
#include <fstream>
#include <string>

using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;

int main()
{

int push, day;

cout << "Enter the number of the day\nIf this it's the first time you are running the program you should enter 1\n";

cin >> day;

cout << "Enter how many Push Ups you did today\n";

cin >> push;

ofstream pushups("PushUps.txt",std::ios::app);

pushups << day << ' ' << push << std::endl;

ifstream ipushups("PushUps.txt", std::ios::app);

int arraypush[9];
int arrayday[9];

while(ipushups >> day >> push){

   arrayday[day];
   arraypush[push];
}

cout << arrayday[2];
cout << arraypush[2];
}


/* In .txt file :

1 20
2 33
3 44
4 22
5 23
6 44
7 33

It supposed to read 3 and 44,  

   arrayday[day];
   arraypush[push];

I think those two are the problem..How can i write this to work ?
