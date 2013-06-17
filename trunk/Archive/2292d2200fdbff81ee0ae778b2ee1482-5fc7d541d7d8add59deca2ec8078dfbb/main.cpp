    #include <vector>
    #include <string>
    #include <algorithm>
    #include <iostream>

    struct MyStruct {
      std::string member_one;
      std::string member_two;
    };

    int main()
    {
        std::vector<MyStruct> my_struct_vect = {
            {"Ha", "1234" },
            {"He", "3456" },
            {"Hi", "5678" },
            {"Ho", "9012" },
            {"Hu", "3456" },
            };

        std::vector<std::string> member_one_vect(my_struct_vect.size());

        std::transform(
            my_struct_vect.begin(), my_struct_vect.end(), member_one_vect.begin(),
            [] (MyStruct const& ms)
        {
            return ms.member_one;
        });

        for (auto const& s : member_one_vect)
        {
            std::cout << s << " ";
        }
    }

