// is there anything wrong with the below snippet?
//   if yes: why doesn't it work as expected?
//   if  no: reason about how function overloads are selected

namespace logged {
  float half_of (int n) {
    std::cerr << "half_of(int), convert to float and continue\n";
    return half_of (static_cast<float> (n));
  }

  float half_of (float f) {
    std::cerr << "half_of(float), divide by two and return!\n";
    return f / 2.f;
  }
}

int
main (int argc, char *argv[])
{
  std::cout << logged::half_of (11) << std::endl;   
}