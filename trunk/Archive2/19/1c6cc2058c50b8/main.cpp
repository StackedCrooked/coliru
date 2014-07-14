#include <vector>

int main( )
{ 
    int index1 = 2;
    int index2 = 2;
    std::vector<std::vector<float>> pVectorTemp_
        ( index1
        , std::vector<float>(index2) );
}