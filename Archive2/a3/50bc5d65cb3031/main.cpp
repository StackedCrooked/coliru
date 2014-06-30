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
        sort( names->begin(), names->end() );
    }
    
    void OutputNames( const SharedNames& names )
    {
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
        
        cout << "Sorted names:" << endl;
        SortNames( names );
        OutputNames( names );
        
        return;
        delete names;   //--- Ooops, memory leak !
    }
}

int main()
{
    SmartWay::Test();
    OldWay::Test();
}
