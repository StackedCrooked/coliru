template<typename T>
int func1(const T* szTarget)
{
  //...
}

template<typename T>
T* func2(const T* szTarget)
{
  //...
}

class MyClass
{
public:
  template<>
  int func1(const char* szTarget)
  {
  }
  int func1(const wchar_t* szTarget);
  char* func2(const char* szTarget);
  wchar_t* func2(const wchar_t* szTarget);
};

int main()
{
    
}