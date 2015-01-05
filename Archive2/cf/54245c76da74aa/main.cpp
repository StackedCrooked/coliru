#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

struct A
{
    std::string picture;
    int id;
    static std::vector<A> elements;
};

std::vector<A> A::elements;

struct Pos {int x, y;};

struct B
{
    Pos pos;
    int id;
    static std::vector<B> elements;
};

std::vector<B> B::elements;

template <typename... Ts>
class ComponentIterator {
    static constexpr std::size_t size = sizeof...(Ts);

public:
    ComponentIterator() : indices(), finished(false) { adjust(); }

    std::tuple<Ts&...> get()
    {
        return get(std::index_sequence_for<Ts...>());
    }

    ComponentIterator& operator ++()
    {
        for (auto& e : indices) {
            ++e;
        }
        adjust();
        return *this;
    }

    bool is_finished() const { return finished; }
private:
    void adjust()
    {
        adjust(std::index_sequence_for<Ts...>());
    }

    template <std::size_t...Is>
    std::tuple<Ts&...> get(std::index_sequence<Is...>)
    {
        return std::tie(Ts::elements[indices[Is]]...);
    }

    template <std::size_t...Is>
    void adjust(std::index_sequence<Is...>) {
        bool is_ended[size] = {indices[Is] == Ts::elements.size()...};
        if (std::any_of(std::begin(is_ended), std::end(is_ended),
            [](bool b) { return b; })) {
            finished = true;
            return;
        }

        int min_value = std::min({Ts::elements[indices[Is]].id...}) - 1;
        for (;;)
        {
            ++min_value;
            bool increases[size] = {increase_until<Ts>(indices[Is], min_value)...};
            if (std::any_of(std::begin(increases), std::end(increases),
                [](bool b) { return !b; })) {
                finished = true;
                return;
            }
            const int ids[size] = {Ts::elements[indices[Is]].id...};
            if (std::all_of(std::begin(ids), std::end(ids),
                [min_value](int id) { return id == min_value;})) {
                return;
            }
        }
    }

    template <typename T>
    bool increase_until(std::size_t& index, int min_value)
    {
        for (; index != T::elements.size(); ++index) {
            if (min_value <= T::elements[index].id) {
                return true;
            }
        }
        return false;
    }
private:
    std::array<std::size_t, size> indices;
    bool finished;
};

int main()
{
    A::elements = {
        {"somePic.jpg", 1}, {"otherPic.jpg", 2}, {"lastPic.jpg", 4}};
    B::elements = {{{1,2}, 2}, {{4,5}, 3}, {{4,5}, 4}};
    ComponentIterator<A, B> it;
    while (!it.is_finished()) {
        A& a = std::get<0>(it.get());
        B& b = std::get<1>(it.get());
        std::cout << "A id:" << a.id << ", picture:" << a.picture << std::endl;
        std::cout << "B id:" << b.id << ", pos:" << b.pos.x << ", " << b.pos.y << std::endl;
        ++it;
    }

}
