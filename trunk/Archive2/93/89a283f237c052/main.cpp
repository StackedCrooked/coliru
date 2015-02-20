#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

int main()
{
    std::vector<std::string> paths = {
        "/abc/sub",
        "/abc",
        "/xxx/yyy/zzz",
        "/xxx/yyy/zzz/iii/foobar",
        "/www/zzz",
        "/www/zzz/ppp",
        "/www/xxx",
    };
    
    // sort the paths
    std::sort(paths.begin(), paths.end());
    
    // predicate that returns true if second argument starts with the first
    auto pred = [](std::string const& l, std::string const& r) {
        return r.find(l) == 0;
    };
    
    // use adjacent_find to remove paths that contain others as substrings
    auto it = paths.begin();
    while((it = std::adjacent_find(it, paths.end(), pred)) != paths.end()) {
        paths.erase(std::next(it));
    }

    for(auto const& p : paths) {
        std::cout << p << '\n';
    }
}
