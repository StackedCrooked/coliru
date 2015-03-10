#include <iostream>

template <typename StreamType = std::ostream, StreamType& stream = std::cout>
class StringList {
    template <typename...> class AddStrings;
  public:
    template <typename... Args> void addStrings (Args&&... args) {AddStrings<Args...>()(args...);}
};

template <typename StreamType, StreamType& stream>
template <typename First, typename... Rest>
class StringList<StreamType, stream>::AddStrings<First, Rest...> : AddStrings<Rest...> {
public:
    void operator()(First&& first, Rest&&... rest) {
        // do whatever
        AddStrings<Rest...>::operator()(std::forward<Rest>(rest)...);
    }
};

template <typename StreamType, StreamType& stream>
template <>
class StringList<StreamType, stream>::AddStrings<> {
    friend class StringStreamList;
    void operator()() const {}  // End of recursion.
};

int main() {
    StringList<> stringList;
//  stringList.addStrings ("dog", "cat", "bird");
}