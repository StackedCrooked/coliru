template <typename... Types>
class TupleLite {};

template <typename FirstType, typename... OtherTypes>
class TupleLite<FirstType, OtherTypes...>
{
  public:
    FirstType type_;
    TupleLite<OtherTypes...> other_types_;
};


int main()
{
  TupleLite<int,double> mytuple;
}