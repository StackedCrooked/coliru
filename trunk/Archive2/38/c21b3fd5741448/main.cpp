 #include <iostream>
 #include <vector>
 #include <algorithm>
 #include <memory>
 
using namespace std;

template<class InputIt, class OutputIt, class UnaryPredicate>
OutputIt move_if(InputIt first, InputIt last, 
                 OutputIt d_first, UnaryPredicate pred)
{
    while (first != last) {
        if (pred(*first))
            *d_first++ = std::move(*first);
        first++;
    }
    return d_first;
}

int main() {

std::vector<std::unique_ptr<int>> v1;
v1.push_back(std::unique_ptr<int>(new int(1)));
v1.push_back(std::unique_ptr<int>(new int(2)));
v1.push_back(std::unique_ptr<int>(new int(3)));
v1.push_back(std::unique_ptr<int>(new int(4)));

std::vector<std::unique_ptr<int>> v2;

move_if(begin(v1), end(v1), std::back_inserter(v2), [](std::unique_ptr<int>& p) { return *p % 2 == 0; });
 
for(auto& p : v2)
   std::cout << *p << std::endl;
}