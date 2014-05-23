    #include <iostream>
    #include <string>

    struct my_str {
      std::string s;

      my_str(const std::string & str): s(str) { std::cout << "  my_str parameter ctor" << std::endl; }
      my_str(const my_str & o): s(o.s)        { std::cout << "  my_str copy ctor" << std::endl; }
      my_str(my_str && o): s(std::move(o.s))  { std::cout << "  my_str move ctor" << std::endl; }
    };

    template <typename T>
    my_str build_ur(T && s) {
      return my_str(std::forward<T>(s));
    }

    my_str build_val(my_str s) {
      return my_str(std::move(s)); 
    }

    int main() {
      my_str s1("hello");
      my_str s2("world");

      std::cout << "Building from universal reference (copy):" << std::endl;
      build_ur(s1);
      std::cout << "Building from universal reference (move):" << std::endl;
      build_ur(std::move(s1));

      std::cout << "Building from value (copy):" << std::endl;
      build_val(s2);               
      std::cout << "Building from value (move):" << std::endl;
      build_val(std::move(s2));    

      std::cout << std::endl;
      return 0;
    }