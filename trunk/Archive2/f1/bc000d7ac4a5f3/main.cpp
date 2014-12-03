#include <tuple>
using std::tuple;
using std::make_tuple;
using std::get;
#include <stdio.h>

int main(int argc, char **argv) {
    auto t = make_tuple(true,4);
    printf("%d\n",get<bool>(t)?get<int>(t):0);
    return 0;
}
