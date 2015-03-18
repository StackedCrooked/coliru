#include <iostream>
#include <vector>
#include <assert.h>

    void advance( std::vector<size_t>& indexes, std::vector<size_t> const& counts, size_t amt=1 ) {
      if (indexes.size() < counts.size())
        indexes.resize(counts.size());
      for (size_t i = 0; i < counts.size(); ++i ) {
        indexes[i]+=amt;
        if (indexes[i] < counts[i])
          return;
        assert(counts[i]!=0);
        amt = indexes[i]/counts[i];
        indexes[i] = indexes[i]%counts[i];
      }
      // past the end, don't advance:
      indexes = counts;
    }

    bool vector_ascending( std::vector<size_t> const& v ) {
      for (size_t i = 1; (i < v.size()); ++i) {
        if (v[i-1] < v[i]) {
          return false;
        }
      }
      return true;
    }
    void print_a_lot( std::vector<size_t> counts ) {
      for( std::vector<size_t> v(counts.size()); v < counts; advance(v,counts)) {
        // check validity
        if (!vector_ascending(v))
          continue;
        for (size_t x : v)
          std::cout << (x+1);
        std::cout << std::endl;
      }
    }
    
int main() {
    print_a_lot( {6,6,6} );
}