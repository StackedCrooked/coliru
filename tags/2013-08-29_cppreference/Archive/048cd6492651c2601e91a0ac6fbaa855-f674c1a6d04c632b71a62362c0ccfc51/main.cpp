#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

int main()
{
    std::map<std::string, int> mymap = { { "key1", 10  },
                                         { "key2", 3   },
                                         { "key3", 230 },
                                         { "key4", 15  },
                                         { "key5", 1   },
                                         { "key6", 66  },
                                         { "key7", 10  } };

    std::vector<std::pair<std::string, int>> top_four(4);
    std::partial_sort_copy(mymap.begin(),
                           mymap.end(),
                           top_four.begin(),
                           top_four.end(),
                           [](std::pair<const std::string, int> const& l,
                              std::pair<const std::string, int> const& r)
                           {
                               return l.second > r.second;
                           });

    for (auto const& p: top_four)
    {
        std::cout << "{ " << p.first << ", " << p.second << "}\n";
    }

    return 0;
}
