#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>

struct Boo{
    Boo(){ std::cout<<"Boo "; }
    ~Boo(){ std::cout<<"~Boo "; }
};
typedef boost::shared_ptr<Boo> BooPtr;

int main(){
    std::vector<BooPtr> v;
    v.push_back(BooPtr(new Boo));
    v.push_back(BooPtr(new Boo));
}
