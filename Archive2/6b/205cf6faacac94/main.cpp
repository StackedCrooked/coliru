#include <boost/tr1/functional.hpp>
#include <iterator>
#include <memory>
#include <vector>

class SomeClass
{
    //implementation unimportant
	//this is a standin for the dbconnection
};
//---------------------------------------------------------------------------

class SomeStruct
{
	//implementation unimportant
	//this is a standin for our glorified structs (airways, waypoints, etc.)
};
//---------------------------------------------------------------------------

//bare minimum class to show that the private members of the class
//can be bound to the private member_function's parameters, so that Populate
//can pass its parameters to member_function.
//this should show that member_function's signature could be templated
//to accept any function type. The public function (Populate, here) would have
//a dependent signature. I'm not sure if it could be deduced from the other
//signature or if we would need to specify it separately.
class MyFunctionObjectClass
{
private:
	std::tr1::function<void (SomeClass*, std::back_insert_iterator<std::vector<SomeStruct> >&, double)> member_function;
	std::auto_ptr<SomeClass> pSomeClass;
	std::vector<SomeStruct> cStructs;
public:
	std::tr1::function<void (double)> Populate;

	MyFunctionObjectClass(std::tr1::function<void (SomeClass*, std::back_insert_iterator<std::vector<SomeStruct> >&, double)> member_);

	std::size_t Size();

	void AssignMemberFunction(std::tr1::function<void (SomeClass*, std::back_insert_iterator<std::vector<SomeStruct> >&, double)> member_);
};