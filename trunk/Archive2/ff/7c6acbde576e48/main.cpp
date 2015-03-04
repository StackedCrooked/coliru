#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
#include <algorithm>

template<class T, char sep=','>
struct comma_sep { //type used for temporary input
    T t; //where data is temporarily read to
    operator const T&() const {return t;} //acts like an int in most cases
};
template<class T, char sep>
std::istream& operator>>(std::istream& in, comma_sep<T,sep>& t) 
{
    if (!(in >> t.t)) //if we failed to read the int
        return in; //return failure state
    if (in.peek()==sep) //if next character is a comma
        in.ignore(); //extract it from the stream and we're done
    else //if the next character is anything else
        in.clear(); //clear the EOF state, read was successful
    return in; //return 
}

int main() {
    typedef std::istream_iterator<comma_sep<int>> istrit;
    typedef std::ostream_iterator<int> ostrit;
    
    std::vector<int> vec = std::vector<int>(istrit(std::cin), istrit());
    std::copy(vec.begin(), vec.end(), ostrit(std::cout, ","));
    return 0;
}