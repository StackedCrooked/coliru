#include <iostream>
#include <string>
#include <random>
#include <chrono>

using namespace std;

int main()
{
    //plusieurs manières :
    //#1 :  La plus courte, mais pas très souple
    std::random_device rd;
    std::cout << "Nombre random : " << rd() << std::endl;
    
    //#2 : La même sur un interval donné :
    std::default_random_engine engine; //le 'moteur d'aléatoire'. Ici on prend celui par défaut
    std::uniform_int_distribution<int> distribution(1, 6); //Ici on choisit notre distribution, donc là c'est une distribution uniforme (tous les nombres ont autant de chance de tomber) d'entiers qui renverra un int (on aurait pu mettre long int, unsigned, etc.)
    std::cout << 
}