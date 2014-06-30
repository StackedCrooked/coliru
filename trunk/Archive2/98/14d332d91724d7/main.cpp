#include <iostream>
#include <string>
#include <vector>
#include <map>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

using namespace std;

namespace Aufgabe11
{
    template< typename O >
	class CountedPtr
	{
		struct CountedPtrData
		{
			O* 		pointer;
			size_t	useCount;

			CountedPtrData( O& object )
			: pointer( new O( object ) )
			, useCount( 1 )
			{}

			~CountedPtrData()
			{
				delete pointer;
			}
		};

		CountedPtrData* myUseData;

	public:
		CountedPtr( const CountedPtr< O >& object )
		: myUseData( object.myUseData )
		{
			myUseData->useCount++;
			cout << "CountedPtr( const CountedPtr< O >& object ): New useCount = " << myUseData->useCount << endl;
		}

		CountedPtr( O&& object )
		: myUseData( new CountedPtrData( object ) )
		{
			cout << "CountedPtr( O&& object ): New useCount = " << myUseData->useCount << endl;
		}

		~CountedPtr()
		{
			if( !myUseData )
			{
				cout << "Pointer has been moved." << endl;
				return;
			}
			cout << "~CountedPtr(): New useCount = " << myUseData->useCount - 1 << endl;
			if( --myUseData->useCount == 0 )
				delete myUseData;
		}

		O operator*()
		{
			return *myUseData->pointer;
		}

		O* operator->()
		{
			return myUseData->pointer;
		}

		size_t UseCount() const { return myUseData->useCount; }
	};

	class Dummy
	{
	public:
		Dummy( int v )
		: value( v )
		{
			cout << "Dummy()" << endl;
		}
		~Dummy()
		{
			cout << "~Dummy() " << value << endl;
		}

		int value;
	};

	typedef CountedPtr< Dummy > Dummy_x;
	Dummy_x GetDummy()
	{
		Dummy_x p1( Dummy( 1 ) );
		Dummy_x p2( Dummy( 2 ) );
		return p1;
	}
	void PrintDummy( Dummy_x& dummy )
	{
		cout << "p1->value = " << dummy->value << " UseCount = " << dummy.UseCount() << endl;
	}
	void UseDummy( Dummy_x dummy )
	{
		PrintDummy( dummy );
	}
	vector< Dummy_x > PackageDummy( Dummy_x& dummy )
	{
		vector< Dummy_x > dummies;
		int i = 0;
		cout << i++ << endl;
		dummies.push_back( dummy );
		cout << i++ << endl;
		dummies.push_back( dummy );
		cout << i++ << endl;
		dummies.push_back( dummy );
		cout << i++ << endl;
		dummies.push_back( dummy );
		cout << i++ << endl;
		dummies.push_back( dummy );
		cout << i++ << endl;
		dummies.push_back( dummy );
		cout << i++ << endl;
		dummies.push_back( dummy );
		cout << i++ << endl;
		dummies.push_back( dummy );
		cout << i++ << endl;
		dummies.push_back( dummy );
		cout << i++ << endl;
		return dummies;
	}

	void Execute()
	{
		auto dummy = GetDummy();
		PrintDummy( dummy );
		UseDummy( dummy );
		PrintDummy( dummy );

		cout << endl << "vector test" << endl;
		auto dummies = PackageDummy( dummy );
		PrintDummy( dummy );
		dummies.clear();
		PrintDummy( dummy );
	}
}

int main()
{
    Aufgabe11::Execute();
}
