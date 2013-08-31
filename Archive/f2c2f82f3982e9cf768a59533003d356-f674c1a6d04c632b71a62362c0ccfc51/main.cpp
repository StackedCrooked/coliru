#include <vector>

template <class R>
class AVectorContainner
{
public:
    AVectorContainner() {
        mVector= new std::vector<entry>;
    }
  typedef std::pair<int ,R *> entry;

  void insert(R* aPointer, int aID) {
     entry aEntry;
     aEntry=std::make_pair(aID,aPointer );
     mVector->push_back(aEntry);
  }
private: 
  std::vector<entry> * mVector;
};

class SomeType {
};

int main() {
    SomeType * aTipe= new SomeType();
    int aID=1;
    AVectorContainner<SomeType> *aContainer= new AVectorContainner<SomeType>();
    aContainer->insert(aTipe,aID);//error line
    return 0;
}
