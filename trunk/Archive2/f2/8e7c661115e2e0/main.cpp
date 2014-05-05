/*template<typename T>
struct TC;

class CATest;
using TES=TC<CATest>;*/

template<typename T>
class ForwardDeclared;

class ForwardDeclared2;

class CTest;

void TestFunction1(void);
void TestFunction2(void);

int main()
{
    CTest* p=nullptr;
    p = p;
    
    ForwardDeclared<int> * p1 = nullptr;
    TestFunction(p1);
    p1 = p1;
    
    ForwardDeclared2 * p2 = nullptr;
    TestFunction(p2);
    p2 = p2;
}

template<typename T>
struct TC;

class CATest;
using TES=TC<CATest>;

void TestFunction1(ForwardDeclared<int> *p1)
{
    
}

void TestFunction2(ForwardDeclared2 *p2)
{
    
}