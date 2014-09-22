#include <vector>

template<class I, class O>
class TE {public: virtual ~TE() = 0;}; //This is an abstract class

template<class I, class O>
class TESO: protected TE<I, O> {public: ~TESO(){}};

template<class I, class O>
class TEMO: protected TE<I, O> {public: ~TEMO(){}};

template<typename I, typename O, template<typename, typename> class TE>
class TQ {
private:
    std::vector< TE<I,O> > TEs;
public:
};


TQ<int,bool, TESO> tq1;
TQ<int,bool, TEMO> tq2;

int main() {
}