#include <map>
#include <tuple>

struct Banane{
    Banane(){}
    /* delete move assign operator and move constructor */
    Banane(const Banane&) = delete;
    Banane&operator=(const Banane&) = delete;
    Banane(Banane&&) = delete;
    Banane&operator=(Banane&&) = delete;
};

int main() {
    std::map<int,Banane> m;

    m.emplace(std::piecewise_construct,
          std::make_tuple(3) , 
          std::make_tuple() 
         );
}