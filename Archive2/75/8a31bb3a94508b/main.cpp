#include <vector>
#include <iostream>

class tableau {
  private:
    std::vector<std::vector<unsigned int> > rep;
  public:
    typedef std::vector<std::vector<unsigned int> >::iterator iterator;
    void push_back(std::vector<unsigned int> const& new_row) {
      rep.push_back(new_row);
    }
    iterator begin() { return rep.begin(); }
    iterator end()   { return rep.end();   }
};

int main() {
  tableau t1;
  std::vector<unsigned int> row1(10);
  std::vector<unsigned int> row2(8);

  t1.push_back(row1);
  t1.push_back(row2);

  tableau::iterator it = t1.begin();
  for ( ; it != t1.end(); ++it) {
    //display rows of tableau
  }
  return 0;
}