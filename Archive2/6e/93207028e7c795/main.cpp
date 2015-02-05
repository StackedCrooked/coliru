#include <type_traits>
using namespace std;

template <
    class T,
    class = typename std::enable_if<!std::is_constructible<T>::value, void>::type
>
class singleton {
public:
    static T& instance() {
        static T inst;
        return inst;
    }
};

class class_with_public_constr
 : public singleton<class_with_public_constr> {
public:
    class_with_public_constr() {}
};

int main() {}