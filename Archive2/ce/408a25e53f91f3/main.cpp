using namespace std;
class IntVector{
private:
    unsigned sz;
    unsigned cap;
    int *data;
public:
    IntVector();
    IntVector(unsigned size);
    IntVector(unsigned size, int value);
    unsigned size() const;
};

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;



IntVector::IntVector(){
    sz = 0;
    cap = 0;
    data = NULL;
}

IntVector::IntVector(unsigned size){
    sz = size;
    cap = size;
    data = new int[sz];
    *data = 0;
}

IntVector::IntVector(unsigned size, int value){
    sz = size;
    cap = size;
    data = new int[sz];
    for(unsigned int i = 0; i < sz; i++){
        data[i] = value;
    }
}

unsigned IntVector::size() const{
    return sz;
}

int main()
{
    IntVector testing(6, 4); cout << testing.size() << endl;
}