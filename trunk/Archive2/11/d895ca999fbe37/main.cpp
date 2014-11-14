#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

class spObj {
    int r;
  public:
    spObj(int arg = 0) : r(arg) {}

    friend std::ostream& operator<<(std::ostream& os, spObj const& v) {
        return os << "spObj[" << v.r << "]";
    }
};

template <typename It, typename Out, typename Pred>
   Out copy_until(It& first, It last, Out out, Pred pred) 
{
    while (first!=last && pred())
        *out++ = *first++;
    return out;
}

int main() {
    std::istringstream result_set("1 7 88 102 -43 9 3 3 3 3 3 3 3 3 3 3 3"); // fictious database result
    std::istream_iterator<int> result_reader(result_set), sentinel;

    std::vector<spObj> container;
    copy_until(result_reader, sentinel, std::back_inserter(container), [&] { return container.size() < 5; });

    for (spObj const& record : container)
        std::cout << record << "\n";
}
