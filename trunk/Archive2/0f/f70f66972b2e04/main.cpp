#include <vector>

template<typename T1, typename T2 = T1::value_type>
        auto find_all(const T1& ar, T2 xr)
        {
                typedef T1::const_iterator const_iterator;
                vector<const_iterator> it;
                for (auto it2 = ar.cbegin(); it2 != ar.cend(); ++it2)
                        if (*it2 == xr)
                                it.push_back(it2);
                return it;
        }


int main()
{
    std::vector<int> v = {1,2,3};
    auto r = find_all(v, 1);
}
