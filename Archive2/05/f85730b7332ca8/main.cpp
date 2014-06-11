#include <iostream>
#include <iterator>
#include <tuple>
#include <boost/iterator/function_input_iterator.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/iterator_range.hpp>

using boost::make_function_input_iterator;

template <class Function, class BeginInput, class EndInput>
auto make_generator(Function &&f, BeginInput &&begin_state,
                    EndInput &&end_state)
    -> decltype(boost::make_iterator_range(
          make_function_input_iterator(std::forward<Function>(f),
                                       std::forward<BeginInput>(begin_state)),
          make_function_input_iterator(std::forward<Function>(f),
                                       std::forward<EndInput>(end_state)))) {
    return boost::make_iterator_range(
        make_function_input_iterator(std::forward<Function>(f),
                                     std::forward<BeginInput>(begin_state)),
        make_function_input_iterator(std::forward<Function>(f),
                                     std::forward<EndInput>(end_state)));
}

template <class Function>
auto make_generator(Function &&f)
    -> decltype(make_generator(std::forward<Function>(f), boost::infinite(),
                               boost::infinite())) {
    return make_generator(std::forward<Function>(f), boost::infinite(),
                          boost::infinite());
}

class Fibonacci {
    int f0 = 0;
    int f1 = 1;

  public:
    Fibonacci() = default;

    typedef int result_type;
    result_type operator()() {
        std::tie(f0, f1) = std::make_tuple(f1, f0 + f1);
        return f0;
    }
};

int main() {
    using std::cout;
    using std::endl;
    auto out = std::ostream_iterator<int>(cout, ", ");

    {
        cout << " -- Iterators:" << endl;
        Fibonacci fib;
        auto first = make_function_input_iterator(fib, 0);
        auto last = make_function_input_iterator(fib, 10);
        std::copy(first, last, out);
        cout << endl;
    }

    {
        cout << " -- Range:" << endl;
        Fibonacci fib;
        boost::copy(make_generator(fib, 0, 10), out);
        cout << endl;
    }

    {
        cout << " -- Infinte range:" << endl;
        Fibonacci fib;
        int count = 0;
        for (auto f : make_generator(fib)) {
            cout << f << ", ";
            count++;
            if (count > 9)
                break;
        }
        cout << endl;
    }
}