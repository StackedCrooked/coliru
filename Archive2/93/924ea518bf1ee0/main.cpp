#include <stddef.h>
#include <cassert>
#include <cstdint>


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
    

    // compiles, but <result> is not set???
    return result = Result::INSUCCESS, nullptr;
}

void testReturnWithSideEffects()
{
    Result result = Result::SUCCESS;
    func(result);
    assert(result == Result::INSUCCESS);
}

int main()
{
    testReturnWithSideEffects();
    }