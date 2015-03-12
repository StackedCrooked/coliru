struct SignalBase
{
  SignalBase() = default;

  template<typename Signal>
  SignalBase(Signal const& s)  // (1)
  {}
};

struct Signal1 : public SignalBase
{ using SignalBase::SignalBase; };

struct Signal2 : public SignalBase
{ using SignalBase::SignalBase; };

int main()
{ 
    Signal1 s1;
    Signal2 s2(s1);  // (2)
}
