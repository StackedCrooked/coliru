#include <tuple>
#include <utility>
#include <vector>
#include <iostream>
#include <ios>

namespace detail {
    
// the lambda is fully bound with one element from each of the ranges
template<class Op>
void insert_tuples(Op op)
{
        // evaluating the lambda will insert the currently bound tuple
        op();
}

// "peal off" the first range from the remaining tuple of ranges
template<class Op, class InputIterator1, class... InputIterator2>
void insert_tuples(Op op, std::pair<InputIterator1, InputIterator1> head, std::pair<InputIterator2, InputIterator2>... tail)
{
        // "peal off" the elements from the first of the remaining ranges
        // NOTE: the recursion will effectively generate the multiple nested for-loops
        for (auto it = head.first; it != head.second; ++it) {
                // bind the first free variable in the lambda, and
                // keep one free variable for each of the remaining ranges
                detail::insert_tuples(
                        [=](InputIterator2... elems) mutable { op(it, elems...); },
                        tail...
                );
        }
}

}       // namespace detail

// convert a tuple of ranges to the range of tuples representing the Cartesian product
template<class OutputIterator, class... InputIterator>
void cartesian_product(OutputIterator result, std::pair<InputIterator, InputIterator>... dimensions)
{
        detail::insert_tuples(
                 [=](InputIterator... elems) mutable { *result++ = std::make_tuple(*elems...); },
                 dimensions...
        );
}

int main() 
{
        bool b[] = { false, true };
        int i[] = { 0, 1 };
        std::string s[] = { "Hello", "World" };

        std::vector< std::tuple<bool, int, std::string> > cp = {
                std::make_tuple(false, 0, "Hello") ,
                std::make_tuple(false, 0, "World"),
                std::make_tuple(false, 1, "Hello"),
                std::make_tuple(false, 1, "World"),
                std::make_tuple(true,  0, "Hello"),
                std::make_tuple(true,  0, "World"),
                std::make_tuple(true,  1, "Hello"),
                std::make_tuple(true,  1, "World")
        };

        std::vector< std::tuple<bool, int, std::string> > result;
        cartesian_product(
                std::back_inserter(result),
                std::make_pair(std::begin(b), std::end(b)),
                std::make_pair(std::begin(i), std::end(i)),
                std::make_pair(std::begin(s), std::end(s))
        );
        
        std::cout << std::boolalpha << (result == cp);
}