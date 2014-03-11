#include <vector>
#include <tuple>
using namespace std;
template <typename ... Ts>
class Data
{
public:
    template <typename T>
    void push_back(const T& x) { return getVector<T>().push_back(x); }

    template <typename T>
    std::size_t size() const { return getVector<T>().size(); }

private:
    template <typename T>
    const std::vector<T>& getVector() const { return std::get<get_index<T, Ts...>::value>(items); }

    template <typename T>
    std::vector<T>& getVector() { return std::get<get_index<T, Ts...>::value>(items); }
private:
    std::tuple<std::vector<Ts>...> items;
};
class A{};
class B{};

int main()
{
    Data<A, B> d;

    d.push_back(A());
    d.push_back(B());
    return 0;
}