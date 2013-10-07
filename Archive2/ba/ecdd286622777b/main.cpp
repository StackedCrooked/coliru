// This snippet demonstrates how components are going to talk to each other.
// Note especially GameObject::RegisterCallbackFunction() and GameObject::Call().
// You can get away with looking at just SampleComponent1, SampleComponent2, and main() to get a sense of what's going on.


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <exception>


///////////////////////////////
// AltTypeId.h
///////////////////////////////

// From http://www.altdevblogaday.com/2011/10/10/making-your-own-type-id-is-fun/

//////////////////////////////////////////////////////////////////////////
// typedef for unsigned int as altTypeId
typedef unsigned char* altTypeId;


//////////////////////////////////////////////////////////////////////////
// templated TypeID class
//
// Assuming that unsigned int is the same as the pointer type on the platform 
// this is guaranteed to return a unique value for each instantiation.
// 
// The only caveat to this is that the actual value of the ID will almost
// certainly not remain constant over multiple executions of the exe.
//
template< typename T >
class TAltTypeIdGenerator
{
private:
    // no instance of this class can be created.
    TAltTypeIdGenerator()
	{}

public:
	// this generates a typeID for each class that instantiates the template
	static altTypeId GetAltTypeId()
	{
        // I wasn't sure if the char would take up > 1 byte because of alignment.
        // With VS2010 on win32 they take up exactly 1 byte each.
		static char iAddressOfThisIsTheTypeId;
		return reinterpret_cast< altTypeId >( &iAddressOfThisIsTheTypeId );
	}
};

// since all values of altTypeId are now valid memory addresses we can make this the same as NULL
#define ALTTYPEID_INVALID	NULL

// macro for getting hold of a type's altTypeId
#define GetAltTypeIdOf( TYPENAME )		( TAltTypeIdGenerator< TYPENAME >::GetAltTypeId() )



//////////////////////////////////////////////////////////////////////////
// template function that resolves to the correct form of 
// CReflectionData< T >::GetTypeID() based on the input type
template< typename T >
altTypeId GetAltTypeIdOfInstance( T instance )
{
	return TAltTypeIdGenerator< T >::GetAltTypeId();
}




///////////////////////////////
// FunctionPointerHolder.h
///////////////////////////////


class FunctionSignatureMismatchException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "You called a function with parameters that don't match those of the function you're trying to call.";
  }
} g_functionSignatureMismatchException;




// Parent of FunctionPointerHolder template class, which can be stored in a data structure and retrieved.
class BaseFunctionPointerHolder
{
public:    
    virtual altTypeId GetFunctionTypeId() = 0;
};


// A template class that holds a pointer to a function.
// One of these templates gets instantiated for each type of function.
template < typename FunctionType >
class FunctionPointerHolder : public BaseFunctionPointerHolder
{
public:    
    virtual altTypeId GetFunctionTypeId() { return GetAltTypeIdOf(FunctionType); }
    

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
    
    if( GetAltTypeIdOf(FunctionType) != pFunctionPointerHolder->GetFunctionTypeId() )
    {
        throw g_functionSignatureMismatchException;
    }
    
    FunctionPointerHolder<FunctionType>* pDowncastFunctionPointerHolder = static_cast< FunctionPointerHolder<FunctionType>* >( pFunctionPointerHolder );
    
    pDowncastFunctionPointerHolder->m_pPointerToFunction( param1 );
}


// Call a function with 2 params
template< typename ParamType1, typename ParamType2 >
void CallFunction( BaseFunctionPointerHolder* pFunctionPointerHolder, ParamType1 param1, ParamType2 param2 )
{
    typedef void (* FunctionType)( ParamType1, ParamType2 );
    
    if( GetAltTypeIdOf(FunctionType) != pFunctionPointerHolder->GetFunctionTypeId() )
    {
        throw g_functionSignatureMismatchException;
    }
    
    FunctionPointerHolder<FunctionType>* pDowncastFunctionPointerHolder = static_cast< FunctionPointerHolder<FunctionType>* >( pFunctionPointerHolder );
    
    pDowncastFunctionPointerHolder->m_pPointerToFunction( param1, param2 );
}


