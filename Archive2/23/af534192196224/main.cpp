#include <vector>

struct MYSTRUCT{

    int a, b;
    std::vector<unsigned> vec;

};


int main(int argc, const char * argv[])
{

    MYSTRUCT ptr_s;

    for(int i = 0 ; i < 100 ; i++){
        ptr_s.vec.push_back(i);
    }
    ptr_s.vec.clear();

    return 0;
}