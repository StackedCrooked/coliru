#include <boost/tr1/functional.hpp>
#include <boost/ref.hpp>
#include <boost/utility/result_of.hpp>
#include <iterator>
#include <memory>
#include <vector>

class SomeClass
{
    //implementation unimportant
	//this is a standin for the dbconnection
};
//---------------------------------------------------------------------------

struct SomeStruct
{
	//implementation unimportant
};
//---------------------------------------------------------------------------

//bare minimum class to show that the private members of the class
//can be bound to the private member_function's parameters, so that Populate
//can pass its parameters to member_function.
//this should show that member_function's signature could be templated
//to accept any function type. The public function (Populate, here) would have
//a dependent signature. I'm not sure if it could be deduced from the other
//signature or if we would need to specify it separately.

//template<typename F, 0>
//class VariantParameterFunction
//{
//private:
//    boost:function<F> the_function;
//public:
//    template<typename S>
//    VariantParameterFunction(boost::function<S> assigned_function)
//}

template <typename S, typename T, typename Iter>
class TwiceBoundFunction
{
private:
    boost::function<S> func_;
    T cls_;
    Iter iter_;

public:
    TwiceBoundFunction(boost::function<S> func, T cls, Iter iter)
    : func_(func), cls_(cls), iter_(iter)
    { };

    // one for each # of args
    typename boost::result_of<
        boost::function<S>(T, Iter)
    >::type operator() const
    {
        return func_(cls_, iter_);
    }

    template <typename A>
    typename boost::result_of<
        boost::function<S>(T, Iter, A)
    >::type operator(typename A a) const
    {
        return func_(cls_, iter_, a);
    }

    template <typename A, typename B>
    typename boost::result_of<
        boost::function<S>(T, Iter, A, B)
    >::type operator(typename A a, typename B b) const
    {
        return func_(cls_, iter_, a, b);
    }

    // etc.
};

template<typename T, typename F = void (SomeClass*, std::back_insert_iterator<std::vector<T> >, double)>
class MyFunctionObjectClass
{
private:
	boost::function<F> member_function;
	std::auto_ptr<SomeClass> pSomeClass;
	std::vector<T> cStructs;
public:
	TwiceBoundFunction<F, SomeClass*, std::back_insert_iterator<std::vector<T> > > Operate;

	MyFunctionObjectClass(boost::function<F> member_)
        : member_function(member_),
          pSomeClass(new SomeClass()),
          Operate(member_function, pSomeClass.get(), std::back_inserter(cStructs))
    {
    }

	std::size_t Size()
    {
        return cStructs.size();
    }
};

//---------------------------------------------------------------------------

void FreeFunctionOne(SomeClass* psc, std::back_insert_iterator<std::vector<SomeStruct> > inserter, double val)
{
    if (psc)
	{
		while((int)val > 0)
		{
			inserter = SomeStruct();
			--val;
        }
    }
}

int main()
{
    MyFunctionObjectClass<SomeStruct, void (SomeClass*, std::back_insert_iterator<std::vector<SomeStruct> > inserter, double val)> mfo(FreeFunctionOne);
    return 0;
}