#include <string>

struct s
{
    union
    {
        std::string str;
        int i;
    };
    
    s() : str("hello") {}
    ~s() {}
};

int main()
{
    s obj;
}