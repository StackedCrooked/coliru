#include <stdio.h>
#include <utility>
#include <map>

template <typename K, typename V>
static void
addMapping(const K& id,
           const V& index,
           std::map<K, V>& mapset
) {
    std::pair<std::map<K, V>::iterator, bool> ret;
    // ...
}
int main (){
    
    return 0;
}