#include <vector>
#include <string>

class T {
    private:
        static const std::vector<std::string> tGroups;
        static const std::vector<std::vector<int> > fooGroups;
        static const std::vector<std::vector<std::string> > barGroups;
};

const std::vector<std::string> T::tGroups = {
    "blah","blah","blah","blah"
};

const std::vector<std::vector<int> > T::fooGroups = {
    //L0, L1, L2, ...
    {0,0,15},
    {0,0,6},
    {0,0,4}
};

const std::vector<std::vector<std::string> > T::barGroups = {
    {"blah","blah"},
    {"blah","blah","blah","blah"},
    {"blah","blah","blah"}
};

int main() {
  
   return 0;
}
