#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <type_traits>
#include <boost/iterator/iterator_facade.hpp>

using namespace std;



////////////////////////////////////////////////////////////////////////////////
/// Utility
////////////////////////////////////////////////////////////////////////////////
// make_reverse_iterator
// Reference: http://en.cppreference.com/w/cpp/iterator/make_reverse_iterator
template< class Iterator >
std::reverse_iterator<Iterator> make_reverse_iterator( Iterator i )
{
    return std::reverse_iterator<Iterator>(i);
}

// is_const_iterator
// Reference: http://stackoverflow.com/a/5423637/554283
template<typename T>
struct is_const_pointer { static const bool value = false; };

template<typename T>
struct is_const_pointer<const T*> { static const bool value = true; };

template <typename TIterator>
struct is_const_iterator
{
    typedef typename std::iterator_traits<TIterator>::pointer pointer;
    static const bool value = is_const_pointer<pointer>::value;
};



////////////////////////////////////////////////////////////////////////////////
/// Vector Traits
////////////////////////////////////////////////////////////////////////////////
enum class vector_indexing_method { brackets, xyz, xyzw };
template<typename Vector> struct vector_traits {};

// Get vector traits from an iterator
template<typename Iterator>
using vector_traits_from_iterator = vector_traits<typename iterator_traits<Iterator>::value_type>;

// Get vector value_type from an iterator
template<typename Iterator>
struct vector_value_type {
    using base_value_type = typename vector_traits_from_iterator<Iterator>::value_type;
    using type = conditional_t<is_const_iterator<Iterator>::value, const base_value_type, base_value_type>;    
};
template<typename Iterator>
using vector_value_type_t = typename vector_value_type<Iterator>::type;



////////////////////////////////////////////////////////////////////////////////
/// Elementwise Iterator Base
////////////////////////////////////////////////////////////////////////////////
template<typename Iterator, vector_indexing_method>
struct elementwise_iterator_base {};

// Specialization for brackets
template<typename Iterator>
struct elementwise_iterator_base<Iterator, vector_indexing_method::brackets> {
    vector_value_type_t<Iterator>& dereference() const
    { return (*current)[element]; }
    
    Iterator current;
    int element;
};

// Specialization for xyz
template<typename Iterator>
struct elementwise_iterator_base<Iterator, vector_indexing_method::xyz> {
    vector_value_type_t<Iterator>& dereference() const {
        switch (element) {
        case 0: return current->x;
        case 1: return current->y;
        case 2: return current->z;
        default: assert(false); // Shouldn't be reached. Prevents compiler warnings.
        }
    }
    
    Iterator current;
	int element;
};

// Specialization for xyzw
template<typename Iterator>
struct elementwise_iterator_base<Iterator, vector_indexing_method::xyzw> {
    vector_value_type_t<Iterator>& dereference() const {
        switch (element) {
        case 0: return current->x;
        case 1: return current->y;
        case 2: return current->z;
        case 3: return current->w;
        default: assert(false); // Shouldn't be reached. Prevents compiler warnings.
        }
    }
    
    Iterator current;
    int element;
};



////////////////////////////////////////////////////////////////////////////////
/// Elementwise Iterator
////////////////////////////////////////////////////////////////////////////////
// Template class
template<typename Iterator, int N = vector_traits_from_iterator<Iterator>::num_elements>
class elementwise_iterator 
    : public boost::iterator_facade<
        elementwise_iterator<Iterator, N>,
        vector_value_type_t<Iterator>,
        typename iterator_traits<Iterator>::iterator_category>
    , public elementwise_iterator_base<Iterator, vector_traits_from_iterator<Iterator>::indexing_method>
{
public:
    static_assert(N <= vector_traits_from_iterator<Iterator>::num_elements, "elementwise_iterator: Exceeded vector's num_elements limit.");

    using difference_type = typename iterator_traits<Iterator>::difference_type;
    using base = elementwise_iterator_base<Iterator, vector_traits_from_iterator<Iterator>::indexing_method>;
    using base::current;
    using base::element;
    
    elementwise_iterator() : base{nullptr, 0} {}
	elementwise_iterator( Iterator current ) : base{current, 0} {}

private:
    friend class boost::iterator_core_access;
    
    bool equal( const elementwise_iterator& other ) const
    { return current == other.current && element == other.element; }
    
    void increment() {
    	element = (element + 1) % N;
		if (!element) ++current;
    }

    void decrement() {
        if (!element) {
            element = N;
            --current;
        }
        --element;
    }

    void advance( difference_type n )
    { 
        auto div = std::div(n, N);
        current += div.quot; element += div.rem;
    }

    difference_type distance_to( const elementwise_iterator& other ) const
    { return (other.current - current) * N - (other.element - element); }
};

