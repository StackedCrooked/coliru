#include <iostream>
#include <sstream>
#include <vector>

    void read_data(std::istream& input, std::vector<std::string>& strings, std::vector<double>& doubles, std::vector<int>& ints) {
      std::string s; double d; int i;
      while( input >> s >> d >> i ) {
        strings.push_back(s);
        doubles.push_back(d);
        ints.push_back(i);
      }
    }

    int main() {
      std::istringstream i { "FN 3.2 22\nBB 3.48 48\nXX 2.03 172\n" };
      std::vector<std::string> strings;
      std::vector<double> doubles;
      std::vector<int> ints;

      read_data(i, strings, doubles, ints);
      std::cout << "strings:\n";
      for(auto s: strings) std::cout << "  " << s << "\n";
      std::cout << "doubles:\n";
      for(auto d: doubles) std::cout << "  " << d << "\n";
      std::cout << "ints:\n";
      for(auto i: ints) std::cout << "  " << i << "\n";
    }