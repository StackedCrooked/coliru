#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

///////////////////////////////
// FunctionPointerHolder.h
///////////////////////////////


// Parent of FunctionPointerHolder template class, which can be stored in a data structure and retrieved.
class BaseFunctionPointerHolder
{
};


// A template class that holds a pointer to a function.
// One of these templates gets instantiated for each type of function.
template < typename FunctionType >
class FunctionPointerHolder : public BaseFunctionPointerHolder
{
public:
    FunctionType m_pPointerToFunction;
};


// Creates and returns a FunctionPointerHolder template instance.
namespace FunctionPointerHolderFactory
{
    template < typename FunctionType >
    FunctionPointerHolder<FunctionType>* CreateFunctionPointerHolder( FunctionType pPointerToFunction )
    {
        FunctionPointerHolder<FunctionType>* pReturnValue   = new FunctionPointerHolder<FunctionType>;
        pReturnValue->m_pPointerToFunction  = pPointerToFunction;
        return pReturnValue;
    }
}


// Call a function with 1 param
template< typename ParamType1 >
void CallFunction( BaseFunctionPointerHolder* pFunctionPointerHolder, ParamType1 param1 )
{
    typedef void (* FunctionType)( ParamType1 );
    
    FunctionPointerHolder<FunctionType>* pDowncastFunctionPointerHolder = static_cast< FunctionPointerHolder<FunctionType>* >( pFunctionPointerHolder );
    
    pDowncastFunctionPointerHolder->m_pPointerToFunction( param1 );
}


// Call a function with 2 params
template< typename ParamType1, typename ParamType2 >
void CallFunction( BaseFunctionPointerHolder* pFunctionPointerHolder, ParamType1 param1, ParamType2 param2 )
{
    typedef void (* FunctionType)( ParamType1, ParamType2 );
    
    FunctionPointerHolder<FunctionType>* pDowncastFunctionPointerHolder = static_cast< FunctionPointerHolder<FunctionType>* >( pFunctionPointerHolder );
    
    pDowncastFunctionPointerHolder->m_pPointerToFunction( param1, param2 );
}


// Call a function with 3 params
template< typename ParamType1, typename ParamType2, typename ParamType3 >
void CallFunction( BaseFunctionPointerHolder* pFunctionPointerHolder, ParamType1 param1, ParamType2 param2, ParamType3 param3 )
{
    typedef void (* FunctionType)( ParamType1, ParamType2, ParamType3 );
    
    FunctionPointerHolder<FunctionType>* pDowncastFunctionPointerHolder = static_cast< FunctionPointerHolder<FunctionType>* >( pFunctionPointerHolder );
    
    pDowncastFunctionPointerHolder->m_pPointerToFunction( param1, param2, param3 );
}


// ... we'll need to add more "CallFunction" functions if we need to support more parameters.



///////////////////////////////
// GameObjectFunctionIds.h
///////////////////////////////
enum GameObjectFunctionId
{
    GOF_SAMPLE_GAMEOBJECT_FUNCTION_TYPE1,
    GOF_SAMPLE_GAMEOBJECT_FUNCTION_TYPE2,
    GOF_GET_NUM_COWS
};




///////////////////////////////
// GameObject.h
///////////////////////////////

class Component;

typedef std::pair< Component*, BaseFunctionPointerHolder* > ComponentAndCallbackPair;
typedef std::vector< ComponentAndCallbackPair > VectorOfPairsOfComponentsAndCallbacks;
typedef std::map< GameObjectFunctionId, VectorOfPairsOfComponentsAndCallbacks > MapOfFunctionIdsToFunctions;

class GameObject
{
public:
    
    void Dock( Component* );
    
    
    template < typename FunctionType >
    void RegisterCallbackFunction( GameObjectFunctionId eFunctionId, Component* pComponentThatOwnsFunction, FunctionType pCallbackFunction );
    
    
    // We'll need to add more "Call" functions if we need to support more parameters.    
    void Call( GameObjectFunctionId eFunctionId );
    
    template< typename ParamType1 >
    void Call( GameObjectFunctionId eFunctionId, ParamType1 param1 );
    
    template< typename ParamType1, typename ParamType2 >
    void Call( GameObjectFunctionId eFunctionId, ParamType1 param1, ParamType2 param2 );
    
protected:
    std::vector< Component* > m_componentList;
    MapOfFunctionIdsToFunctions m_mapOfFunctionIdsToFunctions;
};




///////////////////////////////
// Component.h
///////////////////////////////

class GameObject;

class Component
{
public:
    Component( GameObject* pOwningGameObject ) { m_pOwningGameObject = pOwningGameObject; }
    virtual void RegisterCallbackFunctions() { };
    
protected:    
    GameObject* m_pOwningGameObject;
};


///////////////////////////////
// GameObject.cpp
///////////////////////////////


void GameObject::Dock( Component* pComponent )
{
    m_componentList.push_back( pComponent );
}


template < typename FunctionType >
void GameObject::RegisterCallbackFunction( GameObjectFunctionId eFunctionId, Component* pComponentThatOwnsFunction, FunctionType pCallbackFunction )
{
    ComponentAndCallbackPair newComponentAndCallbackPair   = std::make_pair( pComponentThatOwnsFunction, pCallbackFunction );
 
    MapOfFunctionIdsToFunctions::iterator existingVectorOfPairsOfComponentsAndCallbacks  = m_mapOfFunctionIdsToFunctions.find( eFunctionId );

    // TODO
/*
    if( existingVectorOfPairsOfComponentsAndCallbacks == MapOfFunctionIdsToFunctions::end )
    {
        VectorOfPairsOfComponentsAndCallbacks newVectorOfPairsOfComponentAndCallbacks;
        newVectorOfPairsOfComponentAndCallbacks.push_back( newComponentAndCallbackPair );
        m_mapOfFunctionIdsToFunctions[ eFunctionId ]    = newVectorOfPairsOfComponentAndCallbacks;
    }
    else
    {
        existingVectorOfPairsOfComponentsAndCallbacks->push_back( newComponentAndCallbackPair );
    }
*/    
}


