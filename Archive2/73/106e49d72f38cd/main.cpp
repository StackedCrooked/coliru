#include <memory>
#include <map>

using namespace std;

map<int, unique_ptr<int> > mapCreator () {
  map<int, unique_ptr<int> > smallMap;
  for (int i = 0; i < 10; i++) {
    unique_ptr<int> ptr(new int(10));
    smallMap.insert(make_pair(
      i,
      std::move(ptr)
    ));
  }
  return smallMap;
}

class mapContainer {
 public:
  mapContainer(map<int, unique_ptr<int> > smallMap) : smallMap_(std::move(smallMap)) {
  }     
 private:
  const map<int, unique_ptr<int> > smallMap_;
};

int main() {
  mapContainer container(mapCreator());
}