// Utility functions
template<typename Iterator>
auto elementwise( Iterator iterator )
{ return elementwise_iterator<Iterator>{iterator}; }

template<int N, typename Iterator>
auto elementwise( Iterator iterator )
{ return elementwise_iterator<Iterator, N>{iterator}; }



////////////////////////////////////////////////////////////////////////////////
/// Assorted Vector Classes
////////////////////////////////////////////////////////////////////////////////
// Using C arrays for storage
class vector_brackets_3 {
	float data[3];
public:
    vector_brackets_3( float x = 0.0, float y = 0.0, float z = 0.0 ) : data{x, y, z} {}
    
	float& operator[]( int i ) { return data[i]; }
	const float& operator[]( int i ) const { return data[i]; }
};

// Using XYZ members for storage
struct vector_xyz {
	float x, y, z;
};

// Using XYZW members for storage
struct vector_xyzw {
    float x, y, z, w;
};

// Using just a plain C array
using vector_carray = double[4];



////////////////////////////////////////////////////////////////////////////////
/// Vector Traits Specializations
////////////////////////////////////////////////////////////////////////////////
template<>
struct vector_traits<vector_brackets_3> {
    using value_type = float;
    const static vector_indexing_method indexing_method{vector_indexing_method::brackets};
    const static int num_elements{3};
};

template<>
struct vector_traits<vector_xyz> {
    using value_type = float;
    const static vector_indexing_method indexing_method{vector_indexing_method::xyz};
    const static int num_elements{3};
};

template<>
struct vector_traits<vector_xyzw> {
    using value_type = float;
    const static vector_indexing_method indexing_method{vector_indexing_method::xyzw};
    const static int num_elements{4};
};

template<>
struct vector_traits<vector_carray> {
    using value_type = double;
    const static vector_indexing_method indexing_method{vector_indexing_method::brackets};
    const static int num_elements{4};
};



////////////////////////////////////////////////////////////////////////////////
/// Code Sample
////////////////////////////////////////////////////////////////////////////////    
template<typename T>
using container = std::vector<T>; // You can try with std::list as well.

