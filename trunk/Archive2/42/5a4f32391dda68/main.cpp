#include <iostream>
#include <string>
#include <vector>
#include <map>

///////////////////////////////
// FunctionPointerHolder.h
///////////////////////////////


// Parent of FunctionPointerHolder template class, which can be stored in a data structure and retrieved.
class BaseFunctionPointerHolder
{
};


// A template class that holds a pointer to a function.
// One of these templates gets 
template < typename FunctionType >
class FunctionPointerHolder : public BaseFunctionPointerHolder
{
public:
    FunctionType m_pPointerToFunction;
};


template < typename FunctionType >
FunctionPointerHolder<FunctionType>* CreateFunctionPointerHolder( FunctionType pPointerToFunction )
{
    FunctionPointerHolder<FunctionType>* pReturnValue   = new FunctionPointerHolder<FunctionType>;
    pReturnValue->m_pPointerToFunction  = pPointerToFunction;
    return pReturnValue;
}


// Call a function with 1 param
template< typename ParamType1 >
void CallFunction( BaseFunctionPointerHolder* pFunctionPointerHolder, ParamType1 param1 )
{
    typedef void (* FunctionType)( ParamType1, ParamType2 );
    
    FunctionPointerHolder<FunctionType>* pDowncastFunctionPointerHolder = static_cast< FunctionPointerHolder<FunctionType>* >( pFunctionPointerHolder );
    
    pDowncastFunctionPointerHolder->m_pPointerToFunction( param1, param2 );
}


// Call a function with 2 params
template< typename ParamType1, typename ParamType2 >
void CallFunction( BaseFunctionPointerHolder* pFunctionPointerHolder, ParamType1 param1, ParamType2 param2 )
{
    typedef void (* FunctionType)( ParamType1, ParamType2 );
    
    FunctionPointerHolder<FunctionType>* pDowncastFunctionPointerHolder = static_cast< FunctionPointerHolder<FunctionType>* >( pFunctionPointerHolder );
    
    pDowncastFunctionPointerHolder->m_pPointerToFunction( param1, param2 );
}


void SampleGlobalFunction(int iParam1, float fParam2 )
{
    std::cout << "SampleGlobalFunction param 1: " << iParam1 << "\n";
}


int main()
{
    std::cout << "Hello world." << "\n";
    SampleGlobalFunction( 123, 2.0f );
    
    BaseFunctionPointerHolder* pFunctionPointerHolder   = CreateFunctionPointerHolder( SampleGlobalFunction );
    CallFunction( pFunctionPointerHolder, 256, 7.5f );
}
