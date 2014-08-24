#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

auto list = [](auto... vals) {
    return [=](auto operation) {
        return operation(vals...);
    };
};

auto cat = [](auto list1, auto list2) {
    return list1([=](auto... l1v) {
        return list2([=](auto... l2v) {
            return list(l1v..., l2v...);
        });
    });
};

auto head = [](auto lst) {
    return lst([=](auto fst, auto... rest) {
        return fst;
    });
};

auto tail = [](auto lst) {
    return lst([=](auto fst, auto... rest) {
        return list(rest...);
    });
};

int main()
{
    cat(list('1',"2",3), list('2','3',"4"))
    ([](auto fst, auto sec, auto... rest) {
            std::cout << fst << ", " << sec << std::endl;
    });
}
