#include <iostream>
#include <vector>
#include <functional>

class Pudelko{
private:
    std::vector<int> tab;

public:       
   Pudelko(int size)
    :tab(size)
   {};
      
   Pudelko operator+(const Pudelko &P) const;   
   friend std::istream& operator>>(std::istream& in, Pudelko& P);   
   friend std::ostream& operator<<(std::ostream& out, const Pudelko& P);   
};

Pudelko Pudelko::operator+ (const Pudelko &P) const {
    int size = std::min(tab.size(), P.tab.size());
    Pudelko sum(size);
     for(int i=0; i<size; i++)
        sum.tab[i] = tab[i] + P.tab[i];         
     return sum; 
} 
   
std::istream& operator>>(std::istream& in, Pudelko& P) { // set tab elements
   for(int& i : P.tab)
        in >> i;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Pudelko& P) {
   for(int i : P.tab)
        std::cout << i << ',';       
    return out;
}


int main() {
    Pudelko p(2);  
    std::cin >> p; // set tab elements for first object
    
    Pudelko p1(3);
    std::cin >> p1; // set tab elements for second object
        
    Pudelko suma = p + p1; // I want to add two object
    std::cout << suma;   // show output tab
}