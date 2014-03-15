#include <string>
#include <algorithm>
#include <vector>

template <class T>
struct orderLexSpecial {

  bool operator()(std::pair<std::string, T> const& lhs, std::pair<std::string, T> const& rhs) {
    return compString(lhs.first, rhs.first) || 
      (!compString(rhs.first, lhs.first) && std::less<T>()(lhs.second, rhs.second))
    ;
  }


  bool compString(std::string const& lhs, std::string const& rhs) {
    auto posl = std::find(begin(keywords), end(keywords), lhs);
    auto posr = std::find(begin(keywords), end(keywords), rhs);
    
    return posl < posr ||
      (posl == end(keywords) && posr == end(keywords) && lhs<rhs)
    ;
  }
  
  const std::vector<std::string> keywords = {"name", "id"};
};

#include <iostream>

using namespace std;


int main() {
    typedef pair<std::string, int> sip;
    vector<sip> sips = { {"foo", 42}, {"name", 100}, {"id", 5000}, {"aaa", 96}, {"id", -2}  };
    std::sort(begin(sips), end(sips), orderLexSpecial<int>());
    
    for (auto& e : sips)
      cout << e.first << ": " << e.second << '\n';
}