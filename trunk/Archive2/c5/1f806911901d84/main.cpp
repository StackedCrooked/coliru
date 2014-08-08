#include <cassert>
#include <iterator>
#include <string>
 
int main()
{
    std::string s{ "xmplr" };
 
    // insert(size_type index, size_type count, char ch)
    s.insert(0, 1, 'E');
    assert("Exmplr" == s);
 
    // insert(size_type index, char* s)
    s.insert(2, "e");
    assert("Exemplr" == s);
 
    // insert(size_type index, string const& str)
    s.insert(6, std::string("a"));
    assert("Exemplar" == s);
 
    // insert(size_type index, string const& str,
    //     size_type index_str, size_type count)
    s.insert(8, std::string(" is an example string."), 0, 14);
    assert("Exemplar is an example" == s);
 
    // insert(const_iterator pos, char ch)
    s.insert(s.cbegin() + s.find_first_of('n') + 1, ':');
    assert("Exemplar is an: example" == s);
 
    // insert(const_iterator pos, size_type count, char ch)
    s.insert(s.cbegin() + s.find_first_of(':') + 1, 2, '=');
    assert("Exemplar is an:== example" == s);
 
    // insert(const_iterator pos, InputIt first, InputIt last)
    {
        std::string const seq{ " string" };
        s.insert(s.begin() + s.find_last_of('e') + 1,
            std::begin(seq), std::end(seq));
        assert("Exemplar is an:== example string" == s);
    }
 
    // insert(const_iterator pos, std::initializer_list<char>)
    {
        std::initializer_list<char> const period = { '.' };
        s.insert(s.cbegin() + s.find_first_of('g') + 1, period);
        assert("Exemplar is an:== example string." == s);
    }
}