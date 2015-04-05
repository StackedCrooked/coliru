// condition_variable example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <unordered_map>
#include <utility>
#include <sstream>
#include <random>
#include <cwctype>
#include <locale>

class QWidget;

class grille
{
    public:
    
        grille(int width, int height, QWidget *parent){
            std::cout << "1" << std::endl;
        }
         
        grille(int width, int height, int nbMines, QWidget *parent) :  grille(width,height, parent) {
            std::cout << "2" << std::endl;
        }
};

int main ()
{
    grille t(3, 4, 5, nullptr);

    return 0;
}