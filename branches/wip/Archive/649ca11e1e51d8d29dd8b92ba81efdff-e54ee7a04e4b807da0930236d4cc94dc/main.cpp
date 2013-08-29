    #include <algorithm>
    #include <vector>

    int main()
    {
        std::vector<int> v {1, 2, 3, 4, 5, 6};
        std::vector<int> r;

        std::transform(v.begin(), v.end(), v.begin(),
            std::back_inserter(r), [] (int a, int b) { return a + b; });
    }
