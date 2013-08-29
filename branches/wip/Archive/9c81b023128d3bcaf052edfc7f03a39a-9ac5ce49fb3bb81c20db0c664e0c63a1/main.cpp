    class A {
        public:
        template <class T> 
          bool isGood(int in) const {
          const T f;
          return in < f.value();
          }
    
    };
    
    class B {
        public:
        int value() const {return 10;}
    };
    
    template <class T>
    bool tryEvaluator(T& evaluator, int value) {
        return evaluator.isGood<B>(value);
        }


    int main( int argc, const char* argv[] ) {
      const A evaluator;
      tryEvaluator(evaluator,20);
      return 0;
      }