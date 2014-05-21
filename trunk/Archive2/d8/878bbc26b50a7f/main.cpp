#include <boost/concept/requires.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept_check.hpp>

#include <type_traits>
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

namespace Silvasi {
    using namespace boost;

    template <typename T>
    void implicitlyBoolConvertible(const T& declvalT) {
        bool unused = declvalT; // attempt to trigger an implicit conversion
        (void) unused;
    }

    template <typename T>
    struct Equality_comparable {
        BOOST_CONCEPT_USAGE(Equality_comparable) {
            implicitlyBoolConvertible(a == b);
            implicitlyBoolConvertible(a != b);
        }
    private:
        T a, b;
    };

    template <typename T>
    struct Ordered : Equality_comparable<T> {
        BOOST_CONCEPT_USAGE(Ordered) {
            implicitlyBoolConvertible(a < b);
            implicitlyBoolConvertible(a > b);
            implicitlyBoolConvertible(a <= b);
            implicitlyBoolConvertible(a >= b);
        }
    private:
        T a, b;
    };

    struct Doubloon {
        Doubloon() = default;
        Doubloon(const Doubloon&) = default;
        Doubloon(Doubloon&&) = default;
        Doubloon& operator=(Doubloon&&) = default;
        Doubloon& operator=(const Doubloon&) = default;

        Doubloon(int numDoubloons) : numDoubloons(numDoubloons) {}

        friend bool operator==(const Doubloon& lhs, const Doubloon& rhs) {
            return lhs.numDoubloons == rhs.numDoubloons;
        }

        friend bool operator!=(const Doubloon& lhs, const Doubloon& rhs) {
            return !(lhs == rhs);
        }

        friend bool operator<(const Doubloon& lhs, const Doubloon& rhs) {
            return lhs.numDoubloons < rhs.numDoubloons;
        }

        friend bool operator>(const Doubloon& lhs, const Doubloon& rhs) {
            return lhs.numDoubloons > rhs.numDoubloons;
        }

        friend bool operator<=(const Doubloon& lhs, const Doubloon& rhs) {
            return !(lhs > rhs);
        }

        friend bool operator>=(const Doubloon& lhs, const Doubloon& rhs) {
            return !(lhs < rhs);
        }

        friend std::ostream& operator<<(std::ostream& os, const Doubloon& val) {
            os << val.numDoubloons;
            return os;
        }

        int numDoubloons;
    };

    template <typename I, typename T>
    bool contains(I first, I last, const T& value) {
        BOOST_CONCEPT_ASSERT((Equality_comparable<T>));
        BOOST_CONCEPT_ASSERT((ForwardIterator<I>));
        BOOST_CONCEPT_ASSERT((Convertible<T, typename ForwardIterator<I>::value_type>));
        while (first != last && *first != value) ++first;
        return first != last;
    }

    template <typename I>
    BOOST_CONCEPT_REQUIRES(
        ((Mutable_RandomAccessIterator<I>))
        ((LessThanComparable<typename Mutable_RandomAccessIterator<I>::value_type>)),
        (void))
        sort(I begin, I end) {
            std::sort(begin, end); // std::sort -> void
    }
} // ::Silvasi

int main() {
    std::cout << "Testing Silvasi::contains()\n";

    Silvasi::Doubloon ints[] = { { 1 }, { 4 }, { -1 } };
    Silvasi::contains(std::begin(ints), std::end(ints), Silvasi::Doubloon{ 4 });

    std::cout << "Passed: Type is Equality Comparable.\n"
              << "Passed: Iterator is at least a Forward Iterator\n"
              << "Passed: The type of the value is compatible with the associated type of the iterator." << std::endl;

    std::cout << "\nTesting Silvasi::sort()\n";
    std::vector<Silvasi::Doubloon> doubloons = { { 1 }, { 5 }, { -5 } };
    Silvasi::sort(std::begin(doubloons), std::end(doubloons));

    std::cout << "Passed: Iterator as at least a Random Access Iterator and it's not const.\n"
              << "Passed: The associated value_type of the Iterator is Less Than Comparable (sufficient to impose order on the set).\n"
              << "Passed: The return type of the function is void." << std::endl;
}