// Call a function with 3 params
template< typename ParamType1, typename ParamType2, typename ParamType3 >
void CallFunction( BaseFunctionPointerHolder* pFunctionPointerHolder, ParamType1 param1, ParamType2 param2, ParamType3 param3 )
{
    typedef void (* FunctionType)( ParamType1, ParamType2, ParamType3 );
    
    if( GetAltTypeIdOf(FunctionType) != pFunctionPointerHolder->GetFunctionTypeId() )
    {
        throw g_functionSignatureMismatchException;
    }
    
    FunctionPointerHolder<FunctionType>* pDowncastFunctionPointerHolder = static_cast< FunctionPointerHolder<FunctionType>* >( pFunctionPointerHolder );
    
    pDowncastFunctionPointerHolder->m_pPointerToFunction( param1, param2, param3 );
}


// ... we'll need to add more "CallFunction" functions if we need to support more parameters.



///////////////////////////////
// GameObjectFunctionIds.h
///////////////////////////////
enum GameObjectFunctionId
{
    GOF_SAMPLE_GAMEOBJECT_FUNCTION_TYPE1,   // params: bool bCanRideHorses, int iNumberOfSongsSungYesterday
    GOF_SAMPLE_GAMEOBJECT_FUNCTION_TYPE2,   // params: float fDeltaNewtonsPerMillenium
    GOF_GET_NUM_COWS                        // params: int* piReturnNumCows
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
    pComponent->RegisterCallbackFunctions();
}


template < typename FunctionType >
void GameObject::RegisterCallbackFunction( GameObjectFunctionId eFunctionId, Component* pComponentThatOwnsFunction, FunctionType pCallbackFunction )
{
    BaseFunctionPointerHolder* pFunctionPointerHolder       = FunctionPointerHolderFactory::CreateFunctionPointerHolder( pCallbackFunction );
    ComponentAndCallbackPair newComponentAndCallbackPair   = std::make_pair( pComponentThatOwnsFunction, pFunctionPointerHolder );
 
    MapOfFunctionIdsToFunctions::iterator mapIterWithFunctionIdAsKey  = m_mapOfFunctionIdsToFunctions.find( eFunctionId );


    if( mapIterWithFunctionIdAsKey == m_mapOfFunctionIdsToFunctions.end() )
    {
        VectorOfPairsOfComponentsAndCallbacks newVectorOfPairsOfComponentAndCallbacks;
        newVectorOfPairsOfComponentAndCallbacks.push_back( newComponentAndCallbackPair );
        m_mapOfFunctionIdsToFunctions[ eFunctionId ]    = newVectorOfPairsOfComponentAndCallbacks;
    }
    else
    {
        VectorOfPairsOfComponentsAndCallbacks& rVector  = mapIterWithFunctionIdAsKey->second;
        rVector.push_back( newComponentAndCallbackPair );
    }
}


void GameObject::Call( GameObjectFunctionId eFunctionId )
{
    MapOfFunctionIdsToFunctions::iterator mapIterWithFunctionIdAsKey  = m_mapOfFunctionIdsToFunctions.find( eFunctionId );
    
    if( mapIterWithFunctionIdAsKey != m_mapOfFunctionIdsToFunctions.end() )
    {
        VectorOfPairsOfComponentsAndCallbacks& rVector  = mapIterWithFunctionIdAsKey->second;
        
        for(    VectorOfPairsOfComponentsAndCallbacks::iterator vectorIterator = rVector.begin();
                vectorIterator != rVector.end();
                ++vectorIterator )
        {
            
            ComponentAndCallbackPair& rComponentAndCallbackPair = *vectorIterator;
            
            Component*                  pComponent              = rComponentAndCallbackPair.first;
            BaseFunctionPointerHolder*  pFunctionPointerHolder  = rComponentAndCallbackPair.second;
            
            CallFunction( pFunctionPointerHolder, pComponent );
            
        }
    }
}


template< typename ParamType1 >
void GameObject::Call( GameObjectFunctionId eFunctionId, ParamType1 param1 )
{
    MapOfFunctionIdsToFunctions::iterator mapIterWithFunctionIdAsKey  = m_mapOfFunctionIdsToFunctions.find( eFunctionId );
    
    if( mapIterWithFunctionIdAsKey != m_mapOfFunctionIdsToFunctions.end() )
    {
        VectorOfPairsOfComponentsAndCallbacks& rVector  = mapIterWithFunctionIdAsKey->second;
        
        for(    VectorOfPairsOfComponentsAndCallbacks::iterator vectorIterator = rVector.begin();
                vectorIterator != rVector.end();
                ++vectorIterator )
        {
            
            ComponentAndCallbackPair& rComponentAndCallbackPair = *vectorIterator;
            
            Component*                  pComponent              = rComponentAndCallbackPair.first;
            BaseFunctionPointerHolder*  pFunctionPointerHolder  = rComponentAndCallbackPair.second;
            
            CallFunction( pFunctionPointerHolder, pComponent, param1 );            
        }
    }
}


