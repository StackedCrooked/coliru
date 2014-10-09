#include <iostream>
#include <string>
#include <memory>

using namespace std;

namespace
{
    class Object
	{
		string content = "Bla123";
	public:
		Object()
		{}

		string Content() const
		{
			return content;
		}
	};
	typedef std::unique_ptr< Object > UniqueObjectPtr;

	UniqueObjectPtr CreateObject()
	{
		return UniqueObjectPtr( new Object() );
	}

	typedef std::shared_ptr< UniqueObjectPtr > SharedObjectHolder;


	class Pointer
	{
		Object* 			target;
		SharedObjectHolder 	resolver;

	public:
		Pointer( UniqueObjectPtr object )
		: target	( object.get() )
		, resolver	( new UniqueObjectPtr( std::move( object ) ) )
		{
		}

		Pointer( const Pointer& pointer )
		: target	( nullptr )
		, resolver	( pointer.resolver )
		{
			target = ( *resolver ).get();
		}

		Object* Deref()
		{
			if( !resolver || !( *resolver ) )
				return nullptr;
			if( !target )
				target = ( *resolver ).get();
			return target;
		}
		Object* operator->()
		{
			return Deref();
		}
        operator bool()
        {
            return Deref();
        }

		UniqueObjectPtr RetriveUniqueObjectPtr()
		{
			return std::move( *resolver );
		}
	};

	void Execute()
	{
		Pointer origin	( CreateObject() 	);
		Pointer pointer1( origin 			);
		Pointer pointer2( origin 			);

		cout << "origin = " 	<< ( origin 	? "true" : "false" ) << endl;
		cout << "pointer1 = " 	<< ( pointer1	? "true" : "false" ) << endl;
		cout << "pointer2 = " 	<< ( pointer2	? "true" : "false" ) << endl;
		cout << "pointer1->Content() = " << pointer1->Content() << endl;

        cout << endl << "Extracting UniqueObjectPtr away from Pointer's" << endl;
		auto extracted = pointer1.RetriveUniqueObjectPtr();

		cout << "origin = " 	<< ( origin 	? "true" : "false" ) << endl;
		cout << "pointer1 = " 	<< ( pointer1	? "true" : "false" ) << endl;
		cout << "pointer2 = " 	<< ( pointer2	? "true" : "false" ) << endl;

		cout << "extracted = " 	<< ( extracted	? "true" : "false" ) << endl;
		cout << "extracted->Content() = " << extracted->Content() << endl;
	}
}

int main(void) 
{
    Execute();
    return 0;
}
