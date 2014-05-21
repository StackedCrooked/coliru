constexpr unsigned intLog2(unsigned num_states_) {
  return
    num_states_ == 1 ?
      1 :
      (
      intLog2(num_states_ - 1) * intLog2(num_states_ - 1) == num_states_ - 1 ?
        intLog2(num_states_ - 1) + 1 :
        intLog2(num_states_ - 1)
      );
}

template<int n>
struct A
{
    static constexpr const unsigned value = n;
};

int main()
{
    volatile A<intLog2(1024)> a;
}