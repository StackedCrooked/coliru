#include <memory>

using uptr = std::unique_ptr<int>;

template <class T>
void useCallBack2(T&& callBack) {
  callBack();
}

template <class T>
void useCallBack(T&& callBack) {
  callBack();
  useCallBack2(std::move(callBack));
}

inline void someFunctionCallback(uptr&&) {
}

int main() {
  auto callBack = [] { someFunctionCallback(uptr{new int{8}}); };
  useCallBack(std::move(callBack));
}