#include <algorithm>
#include <array>
#include <utility>

template <typename T, typename CRTP>
struct VectorBase {
  CRTP& crtp() { return static_cast<CRTP&>(*this); }
  const CRTP& crtp() const { return static_cast<const CRTP&>(*this); }

  std::size_t size() const {
    return crtp().data.size();
  }

  void zero() {
    std::fill(std::begin(crtp().data), std::end(crtp().data), T());
  }

  T& operator [] (std::size_t i) {
    return crtp().data[i];
  }
};

template <typename T, std::size_t N>
struct Vector : VectorBase<T, Vector<T, N>> {
    union {
        std::array<T, N> data;
        struct {
            T x, y, z, w;
        };
    };
};

template <typename T>
struct Vector<T, 2> : VectorBase<T, Vector<T, 2>> {
    union {
        std::array<T, 2> data;
        struct {
            T x, y;
        };
    };
};

template <typename T>
struct Vector<T, 3> : VectorBase<T, Vector<T, 3>> {
    union {
        std::array<T, 3> data;
        struct {
            T x, y, z;
        };
    };
};

int main() {
    Vector<float, 3> vec3f;
    vec3f.zero();
    Vector<double, 2> vec2d;
    vec2d.size();
    vec2d[1] = vec3f[2];
}
