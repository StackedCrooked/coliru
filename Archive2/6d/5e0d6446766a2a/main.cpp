class Text {
  class const_iterator;
public:
  
  const_iterator begin() const;
  const_iterator end() const;
};

class Text::const_iterator {};

Text::const_iterator Text::begin() const { return const_iterator(); }
Text::const_iterator Text::end() const { return const_iterator(); }

int main(void) {
 Text T;
 
 auto I = T.begin();
}