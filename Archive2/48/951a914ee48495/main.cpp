    #include <iostream>
    #include <functional>
    #include <list>
    #include <iostream>
    #include <boost/any.hpp>
     
    template <typename T>
    auto fetch_back(T& t) -> typename std::remove_reference<decltype(t.back())>::type
    {
      typename std::remove_reference<decltype(t.back())>::type ret = t.back();
      t.pop_back();
      return ret;
    }
     
    template <typename X>
    X test_cast(boost::any y)
    {
      return boost::any_cast<X>(y);
    }
     
    template <typename Ret, typename...Arg>
    Ret call (Ret (*func)(Arg...), std::list<boost::any> args)
    {
      if (sizeof...(Arg) != args.size())
        throw "Argument number mismatch!";
     
      return func(boost::any_cast<Arg>(fetch_back(args))...);
    }
     
    int foo(int x, double y, std::string z)
    {
      std::cout << "foo called : " << x << " " << y << " " << z << std::endl;
      return 42;
    }
     
    int main ()
    {
      std::list<boost::any> args;
      args.push_back(1);
      args.push_back(4.56);
      args.push_back(std::string("abc"));
      call(foo, args);
    }
    