#include <iostream>
#include <algorithm>
#include <vector>


int main()
{
    std::vector<int> foo;
    std::cout << "How many elements do you want to put in the vector?\n";
    int n;
    std::cin >> n;
	for(int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        foo.push_back(x);
	}
	if(not std::is_sorted(foo.begin(), foo.end()))
	    std::sort(foo.begin(), foo.end());
    std::cout << "Insert another element.\n";
    std::cin >> n;
    auto it = std::upper_bound(foo.cbegin(), foo.cend(), n); //1
    foo.insert(it, n); //2
    for(int i: foo)
        std::cout << i << ' ';
}
