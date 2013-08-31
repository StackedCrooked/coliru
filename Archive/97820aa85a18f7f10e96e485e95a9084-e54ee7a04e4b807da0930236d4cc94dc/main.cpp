    #include <vector>
    #include <boost/variant.hpp>
    #include <iostream>

    struct my_class { my_class(int i) : x{i} { } int x; };

    struct my_visitor : boost::static_visitor<void>
    {
        void operator () (int i)
        {
            std::cout << "Look, I got an int! " << i << std::endl;
        }

        void operator () (std::string const& s)
        {
            std::cout << "Look, I got an string! " << s << std::endl;
        }

        void operator () (my_class const& obj)
        {
            std::cout << "Look, I got a UDT! And inside it a " << obj.x << std::endl;
        }
    };

    int main()
    {
        typedef boost::variant<int, std::string, my_class> my_variant;
        std::vector<my_variant> v;
        v.push_back(42);
        v.push_back("Hello!");
        v.push_back(my_class{1729});

        my_visitor mv;
        for (auto const& e : v)
        {
            e.apply_visitor(mv);
        }
    }