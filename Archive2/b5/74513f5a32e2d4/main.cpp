class Text {
  class const_iterator;
public:
  
  const_iterator begin() const;
  const_iterator end() const;
};

class Text::const_iterator {    
  Text Current;
  
public:
  const_iterator(const Text &T) : Current(T) {}
};

Text::const_iterator Text::begin() const { return const_iterator(*this); }
Text::const_iterator Text::end() const { return const_iterator(*this); }

int main(void) {
 Text T;
 
 auto I = T.begin();
}