#include <iostream>

template <class BidirectionalIterator>
  void reverse (BidirectionalIterator first, BidirectionalIterator last)
{
  while ((first!=last)&&(first!=--last)) {
    std::iter_swap (first,last);
    ++first;
  }
}

void reverse(std::string& s)
{
    int i = 0;
    int j = s.size();
    while ((i != j) && (i != (--j))) 
    {
        std::swap(s[i], s[j]);
        ++i;
    }
}

void reverse(int n, std::string& s)
{
    int beg = 0;
    int end = beg + n;
    int size = s.size();
    std::string copy = s;
    s = "";
    for (int i = 0; i < size / n + 1; i++)
    {
        std::string chunk(copy.begin() + beg, copy.begin() + end);
        if (end < size)
            reverse(chunk);
        s += chunk;
        beg += n;
        end += n;
    }
}

int main()
{
    std::string s("ABC DEF GHI JK");
    std::string target("CBA FED IHG JK");

    reverse(3, s);
    std::cout << s << "|" << target <<"|\n";
    std::cout << std::boolalpha << (s == target);
    return 0;
}