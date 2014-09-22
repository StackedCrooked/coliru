#include <vector>

template<class I, class O>
class TE {}; //This is an abstract class

template<class I, class O>
class TESO: protected TE<I, O> {};

template<class I, class O>
class TEMO: protected TE<I, O> {};

template<typename I, typename O, template<typename U, typename V> class TE>
class TQ {
private:
    std::vector< TE<I,O> > TEs;
public:
};


TQ<int,bool, TESO> tq1;
TQ<int,bool, TEMO> tq2;

int main() {
}