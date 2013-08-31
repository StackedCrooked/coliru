#include <iostream>
#include <string>
#include <cassert>
#include <memory>

class inner
{
  public:
    inner()
    {
      int i = 0;
      std::cout << "inner ctor: i = " << i << "\n";
    }

    explicit inner(int _i):i(_i) 
    {
      std::cout << "inner one arg ctor: i = " << i << "\n";
    }

    inner(const inner& rhs) // copy ctor
    {
      i = rhs.i;
      str = rhs.str;
      std::cout << "inner copy ctor: i = " << i << "\n";
    }

    inner& operator=(const inner& rhs)
    {
      std::cout << "inner assignment\n";
      i = rhs.i;
      return *this
    }

    int get_i()
    {
      return i;
    }

    char& operator[](std::size_t pos) const
    {
      assert(pos >= 0 && pos < str.length());
      return const_cast<char&>(str[pos]);
    }

    char& operator[](std::size_t pos)
    {
      assert(pos >= 0 && pos < str.length());
      return str[pos];
    }

  private:
    int i;  
    std::string str;
};


class outer
{
  public:
    outer(inner& _i): i(_i)
    {
      std::cout<< "outer ctor\n";
    }

    outer& operator=(const outer& rhs)
    {
        i = rhs.i;
        return *this
    }

  private:
    inner i;
};



class base
{
  public:
    base(std::string s): str(s) {};
    ~base()
    {
      std::cout << "base dtor\n";
    }
    base& operator= (const base& rhs)
    {
      std::cout << "base operator=\n";
      if(this == &rhs) 
        return *this;

      str = rhs.str;

      return *this;
    }

    const std::string& get_str() const
    {
      return str;
    }

    friend std::ostream& operator<< (std::ostream& stream, const base& d);

  private:
    std::string str;
};

std::ostream& operator<< (std::ostream& os, const base& d)
{
  os << "(" << d.str << ")";
  return os;
}

class der: public base
{
  public:
    der(std::string s, std::string s2): base(s), str2(s2) {};
    ~der()
    {
      std::cout << "der dtor\n";
    }

    der& operator=(const der& rhs)
    {
      std::cout << "der operator=\n";
      if(this == &rhs)
        return *this;


      base::operator=(rhs);

      str2 = rhs.str2;

      return *this;
    }

    friend std::ostream& operator<< (std::ostream& stream, const der& d);

  private:
    std::string str2;
};


std::ostream& operator<< (std::ostream& os, const der& d)
{
  os << "(" << d.str2 << "," << d.get_str() << ")";
  return os;
}

int main()
{
  inner i(20);
  outer o(i);

  der d1("abc", "xyz");
  der d2("qqq", "yyy");

  std::cout << "d2 = " << d2 << std::endl;

  d2 = d1;
  std::cout << "d2 = " << d2 << std::endl;

  std::auto_ptr<der> pd(new der("ddd", "eee"));

  std::cout << "pd = " << *pd << std::endl;

  std::shared_ptr<base> spb1(new base("yyy"));
  std::shared_ptr<base> spb2(spb1);
  std::cout << "spb1 = " << *spb1 << " spb2 = " << *spb2 << std::endl;
  

  return 0;
}