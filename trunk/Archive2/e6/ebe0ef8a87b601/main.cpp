/* Public Domain Dedication
** License CC0 1.0 Universal (or any later version)
** http://creativecommons.org/publicdomain/zero/1.0/
**
** Written by olibre for stackoverflow question
*/

/// Represent a String using an external Buffer
struct MyString
{
    constexpr MyString( char const* p=0, int sz=0 ) : ptr_(p), size_(sz) {}
    constexpr char const* data() const { return ptr_;  }
    constexpr int         size() const { return size_; }

    char const *ptr_  = 0;
    int  const  size_ = 0;
};

struct Foo
{
    int foo()
    {
        return str_.size();
    }

    constexpr static MyString str_{"ABC",3};
};

int main()
{
  Foo bar;
  return ! bar.foo();
}

// Error because the below definition is missing:

//constexpr MyString Foo::str_;  

