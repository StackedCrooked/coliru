#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <functional>

class CStats
{
public:
    CStats() 
    {
        d = 3.0f;
        a = 1;
    }
    int a;
    double d;
};

namespace std
{
    template<>
    struct hash<CStats>
    {
        std::size_t operator()(CStats const& Stats) const
        {
    		const char *pChunk = reinterpret_cast<const char *>(&Stats);
			//std::hash<char> HashFkt;
			std::size_t r = 5381;
			for(unsigned i = 0; i < sizeof(CStats); i++, pChunk++)
            {
                cout << static_cast<int>(*pChunk) << ", ";
				r = ((r << 5) + r) + *pChunk;
            }
            cout << '\n';
            return r;
        }
    };
}

int main()
{
    std::srand(0);

    std::hash<CStats> Hash;
    CStats a, b;

    std::cout << "a=" << Hash(a) << '\n';
    std::cout << "b=" << Hash(b) << '\n';
    std::cout << "a equals a: " << (Hash(a) == Hash(a)) << '\n';
    
}
