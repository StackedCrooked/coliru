#include <iostream>
#include <sstream>

template<class cT>
void swap(std::basic_istream<cT>& lhs, std::basic_istream<cT>& rhs)
{
    std::basic_streambuf<cT>* sbuf = lhs.rdbuf();
    lhs.template basic_ios<cT>::rdbuf(rhs.rdbuf());
    rhs.template basic_ios<cT>::rdbuf(sbuf);
}

int main()
{
    std::istream copy(nullptr);
    swap(std::cin, copy);

    for (std::string word; copy >> word; ) {
        std::cout << word << ' ';
    }
}