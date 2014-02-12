#include <ostream> 
#include <iterator> 
#include <algorithm>
template <class T, 
          class charT=char, 
          class traits=std::char_traits<charT> > 
class infix_ostream_iterator : 
    public std::iterator<std::output_iterator_tag,void,void,void,void> 
{ 
    std::basic_ostream<charT,traits> *os; 
    charT const* delimiter; 
    bool first_elem; 
public: 
    typedef charT char_type; 
    typedef traits traits_type; 
    typedef std::basic_ostream<charT,traits> ostream_type; 
    infix_ostream_iterator(ostream_type& s) 
        : os(&s),delimiter(0), first_elem(true) 
    {} 
    infix_ostream_iterator(ostream_type& s, charT const *d, int len) 
        : os(&s),delimiter(d), first_elem(true), length(len)
    {} 
    
    std::string current_word = "";
    int length;
    int count = 0;
    infix_ostream_iterator<T,charT,traits>& operator=(T const &item) 
    {         
        count++;
        if (item == ' ')
        {
            std::reverse(current_word.begin(), current_word.end());
            *os << current_word;
            if (!first_elem && delimiter != 0)
                *os << delimiter;
            current_word = "";
        } else
            current_word += item;
            
        if (count == length) {
            std::reverse(current_word.begin(), current_word.end());
            *os << current_word;
        }

        first_elem = false; 
        return *this; 
    } 
    infix_ostream_iterator<T,charT,traits> &operator*() { 
        return *this; 
    } 
    infix_ostream_iterator<T,charT,traits> &operator++() { 
        return *this; 
    } 
    infix_ostream_iterator<T,charT,traits> &operator++(int) { 
        return *this; 
    } 
};     

#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
    std::string sen = "Go over there";
    std::copy(sen.begin(), sen.end(), infix_ostream_iterator<char>(std::cout, " ", sen.size()));
}