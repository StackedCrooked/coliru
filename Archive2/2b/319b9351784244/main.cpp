
constexpr int giveMeValue() { return 42; }

struct TryMe {
  static constexpr int arr[1] = {
      giveMeValue()
  };  
};

constexpr int TryMe::arr[1];


int main(int argc, char **args)
{
    int val = TryMe::arr[0];
}