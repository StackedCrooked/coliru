#include <iostream>


class cInitialisationReporter
{
  int i;
public:
  ~cInitialisationReporter()
  {
      std::cout << "cInitialisationReporter::i is " << i << '\n';
  }
};


class cInitialisationReporter2
{
  int i;
public:
  cInitialisationReporter2() {}
  ~cInitialisationReporter2()
  {
      std::cout << "cInitialisationReporter2::i is " << i << '\n';
  }
};


class cInitialisationReporter3
{
  int i;
public:
  cInitialisationReporter3()=default;
  ~cInitialisationReporter3()
  {
      std::cout << "cInitialisationReporter3::i is " << i << '\n';
  }
};

template <class T> void
SetMemAndPlacementConstruct_ZeroInitialisation()
{
  T* allocated = static_cast<T*>(malloc(sizeof(T)));
  signed char* asCharPtr = reinterpret_cast<signed char*>(allocated);
  for(int i = 0; i != sizeof(T); ++i)
  {
      asCharPtr[i] = -1;
  }
  new((void*)allocated) T();
  allocated->~T();
}


template <class T> void
SetMemAndPlacementConstruct_DefaultInitialisation()
{
  T* allocated = static_cast<T*>(malloc(sizeof(T)));
  signed char* asCharPtr = reinterpret_cast<signed char*>(allocated);
  for(int i = 0; i != sizeof(T); ++i)
  {
      asCharPtr[i] = -1;
  }
  new((void*)allocated) T;
  allocated->~T();
}

int
main(int argc, char* argv[])
{
  SetMemAndPlacementConstruct_ZeroInitialisation<cInitialisationReporter>();
  SetMemAndPlacementConstruct_ZeroInitialisation<cInitialisationReporter2>();
  SetMemAndPlacementConstruct_ZeroInitialisation<cInitialisationReporter3>();
  SetMemAndPlacementConstruct_DefaultInitialisation<cInitialisationReporter>();
  SetMemAndPlacementConstruct_DefaultInitialisation<cInitialisationReporter2>();
  SetMemAndPlacementConstruct_DefaultInitialisation<cInitialisationReporter3>();
  return 0;
}