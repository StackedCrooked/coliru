#include <stddef.h>
#include <cassert>
#include <cstdint>
#include <cstdio>

enum class Result : uint32_t {SUCCESS = 0, INSUCCESS = 1};

void* func(Result& result)
{
    // works great
    /*
    result = Result::INSUCCESS;
    return NULL;
    */

    // error: invalid conversion from ‘long int’ to ‘void*’ [-fpermissive]
    
    //return result = Result::INSUCCESS, NULL;
    
    //printf("hello\n"), nullptr ;
    // compiles, but <result> is not set???
    return (printf("hello\n"), nullptr);
}

void testReturnWithSideEffects()
{
    Result result = Result::SUCCESS;
    func(result);
   // assert(result == Result::INSUCCESS);
}

int main()
{
    testReturnWithSideEffects();
}