#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <set>
#include <tuple>
#include <algorithm>
#include <vector>
#include <bitset>
#include <list>
#include <cstdarg>
#include <iomanip>
#include <fstream>
#include <memory>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <locale>
#include <cstring>
#include <complex>
#include <queue>
#include <cstdint>
#include <random>
#include <array>
#include <typeinfo>
#include <thread>
#include <mutex>
#include <cassert>
#include <functional>
#include <atomic>
#include <future>
#include <tuple>
#include <iterator>
#include <unordered_map>
#include <deque>
#include <stdint.h>
#include <wchar.h>
#include <cmath>
#include <type_traits>

using namespace std;

int main()
{

    std::string in = u8"Hände";
    
    stringstream out;

    for (auto x : in)
        out << hex << "U+00" << x << " ";

    cout << out.str();

    return 0;
}