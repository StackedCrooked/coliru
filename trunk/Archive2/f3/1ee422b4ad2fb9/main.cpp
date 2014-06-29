#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

namespace SmartWay
{
    typedef vector< string >     Names;
    typedef shared_ptr< Names >  SharedNames;
    
    template< typename T >
    bool IsInvalid( const T& value )
    {
        if( value )
            return false;
        cerr << "SmartWays: Vorsicht ein Pointer ist ungültig!" << endl;
        return true;
    }
    
    SharedNames GetNames()
    {
        SharedNames names = make_shared< Names >();
        names->push_back( "Timey" );
        names->push_back( "Markus" );
        names->push_back( "Roland" );
        names->push_back( "Alex" );
        return names;
    }
    
    void SortNames( SharedNames& names )
    {
        if( IsInvalid( names ) )
            return;
        sort( names->begin(), names->end() );
    }
    
    void OutputNames( const SharedNames& names )
    {
        if( IsInvalid( names ) )
           return;
        for( auto name : *names )
            cout << '\t' << name << endl;
    }
    
    void Test()
    {
        cout << endl << "Smart way" << endl;    
        auto names = GetNames();
        cout << "Unsorted names:" << endl;
        OutputNames( names );
        cout << endl;    
        
        names.reset();  //- Weil ich kann!!! :D
        
        cout << "Sorted names:" << endl;
        SortNames( names );
        OutputNames( names );      
    }
}

namespace OldWay
{
    typedef vector< string > Names;
    
    Names* GetNames()
    {
        Names* names = new Names();
        names->push_back( "Timey" );
        names->push_back( "Markus" );
        names->push_back( "Roland" );
        names->push_back( "Alex" );
        return names;
    }
    
    void SortNames( Names* names )
    {
        sort( names->begin(), names->end() );
    }
    
    void OutputNames( const Names* names )
    {
        for( auto name = names->cbegin(); name != names->cend(); name++ )
            cout << '\t' << *name << endl;
    }
    
    void Test()
    {
        cout << endl << "Old way" << endl;
        auto names = GetNames();
        cout << "Unsorted names:" << endl;
        OutputNames( names );
        cout << endl;    
        
        delete names;   //- Weil ich kann!! :D
        
        cout << "Sorted names:" << endl;
        SortNames( names );
        OutputNames( names );

        delete names;
    }
}

int main()
{
    SmartWay::Test();
    OldWay::Test();
}
