#include <vector>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

template<typename T>
class Lijstje {
public:
    Lijstje(std::initializer_list<T> list) {
        for (auto& i : list) {
            cout << i << endl;    
        }
    }
    Lijstje(T t) {
        cout << t << endl;    
    }
    Lijstje() = default;
    ~Lijstje() = default;
};


int main() {
    Lijstje<int> m{1,2,3,4,5};
    Lijstje<int> n(1);
    //std::shared_ptr<Lijstje<int>> o = std::make_shared<Lijstje<int>>({1,2,3,4,5});
    std::shared_ptr<Lijstje<int>> p = std::make_shared<Lijstje<int>>(24);
    
}