class First{
public:
  First()             = default;
  First(const First&) = default;

protected:
  ~First() = default;
};

class Second{
public:

  explicit operator First() const {
    return First();
  }

  Second()              = default;
  Second(const Second&) = default;
  Second(const First& )   {};

protected:
  ~Second() = default;
};

template< typename cardinal_policy>
class Host
: public cardinal_policy
{
public:
  Host() = default;

  template< typename o_c_p >
  explicit Host( const Host< o_c_p >& other )
  : cardinal_policy( other )
  {  }

};

int main(){    

  Host< Second > second;
  Host< First  > first( second );
  Host< Second > otherSecond(first);

  return 0;
}