    #include <array>
    #include <iostream>

    template<std::size_t SIZE>
    void mulArray(std::array<int, SIZE>& arr, const int multiplier) {
        for(auto& e : arr) {
            e *= multiplier;
        }
    }

    int main()
    {
        std::array<int, 1> arr1 = {1};
        std::array<int, 2> arr2 = {1, 2};
        std::array<int, 3> arr3 = {1, 2, 3};

        mulArray(arr1, 3);
        for (auto x : arr1) { std::cout << x << " "; }
        std::cout << std::endl;

        mulArray(arr2, 5);
        for (auto x : arr2) { std::cout << x << " "; }
        std::cout << std::endl;

        mulArray(arr3, 2);
        for (auto x : arr3) { std::cout << x << " "; }
        std::cout << std::endl;
    }
