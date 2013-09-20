#include <vector>
#include <iostream>
#include <tuple>

class A{
public:

    explicit A(int i){
        std::cout << "Constructor "<< i <<std::endl;
        for(int l = 0; l<i;l++){
            vec.push_back(l);
        }
    };

    A(A && ref): vec(std::move(ref.vec))
    {
       std::cout << "Move constructor"<<std::endl;
    }

    A & operator=(A && ref){
       if(this != &ref){
            vec = std::move(ref.vec);
       }
       std::cout << "Move assignment"<<std::endl;
       return *this;

    }

    std::vector<int> vec;
};

int main()
{
    std::tuple<A, int> t(std::make_tuple(A(2), 3));
}
