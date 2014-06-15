#include <cstdio>
#include <exception>

enum class Dick
{
    A, B, C, D
};

void Error(std::exception_ptr e)
{
    try {
        if(e) std::rethrow_exception(e);
    }
    catch(Dick x)
    {
        printf("%d\n", (int)x);
    }
}

int main()
{
    std::exception_ptr test;
    try {
        throw Dick::C;
    }
    catch(Dick x)
    {
        test = std::make_exception_ptr(x);
    };
    
    
    Error(test);
}
