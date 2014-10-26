#include <fstream>
#include <utility>
using namespace std;

auto make_logger = [](auto file)
{
    ofstream f(file);
    return [f = move(f)](auto x) mutable
    {
        f << "logging: " << x << endl;
    };
};

int main()
{
    auto log = make_logger("log.txt");
    log("Elbereth");
    log(42);
}
