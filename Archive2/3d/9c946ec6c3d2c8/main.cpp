#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <class K, class T> 
class KeyedCollection {
public:
  // Create an empty collection
  KeyedCollection();

  // Return the number of objects in the collection
  int size() const;

  // Insert object of type T with a key of type K into the
  // collection using an “ignore duplicates” policy
  void insert(const K&, const T&);

friend ostream& operator<<(ostream& outstream,const KeyedCollection<K,T>& inst) {

for (const auto& t : inst.objects)
{
    std::cout << t << std::endl;
}

return outstream;
}

private:
  // Insert required members here
        int objSize;
vector<T> objects;

};

template<class K, class T>
KeyedCollection<K,T>::KeyedCollection() {

objSize = 0;
vector<T> objects;
}   

template<class K, class T>
int KeyedCollection<K,T>::size() const {

    objSize = objects.size();

return objSize;
 }

template<class K, class T> 
void KeyedCollection<K,T>::insert(const K&,const T& c) {

objects.push_back(c);

}

int main()
{
    KeyedCollection<int, int> kc;
    kc.insert(1, 2);
    std::cout << kc;
}
