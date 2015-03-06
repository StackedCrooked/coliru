#include <stdint.h>
#include <utility>

template<typename T>
class IDMap
{
public:
    struct Item {
        uint16_t mVersion;
        T mItem;

        template <typename... Arguments>
        Item(uint16_t version, Arguments&&... args);
    };

    // ....
};

template <typename T>
template <typename... Arguments>
IDMap<T>::Item::Item(uint16_t version, Arguments&&... args) : mVersion(version), mItem(std::forward<Arguments>(args)...)
{
}

int main() {
    IDMap<std::pair<char, double>>::Item m(5, 'a', 42.0);
}