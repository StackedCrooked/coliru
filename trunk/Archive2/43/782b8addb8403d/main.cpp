#include <cstring>
#include <assert.h>

struct Statistics {
  int counter1;
  int counter2;
  int counter3;
  int counter4;
  int counter5;
  // maybe more //
  Statistics() {
    memset(this, 0, sizeof(Statistics));
  }
};

void assert_Statistics() {
  Statistics s;
  int* ptr   = reinterpret_cast<int*>(&s);
  int  count = sizeof(Statistics) / sizeof(int);
  for (int i = 0; i < count; ++i) {
    assert(*(ptr++) == 0);
  }
}

int main()
{
  Statistics s;
  assert_Statistics();
}
