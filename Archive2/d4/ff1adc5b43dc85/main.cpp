#include <iostream>

#include <vector>

#include <string>


using namespace std;


int main()
{

int pocetRadku =5;

int pocetSloupcu =5;

//vector<vector<char>> matice(pocetRadku,vector<char>(pocetSloupcu,'x'));



vector<string> matice;

matice = vector<string>(pocetRadku,string(pocetSloupcu,'x'));

matice[2][2]=' ';


//vector<string> matice(pocetRadku,string(pocetSloupcu,'x'));

//matice[2][2]=' ';

//pole 5-ti prvků, každý bude x

    
for(auto& radek :matice){

            cout<<radek<<endl;

    }
    
return 0;

}