template< typename ParamType1, typename ParamType2 >
void GameObject::Call( GameObjectFunctionId eFunctionId, ParamType1 param1, ParamType2 param2 )
{
    MapOfFunctionIdsToFunctions::iterator mapIterWithFunctionIdAsKey  = m_mapOfFunctionIdsToFunctions.find( eFunctionId );
    
    if( mapIterWithFunctionIdAsKey != m_mapOfFunctionIdsToFunctions.end() )
    {
        VectorOfPairsOfComponentsAndCallbacks& rVector  = mapIterWithFunctionIdAsKey->second;
        
        for(    VectorOfPairsOfComponentsAndCallbacks::iterator vectorIterator = rVector.begin();
                vectorIterator != rVector.end();
                ++vectorIterator )
        {
            
            ComponentAndCallbackPair& rComponentAndCallbackPair = *vectorIterator;
            
            Component*                  pComponent              = rComponentAndCallbackPair.first;
            BaseFunctionPointerHolder*  pFunctionPointerHolder  = rComponentAndCallbackPair.second;
            
            CallFunction( pFunctionPointerHolder, pComponent, param1, param2 );
        }
    }
}


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
    static void ImplementationOfSampleFunctionId1( Component* pThis, bool bCanRideHorses, int iNumberOfSongsSungYesterday )
    {
        std::cout << "SampleComponent1::ImplementationOfSampleFunctionId1() called. bCanRideHorses: \"" << bCanRideHorses << "\". iNumberOfSongsSungYesterday: \"" << iNumberOfSongsSungYesterday << "\".\n\n";
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
    static void ImplementationOfSampleFunctionId1( Component* pBaseThis, bool bCanRideHorses, int iNumberOfSongsSungYesterday )
    {
        SampleComponent2* pThis = static_cast<SampleComponent2*>( pBaseThis );
        
        std::cout << "SampleComponent2::ImplementationOfSampleFunctionId1() called. bCanRideHorses: \"" << bCanRideHorses << "\". iNumberOfSongsSungYesterday: \"" << iNumberOfSongsSungYesterday << "\".\n";
        std::cout << "This instance of SampleComponent2 has \"" << pThis->m_iNumCows << "\" cows.\n\n";
    }
    
    
    static void ImplementationOfSampleFunctionId2( Component* pBaseThis, float fDeltaNewtonsPerMillenium )
    {
        SampleComponent2* pThis = static_cast<SampleComponent2*>( pBaseThis );
        
        std::cout << "SampleComponent2::ImplementationOfSampleFunctionId2() called. fDeltaNewtonsPerMillenium: \"" << fDeltaNewtonsPerMillenium << "\".\n";
        std::cout << "This instance of SampleComponent2 has \"" << pThis->m_iNumCows << "\" cows.\n\n";
    }
    
    
    static void GetNumCows( Component* pBaseThis, int* piReturnNumCows )
    {
        SampleComponent2* pThis = static_cast<SampleComponent2*>( pBaseThis );
        
        *piReturnNumCows    = pThis->m_iNumCows;
    }
    

    int m_iNumCows;
};



///////////////////////////////
// Main.cpp
///////////////////////////////


int main()
{
    std::cout << "Hello world." << "\n\n";


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
    pSampleGameObject->Call( GOF_SAMPLE_GAMEOBJECT_FUNCTION_TYPE2, 22.5f );
    
    // Demonstration of a function that returns 
    int iNumCowsInSampleGameObject  = -1;
    pSampleGameObject->Call( GOF_GET_NUM_COWS, &iNumCowsInSampleGameObject );
    std::cout << "Sample game object has " << iNumCowsInSampleGameObject << " cows.";
    
/*    
    // This will throw an exception due to a param type mismatch:
    float fNumCowsInSampleGameObject  = -1.0f;
    pSampleGameObject->Call( GOF_GET_NUM_COWS, &fNumCowsInSampleGameObject );
*/    


/*
    // This will throw an exception due to a param number mismatch:
    pSampleGameObject->Call( GOF_GET_NUM_COWS, &iNumCowsInSampleGameObject, true );
*/    

}
