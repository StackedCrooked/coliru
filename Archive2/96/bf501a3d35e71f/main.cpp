    #include <iostream>
    #include <string>

    struct my_str {
      std::string s;

      my_str(): s("") { std::cout << "my_str default ctor" << std::endl; }
      my_str(const std::string & str): s(str) { std::cout << "my_str parameter ctor" << std::endl; }
      my_str(const my_str & o): s(o.s) { std::cout << "my_str copy ctor" << std::endl; }
      my_str(my_str && o): s(std::move(o.s)) { std::cout << "my_str move ctor" << std::endl; }
    };
    std::ostream & operator<<(std::ostream & o, const my_str & i) {
      return (o << i.s);
    }

    template <typename T>
    my_str build_templated(T && s) {
      return my_str(std::forward<T>(s));
    }

    my_str build_plain(my_str s) {
      return my_str(std::move(s)); 
    }

    int main() {
      my_str s1("hello");
      my_str s2("world");
      std::cout << "calling the templated function to obtain a copy:" << std::endl;
      build_templated(s1);           
      std::cout << "calling the templated function to move:" << std::endl;
      build_templated(std::move(s1));

      std::cout << "calling the plain function to obtain a copy:" << std::endl;
      build_plain(s2);               
      std::cout << "calling the plain function to move:" << std::endl;
      build_plain(std::move(s2));    

      return 0;
    }