    #include <iostream>
    #include <array>

    template <typename T> inline T bigArry(std::array<T, 5> data)
    {
        T level = data[0];
        for(T item : data)
        {
            if(level<item){ level=item; }
        }
        return  level;
    }

    int main()
    {
        std::array<int, 5> data = {1,2,3,4,5};
        std::cout << bigArry(data);

        return 0;
    }
