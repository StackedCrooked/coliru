#include <iostream>           // std::cout

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