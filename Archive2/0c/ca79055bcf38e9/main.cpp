#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
#include <algorithm>

template<class T>
struct comma_sep {
    T t;
    operator const T&() const {return t;}
};
template<class T>
std::istream& operator>>(std::istream& in, comma_sep<T>& t) 
{
    if (!(in >> t.t)) //if we failed to read the thingy
        return in; //return failure state
    int c = in.peek(); //peek at next character
    if (c==',') //if it's a comma
        in.get(); //extract it from the stream and we're done
    else //if the next character is anything else
        in.clear(); //clear the EOF state, read was successful
    return in; //return 
}

int main() {
    typedef std::istream_iterator<comma_sep<int>> istrit;
    typedef std::ostream_iterator<int> ostrit;
    
    std::istringstream in("1,2,3,4,5");
    std::vector<int> vec = std::vector<int>(istrit(in), istrit());
    std::copy(vec.begin(), vec.end(), ostrit(std::cout, ","));
    return 0;
}