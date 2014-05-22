#include <iostream>
#include <tuple>
#include <functional>

struct S{
    typedef S ThisT;
    
    template<class IdsT, class DataT>
    struct CallbackPack{
        /*constexpr */CallbackPack(IdsT &selfIds):
            selfIds(selfIds){}

        const IdsT  &selfIds;
    };    
    
    const  CallbackPack<ThisT, ThisT> callbackPack123 = CallbackPack<ThisT, ThisT>((*this));
};
 
int main()
{

}