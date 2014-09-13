#include <vector>

using namespace std;

template<class T>
 struct s{

    T val;

    public:
        s(T a = T())
        {
            val = a;
        };
        
        T& get() { return val; }
        
        const T& get() const { return val; }
 };

int main()
{
    s <vector<int>*> arrays{};
    return 0;
}
