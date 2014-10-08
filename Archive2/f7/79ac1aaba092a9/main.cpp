#include <cassert>
#include <utility>

using namespace std;

enum type_t { Obj, Arr, Str };

struct Object { void init(int); };
struct Array { void init(int); };
struct String { void init(int); };

class Value {
    type_t type;
    
    Object hObj;
    Array hArr;
    String hStr;

    template <type_t t>
    bool is() const { return type == t; }
    
public:
    template<class T> void setObj(T&& x)  { type = Obj; hObj.init(forward<T>(x)); } 
    template<class T> void setArr(T&& x)  { type = Arr; hArr.init(forward<T>(x)); }
    template<class T> void setStr(T&& x)  { type = Str; hStr.init(forward<T>(x)); }

    template <typename V>
    friend std::conditional_t<
        std::is_reference<V>::value,
        decltype((std::declval<V>().hObj)),
        decltype(std::declval<V>().hObj)
    >
    getObj(V&& v) {
        assert(v.template is<Obj>());
        return std::forward<V>(v).hObj;
    }
};

static_assert(std::is_same<Object&, decltype(getObj(std::declval<Value&>()))>::value, "");
static_assert(std::is_same<const Object&, decltype(getObj(std::declval<const Value&>()))>::value, "");
static_assert(std::is_same<Object, decltype(getObj(std::declval<Value>()))>::value, "");
static_assert(std::is_same<Object, decltype(getObj(std::declval<const Value>()))>::value, "");
