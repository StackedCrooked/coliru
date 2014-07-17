#include<memory>
#include<vector>

using namespace std;

struct Base { };
struct Derived : public Base { };
int main(){
    vector<unique_ptr<Base>> vec;
    vec.push_back(make_unique<Derived>());
}