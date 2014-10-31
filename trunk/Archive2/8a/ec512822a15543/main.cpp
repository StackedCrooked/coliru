#include <boost/multi_array.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <iostream>

namespace detail {
    namespace mpl = boost::mpl;

	template <typename T, size_t Mindim = 1, size_t Maxdim = 5>
	struct make_generic_array_storage
	{
		template <size_t N> using array_t = boost::multi_array<T, N>;
		template<typename N> struct to_array_f { typedef array_t<N::value> type; };

		using list = typename mpl::transform<
			mpl::range_c<size_t, Mindim, Maxdim>, 
			to_array_f<mpl::_1>,
			mpl::back_inserter<mpl::vector<> > 
		>::type;

		using type = typename boost::make_variant_over<list>::type;
	};
}

template <typename T>
struct GenericArray
{
	template <size_t N> using array_t = boost::multi_array<T, N>;

	template <typename Rhs> GenericArray& operator=(Rhs&& rhs) {
		_storage = std::forward<Rhs>(rhs);
		return *this;
	}

	template <size_t N> array_t<N>		& get()       { return boost::get<array_t<N> >(_storage); }
	template <size_t N> array_t<N> const& get() const { return boost::get<array_t<N> >(_storage); }

  private:
	typename detail::make_generic_array_storage<T>::type _storage;
};

int main()
{
    boost::multi_array<double, 2> array_2d; //2D array
    boost::multi_array<double, 3> array_3d; //4D array
    boost::multi_array<double, 4> array_4d; //5D array

	GenericArray<double> arr;
	arr = array_3d;

	try { auto& ref3 = arr.get<3>(); }
	catch (boost::bad_get const& e) { std::cout << "L:" << __LINE__ << " " << e.what() << "\n"; }

	try { auto& ref2 = arr.get<2>(); } // this fails
	catch (boost::bad_get const& e) { std::cout << "L:" << __LINE__ << " " << e.what() << "\n"; }

	arr = array_2d;

	try { auto& ref2 = arr.get<2>(); } // this succeeds
	catch (boost::bad_get const& e) { std::cout << "L:" << __LINE__ << " " << e.what() << "\n"; }
    
    std::cout << "Done";
}
