template<typename T>
struct TC;

class CATest;
using TES=TC<CATest>;

class CTest;

int main()
{
    CTest* p=nullptr;
    p = p;
    
    TES * p2 = nullptr;
    p2 = p2;
}