/*
    // Still to implement:
    void Call( GameObjectFunctionId eFunctionId );
    
    template< typename ParamType1 >
    void Call( GameObjectFunctionId eFunctionId, ParamType1 param1 );
    
    template< typename ParamType1, typename ParamType2 >
    void Call( GameObjectFunctionId eFunctionId, ParamType1 param1, ParamType2 param2 );
*/



///////////////////////////////
// SampleComponent1.h
///////////////////////////////

class SampleComponent1 : public Component
{
public:

    SampleComponent1( GameObject* pOwningGameObject )
        : Component( pOwningGameObject )
    {
    }


    virtual void RegisterCallbackFunctions()
    {
        m_pOwningGameObject->RegisterCallbackFunction( GOF_SAMPLE_GAMEOBJECT_FUNCTION_TYPE1, this, ImplementationOfSampleFunctionId1 );
    }
    

protected:
    static void ImplementationOfSampleFunctionId1( SampleComponent1* pThis, bool bCanRideHorses, int iNumberOfSongsSungYesterday )
    {
        std::cout << "SampleComponent1::ImplementationOfSampleFunctionId1() called. bCanRideHorses: \"" << bCanRideHorses << "\". iNumberOfSongsSungYesterday: \"" << iNumberOfSongsSungYesterday << "\".\n";
    }
};




///////////////////////////////
// SampleComponent2.h
///////////////////////////////

class SampleComponent2 : public Component
{
public:

    SampleComponent2( GameObject* pOwningGameObject )
        : Component( pOwningGameObject )
    {
    }
    
    
    virtual void RegisterCallbackFunctions()
    {
        m_pOwningGameObject->RegisterCallbackFunction( GOF_SAMPLE_GAMEOBJECT_FUNCTION_TYPE1, this, ImplementationOfSampleFunctionId1 );
        m_pOwningGameObject->RegisterCallbackFunction( GOF_SAMPLE_GAMEOBJECT_FUNCTION_TYPE2, this, ImplementationOfSampleFunctionId2 );
        m_pOwningGameObject->RegisterCallbackFunction( GOF_GET_NUM_COWS, this, GetNumCows );
    }
    
    
    void SetNumCows( int iNumCows )
    {
        m_iNumCows  = iNumCows;
    }
    
protected:
    static void ImplementationOfSampleFunctionId1( SampleComponent2* pThis, bool bCanRideHorses, int iNumberOfSongsSungYesterday )
    {
        std::cout << "SampleComponent2::ImplementationOfSampleFunctionId1() called. bCanRideHorses: \"" << bCanRideHorses << "\". iNumberOfSongsSungYesterday: \"" << iNumberOfSongsSungYesterday << "\".\n";
        std::cout << "This instance of SampleComponent2 has \"" << pThis->m_iNumCows << "\".";
    }
    
    
    static void ImplementationOfSampleFunctionId2( SampleComponent2* pThis, float fDeltaNewtonsPerMillenium )
    {
        std::cout << "SampleComponent2::ImplementationOfSampleFunctionId2() called. fDeltaNewtonsPerMillenium: \"" << fDeltaNewtonsPerMillenium << "\".\n";
        std::cout << "This instance of SampleComponent2 has \"" << pThis->m_iNumCows << "\".";
    }
    
    
    static void GetNumCows( SampleComponent2* pThis, float* pfReturnNumCows )
    {
        *pfReturnNumCows    = pThis->m_iNumCows;
    }
    

    int m_iNumCows;
};



///////////////////////////////
// Main.cpp
///////////////////////////////


void SampleGlobalFunction(int iParam1, float fParam2 )
{
    std::cout << "SampleGlobalFunction param 1: " << iParam1 << "\n";
}


int main()
{
    std::cout << "Hello world." << "\n";
//    SampleGlobalFunction( 123, 2.0f );
    
//    BaseFunctionPointerHolder* pFunctionPointerHolder   = FunctionPointerHolderFactory::CreateFunctionPointerHolder( SampleGlobalFunction );
//    CallFunction( pFunctionPointerHolder, 256, 7.5f );


/////
    // In actual game code, something like this would be data-driven.
    GameObject* pSampleGameObject   = new GameObject();
    
    SampleComponent1* pSampleComponent1  = new SampleComponent1( pSampleGameObject );
    pSampleGameObject->Dock( pSampleComponent1 );
    
    SampleComponent2* pSampleComponent2  = new SampleComponent2( pSampleGameObject );
    pSampleComponent2->SetNumCows( 64 );
    pSampleGameObject->Dock( pSampleComponent2 );
/////    
    
    
    // In actual game code, these calls would usually happen inside a component, most often on their
    // owning GameObject, but sometimes on another GameObject.
    pSampleGameObject->Call( GOF_SAMPLE_GAMEOBJECT_FUNCTION_TYPE1, true, 36 );
    pSampleGameObject->Call( GOF_SAMPLE_GAMEOBJECT_FUNCTION_TYPE2, 22.5 );
    
    int iNumCowsInSampleGameObject  = -1;
    pSampleGameObject->Call( GOF_GET_NUM_COWS, &iNumCowsInSampleGameObject );
    std::cout << "Sample game object has " << iNumCowsInSampleGameObject << " cows.";
}
