#include <thread>
#include <vector>
#include <iostream>

class B
{
    /* B.h */

    private:
       std::thread t;
const std::vector<double>* vec;

    /* B.cpp */
    public:
    ~B(){ if(t.joinable()) t.join(); }

    void loadVec(const std::vector<double> &vals){
       vec = &vals;
    }

    bool calc(const int m){
       std::cout << vec->size() << "\n"; //prints 4
       t = std::thread(&B::startThread, this, m);
//       t.join();

       return true;

    }

    void startThread(const int param){

       std::cout << vec->size() << "\n"; //prints 0
        for(std::vector<double>::const_iterator it = vec->cbegin(); it != vec->cend(); ++it){
std::cout << *it << "\n";
            //do some stuff
        }

    }
};

//main.cpp

int main()
{

  B b;
  std::vector<double> v = { 0.5, 1.0, 1.5, 2.0 };
  b.loadVec(v);
  b.calc(5);
}
