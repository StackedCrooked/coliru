#include<memory>
#include<vector>

using namespace std;

struct Base { };
struct Derived : public Base { };

vector<unique_ptr<Base>> vec;

struct Unrelated { };

template <typename D>
void AddItem(const D& thing) {
    vec.push_back(make_unique<D>(thing));
}


int main(){
    AddItem(Derived());
    AddItem(Unrelated());
}