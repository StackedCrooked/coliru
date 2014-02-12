#include <iostream>
#include <string>
#include <vector>

class kruh  //trida kruh
{
private:
    double polomer{0}; //clenska promenna
public:
    kruh(double polomer) //konstruktor
    {
        this->polomer = (polomer < 10) ? (polomer) : (0);
    }
    
    void nastavpolomer(double polomer) //setter
    {
        this->polomer = (polomer < 10) ? (polomer) : (0);
    }
    //konstantni funkce, nemeni hodnotu clenskych promennych, informace pro kompilator
    double vratpolomer() const //getter
    {
        return this->polomer;
    }
    
    double vratobsah() //clenska funkce
    {
        return polomer * polomer *3.1415;
    }
};

int main()
{
    kruh kruh(7);
    kruh.nastavpolomer(5);
    
    
    std::cout << "polomer: " << kruh.vratpolomer() <<std::endl << "obsah: " << kruh.vratobsah() << std::endl;
    return 0;
}


//2Dpole vektorama
// vector<vector<char>> matice(5, vector<char>(5, 'x')); 5x5 matice charu naplnena 'x' s nazvem matice