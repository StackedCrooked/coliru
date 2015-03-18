#include <iostream>
#include <vector>

    void advance( std::vector<size_t>& indexes, std::vector<size_t> const& counts ) {
      if (indexes.size() != counts.size())
        indexes.resize(counts.size());
      for (size_t i = 0; i < counts.size(); ++i ) {
        ++indexes[i];
        if (indexes[i] < counts[i])
          return;
        indexes[i] = 0;
      }
      // past the end, don't advance:
      indexes = counts;
    }

    void print_a_lot( std::vector<size_t> counts ) {
      for( std::vector<size_t> v(counts.size()); v < counts; advance(v,counts)) {
        for (size_t x : v)
          std::cout << x;
        std::cout << std::endl;
      }
    }
    
int main() {
    print_a_lot( {1,2,3,4} );
}