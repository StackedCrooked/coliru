#include <iostream>
#include <functional>

/*
Javascript:

function addThenFunction(a, b, fn) {
  fn(a + b);
}

addThenFunction(1, 2, function(data) {
  data -= 3;
});
*/

template <typename F> 
void addThenFunction(int a, int b, F cb)
{
  cb(a + b);
}

int main(int argc, char* args[])
{
  std::function<void(int)> cb = [](int data) {
    data -= 3;
  };

  addThenFunction(1, 2, cb);

  addThenFunction(1, 2, [](int data) -> void {
    data -= 3;
  });

  return 0;
}