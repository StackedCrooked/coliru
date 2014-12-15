#include <iostream>
#include <functional>
#include <string>

#include <map>
#include <vector>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>


class BaseFunc {
public:
    virtual ~BaseFunc() = default;

    virtual void Call(std::vector<boost::variant<int, double>>& args_vec) const = 0;
};

template <typename F> class Function;

template <typename R, typename... Args> class Function<R(Args...)> : public BaseFunc
{
public:
    Function(R (*f)(Args...)) : f(f) {}
    void Call(std::vector<boost::variant<int, double>>& args_vec) const override
    {
        Call(args_vec, std::index_sequence_for<Args...>());
    }
private:
    template <std::size_t ... Is>
    void Call(
        std::vector<boost::variant<int, double>>& args_vec,
        std::index_sequence<Is...>) const
    {
        f(boost::get<Args>(args_vec.at(Is))...);
    }

private:
    R (*f)(Args...);
};

class Container {
public:
    template <typename F>
    void AddFunc(const std::string& str, F* f) {
        functions[str] = std::make_unique<Function<F>>(f);
    }
    void CallFunc(const std::string& func_name,
                  std::vector<boost::variant<int, double>>& args_vec) {
        auto it = functions.find(func_name);
        if (it != functions.end())
        {
            it->second->Call(args_vec);
        }
    }
private:
    std::map<std::string, std::unique_ptr<BaseFunc>> functions;
};

void test_id(int i, double d) { std::cout << "id:" << i << " " << d << std::endl; }
void test_i3(int i, int j, int k) { std::cout << "ijk:" << i << " " << j << " " << k << std::endl; }


int main() {
    Container c;

    c.AddFunc("test_id", &test_id);
    c.AddFunc("test_i3", &test_i3);
    
    std::vector<boost::variant<int, double>> arg_id = {42, 0.5f};
    c.CallFunc("test_id", arg_id);
    
}
