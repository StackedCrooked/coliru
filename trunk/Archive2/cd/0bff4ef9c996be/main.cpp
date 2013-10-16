#include <utility>
#include <ostream>

struct Position {
    int x;
    int y;

    friend std::ostream& operator<<(std::ostream& os, Position const& position) {
        return os << "{ " << position.x << ", " << position.y << " }";
    }
};
 
struct Cat {
    Position position;
    // other components
};
 
struct Dog {
    Position position;
    // other components
};

struct PositionIndepent
{
    // no position
};

namespace traits
{
template <typename T, typename BareT = typename std::remove_reference<T>::type>
struct have_position
{
  private:
    struct true_ {};
    struct false_;

    template <typename U>
        static auto test(U const&) -> decltype(std::declval<U>().position = Position {0,0}, void(), true_{});

    template <typename U>
        static false_ test(...);

  public:
    static constexpr bool value = std::is_same<true_, decltype(test<BareT>(std::declval<BareT>()))>::value;
};
 
}
 
#include <vector>
#include <boost/variant.hpp>

namespace details 
{

    struct MoveTo
    {
        typedef void result_type;

        MoveTo(Position target = {}) : target(target) {}
        Position target;

        template <typename T>
        auto operator()(T& object) const 
            -> typename std::enable_if<traits::have_position<T>::value, void>::type 
        {
            std::cerr << "Moving a " << typeid(T).name() << " from " << object.position << " to " << target << "\n";
            object.position = target;
        }

        template <typename T>
        auto operator()(T& object) const 
            -> typename std::enable_if<!traits::have_position<T>::value, void>::type 
        {
            std::cerr << "Cannot move " << typeid(T).name() << "\n";
        }
    };

}

template <typename... T>
void move(boost::variant<T...>& variant, Position const& target) {
    boost::apply_visitor(details::MoveTo(target), variant);
}

template <typename T>
void move(T& object, Position const& target) {
    details::MoveTo action(target);
    action(object);
}

int main()
{
    using Object = boost::variant<Cat, Dog, PositionIndepent>;

    auto randloc = [] { return Position { rand() % 10, rand() % 10 }; };

    auto objects = std::vector<Object> { 
        Cat { randloc() }, 
        Dog { randloc() },
        PositionIndepent { }, 
        Dog { randloc() } 
    };

    for (auto& anything : objects)
        move(anything, {0, 0});
}
