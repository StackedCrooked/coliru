#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <utility>

template <typename T, typename CRTP>
struct VectorBase {
  CRTP& crtp() { return static_cast<CRTP&>(*this); }
  const CRTP& crtp() const { return static_cast<const CRTP&>(*this); }

  std::size_t size() const {
    return std::extent<decltype(CRTP::data)>::value;
  }

  void zero() {
    std::fill(std::begin(crtp().data), std::end(crtp().data), T());
  }

  using iterator = T*;
  using const_iterator = const T*;
  iterator begin() { return &crtp().data[0]; }
  iterator end() { return &crtp().data[0] + size(); }
  const_iterator begin() const { return &crtp().data[0]; }
  const_iterator end() const { return &crtp().data[0] + size(); }

  T& operator [] (std::size_t i) {
    return crtp().data[i];
  }
  const T& operator [] (std::size_t i) const {
    return crtp().data[i];
  }
};

template <typename T, std::size_t N>
struct Vector : VectorBase<T, Vector<T, N>> {
  union {
    T data[N];
    struct {
      T x, y, z, w;
    };
  };
};

template <typename T>
struct Vector<T, 2> : VectorBase<T, Vector<T, 2>> {
  union {
    T data[2];
    struct {
      T x, y;
    };
  };
};

template <typename T>
struct Vector<T, 3> : VectorBase<T, Vector<T, 3>> {
  union {
    T data[3];
    struct {
      T x, y, z;
    };
  };
};

template <typename T, typename U, std::size_t N>
auto operator * (const Vector<T, N>& a, const Vector<U, N>& b)
 -> Vector<decltype(a[0] * b[0]), N> {
  Vector<decltype(a[0] * b[0]), N> result;
  for (std::size_t i = 0; i < N; ++i) {
    result[i] = a[i] * b[i];
  }
  return result;
}

template <typename T, typename U, std::size_t N>
auto dot(const Vector<T, N>& a, const Vector<U, N>& b)
 -> decltype(a[0] * b[0]) {
  auto product = a * b;
  using V = decltype(product.x);
  return std::accumulate(std::begin(product), std::end(product), V(0));
}

template <typename T> using Vector2 = Vector<T, 2>;
template <typename T> using Vector3 = Vector<T, 3>;
template <typename T> using Vector4 = Vector<T, 4>;
using Vec2 = Vector<float, 2>;
using Vec3 = Vector<float, 3>;
using Vec4 = Vector<float, 4>;
using Vec2d = Vector<double, 2>;
using Vec3d = Vector<double, 3>;
using Vec4d = Vector<double, 4>;
using Vec2i = Vector<int, 2>;
using Vec3i = Vector<int, 3>;
using Vec4i = Vector<int, 4>;

int main() {
  Vec3 vec3f;
  vec3f.zero();
  vec3f.y = 2.5;
  Vec3d vec3d;
  vec3d[1] = 3;
  std::cout << dot(vec3f, vec3d) << '\n';
}
