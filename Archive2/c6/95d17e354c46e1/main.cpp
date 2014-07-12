#include <iostream>
#include <map>
#include <type_traits>

template <typename T, typename U>
using same_const = typename std::conditional<std::is_const<T>::value, const U, U>::type;

class Container {
public:
        Container() : mMap{ {1, "hello"}, {3, "world"} }
        { }

        std::string& find(int key) { return doFind(key, mMap); }
        const std::string& find(int key) const { return doFind(key, mMap); }

private:
        typedef std::map<int, std::string> Map;

        template <typename MapType>
        static same_const<MapType, std::string> & doFind(int key, MapType &map)
        {
                auto pos = map.find(key);
                if (pos == map.end()) {
                        throw std::invalid_argument("key");
                }
                return pos->second;
        }

        Map mMap;
};

int main(int, char*[])
{
        Container c1;
        std::cout << "c1.find(1)=" << c1.find(1) << std::endl;
        c1.find(1) = "byebye";
        std::cout << "c1.find(1)=" << c1.find(1) << std::endl;

        const Container c2;
        std::cout << "c2.find(1)=" << c2.find(1) << std::endl;
        //c2.find(1) = "byebye";

        return 0;
}
