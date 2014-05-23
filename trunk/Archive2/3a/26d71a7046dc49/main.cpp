#include <iostream>
#include <tuple>
#include <functional>

struct S{
    //typedef S ThisT;
    
    
    struct CallbackPack{
        /*constexpr */CallbackPack(S &selfIds):
            selfIds(selfIds){}

        const S  &selfIds;
    };    
    
    const  CallbackPack callbackPack123 = CallbackPack((*this));
};
 
int main()
{
    return 0;
}