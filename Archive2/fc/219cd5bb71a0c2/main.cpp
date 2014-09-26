//An interesting little exercise in generating compile-time arrays.
//The process is fairly straightforward:
//  -Generate abstract list via template metaprogramming
//  -Extract values from list into pre-allocated array via helper classes

#include <iostream>
#include <array>

template <int val, typename list_tail = void>
struct ListCons {
    static const int value = val;
    
    typedef list_tail tail;
};

template <typename list, typename exfil_functor>
struct ListDataExfiltrator {
    ListDataExfiltrator(exfil_functor& fn, int start_index = 0) {
        fn(list::value, start_index);
        ListDataExfiltrator<typename list::tail, exfil_functor> descend_into_list{ fn, start_index + 1 };
    }
};
//Case for the end of the list.
template <typename exfil_functor>
struct ListDataExfiltrator<void, exfil_functor> {
    ListDataExfiltrator(exfil_functor& external_obj, int start_index = 0) {}
};

template <int curr_pos, int max_pos>
struct SquareBuilderHelper {
    typedef ListCons<curr_pos * curr_pos, typename SquareBuilderHelper<curr_pos + 1, max_pos>::type> type;
};
//Create a specialization for when we want to stop building the list.
template <int max_pos>
struct SquareBuilderHelper<max_pos, max_pos> {
    typedef ListCons<max_pos * max_pos> type;
};
template <int max_pos>
struct SquareBuilder {
    typedef typename SquareBuilderHelper<1, max_pos>::type type;
};

template <int num_elems>
class MyExfiltrator {
public:
    typedef std::array<int, num_elems> array_type;

    array_type data;
    
    void operator()(int elem_data, int index) {
        data[index] = elem_data;
    }
};

template <int num_elems>
class MyArrayBuilder {
    typedef MyExfiltrator<num_elems> exfil_type;
    typedef typename SquareBuilder<num_elems>::type num_list;
    
    exfil_type thingy;
    
public:
    MyArrayBuilder(void) {
        ListDataExfiltrator<num_list, exfil_type> woop{ thingy };
    }
    
    typename exfil_type::array_type data(void) const {
        return thingy.data;
    }
};

int main(void) {
    MyArrayBuilder<4> bloop;
    
    for (const auto& el : bloop.data()) {
        std::cout << el << '\n';
    }
    return 0;
}