int main() {
    auto out = ostream_iterator<float>{cout, ", "};
    
    container<vector_brackets_3> coordinates1{{0.3, 0.2, 0.1}, {1.9, 1.8, 1.7}, {2.4, 2.5, 2.6}};
	container<vector_xyz> coordinates2{{0.3, 0.2, 0.1}, {1.9, 1.8, 1.7}, {2.4, 2.5, 2.6}};
    container<vector_xyzw> coordinates3{{0.3, 0.2, 0.1, 0.0}, {1.9, 1.8, 1.7, 1.6}, {2.4, 2.5, 2.6, 2.7}};
    container<vector_carray> coordinates4(3);
        coordinates4[0][0] = 0.3;
        coordinates4[0][1] = 0.2;
        coordinates4[0][2] = 0.1;
        coordinates4[0][3] = 0.0;
        coordinates4[1][0] = 1.9;
        coordinates4[1][1] = 1.8;
        coordinates4[1][2] = 1.7;
        coordinates4[1][3] = 1.6;
        coordinates4[2][0] = 2.4;
        coordinates4[2][1] = 2.5;
        coordinates4[2][2] = 2.6;
        coordinates4[2][3] = 2.7;

    cout << "Elementwise print of all elements:" << endl;
    copy(elementwise(begin(coordinates1)), elementwise(end(coordinates1)), out);
    cout << endl;
    copy(elementwise(begin(coordinates2)), elementwise(end(coordinates2)), out);
    cout << endl;
    copy(elementwise(begin(coordinates3)), elementwise(end(coordinates3)), out);
    cout << endl;
    copy(elementwise(begin(coordinates4)), elementwise(end(coordinates4)), out);
    cout << endl;

    cout << "Elementwise print of the first two elements:" << endl;
    copy(elementwise<2>(begin(coordinates1)), elementwise<2>(end(coordinates1)), out);
    cout << endl;
    copy(elementwise<2>(begin(coordinates2)), elementwise<2>(end(coordinates2)), out);
    cout << endl;
    copy(elementwise<2>(begin(coordinates3)), elementwise<2>(end(coordinates3)), out);
    cout << endl;
    copy(elementwise<2>(begin(coordinates4)), elementwise<2>(end(coordinates4)), out);
    cout << endl;

    cout << "Const elementwise print:" << endl;
    copy(elementwise(coordinates1.cbegin()), elementwise(coordinates1.cend()), out);
    cout << endl;
    copy(elementwise(coordinates2.cbegin()), elementwise(coordinates2.cend()), out);
    cout << endl;
    copy(elementwise(coordinates3.cbegin()), elementwise(coordinates3.cend()), out);
    cout << endl;
    copy(elementwise(coordinates4.cbegin()), elementwise(coordinates4.cend()), out);
    cout << endl;

    cout << "Reverse elementwise print (inner):" << endl;
    copy(elementwise(coordinates1.rbegin()), elementwise(coordinates1.rend()), out);
    cout << endl;
    copy(elementwise(coordinates2.rbegin()), elementwise(coordinates2.rend()), out);
    cout << endl;
    copy(elementwise(coordinates3.rbegin()), elementwise(coordinates3.rend()), out);
    cout << endl;
    copy(elementwise(coordinates4.rbegin()), elementwise(coordinates4.rend()), out);
    cout << endl;
    
    cout << "Reverse elementwise print (outer):" << endl;
    copy(make_reverse_iterator(elementwise(end(coordinates1))), make_reverse_iterator(elementwise(begin(coordinates1))), out);
    cout << endl;
    copy(make_reverse_iterator(elementwise(end(coordinates2))), make_reverse_iterator(elementwise(begin(coordinates2))), out);
    cout << endl;
    copy(make_reverse_iterator(elementwise(end(coordinates3))), make_reverse_iterator(elementwise(begin(coordinates3))), out);
    cout << endl;
    copy(make_reverse_iterator(elementwise(end(coordinates4))), make_reverse_iterator(elementwise(begin(coordinates4))), out);
    cout << endl;

    cout << "Elementwise transformation (*2):" << endl;
    auto multiplies_by_2 = [] ( auto& value ) { value *= 2.0; };
    for_each(elementwise(begin(coordinates1)), elementwise(end(coordinates1)), multiplies_by_2);
    copy(elementwise(begin(coordinates1)), elementwise(end(coordinates1)), out);
    cout << endl;
    for_each(elementwise(begin(coordinates2)), elementwise(end(coordinates2)), multiplies_by_2);
    copy(elementwise(begin(coordinates2)), elementwise(end(coordinates2)), out);
    cout << endl;
    for_each(elementwise(begin(coordinates3)), elementwise(end(coordinates3)), multiplies_by_2);
    copy(elementwise(begin(coordinates3)), elementwise(end(coordinates3)), out);
    cout << endl;
    for_each(elementwise(begin(coordinates4)), elementwise(end(coordinates4)), multiplies_by_2);
    copy(elementwise(begin(coordinates4)), elementwise(end(coordinates4)), out);
    cout << endl;
    
    // Causes an error since elementwise is based on a const_iterator.
    //for_each(elementwise(coordinates1.cbegin()), elementwise(coordinates1.cend()), [] ( auto& value ) { value *= 2.0; });
    
    // Causes an error since the vector type of coordinates1 does not contain 4 elements.
    //copy(elementwise<4>(begin(coordinates1)), elementwise<4>(end(coordinates1)), out);
}
