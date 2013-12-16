struct Reading
{
  int hour;
  double temperature;
  constexpr Reading(int h, double temp)
      :hour(h), temperature(temp){}
};

constexpr bool operator==(const Reading& r1, const Reading& r2)
{
  return r1.hour == r2.hour && r1.temperature == r2.temperature;
}

int main()
{
  constexpr Reading r1(42, 4.2);
  constexpr Reading r2 = r1; // compiler will generate a default copy constructor here
  static_assert(r1 == r2, "not equal");
}
