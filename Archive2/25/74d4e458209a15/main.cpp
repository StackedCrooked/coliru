#include <iostream>
#include <string>
#include <map>
#include <functional>

#include <boost/any.hpp>

class AnyCaller
{
  std::map<std::string, boost::any> calls;
public:
  AnyCaller() {}

  void add(const std::string& name, const boost::any& fun) {
    calls[name] = fun;
  }

  // we always use the throwing version of any_cast
  // icbb by error checking

//  // no arg version
//  template<typename Ret>
//  Ret call(const std::string& s) {
//    const boost::any& a = calls[s];
//    return boost::any_cast< std::function<Ret(void)> >(a)();
//  }

  // this should be a variadic template to be actually usable
    template<typename Ret, typename... T>
    Ret call(const std::string& s, T&&... arg) {
        // we have to assume that our users know what we are actually returning here
        const boost::any& a = calls[s];
        return boost::any_cast< std::function<Ret(T...)> >(a)(std::forward<T>(arg)...);
    }

  virtual ~AnyCaller() {}
};

void MessageBoxW(void *, wchar_t const *msg, wchar_t const *title, void *)
{
    std::wcout << title << ": " << msg << std::endl;
}

class A
{
public:
  int foo1() { MessageBoxW(nullptr, L"Helolo VOID", L"Info", NULL); return 1; }
  double foo2(std::wstring str) { MessageBoxW(nullptr, str.data(), L"Info", NULL); return double(4.5); }

  unsigned foo3(std::wstring str1, std::wstring str2)
  {
    std::wstring strBuffer;

    strBuffer = str1;
    strBuffer += L"==>";
    strBuffer += str2;
    MessageBoxW(nullptr, strBuffer.data(), L"Info", NULL);

    return 4;
  }
};

int main()
{  
    {
        A a;
        AnyCaller c;
        c.add("foo1", std::function<int()>(std::bind(&A::foo1, &a)));
        c.add("foo2", std::function<double(std::wstring)>(
                        std::bind(&A::foo2, &a, std::placeholders::_1)));
        
        c.call<int>("foo1");
        c.call<double>("foo2", std::wstring(L"Calling foo2"));
    }  
    {
        A a;
        AnyCaller c;
        c.add("foo1", std::function<int(A*)>(&A::foo1));
        c.add("foo2", std::function<double(A*, std::wstring)>(&A::foo2));
        
        c.call<int>("foo1", &a);
        c.call<double>("foo2", &a, std::wstring(L"Calling foo2"));
    }
}
