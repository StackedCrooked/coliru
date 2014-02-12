struct RGB {
    friend bool operator<(const RGB& lhs, const RGB& rhs);
    
};

bool operator<(const RGB& lhs, const RGB& rhs) {
    return true;
}

#include <vector>
#include <map>
int main()
{
    std::vector < std::map <RGB, int> > count;
    count.push_back(make_pair(RGB(), 0));
    std::vector < std::map <RGB, int> >::iterator it = count.begin();
    count[0].find(RGB());
}