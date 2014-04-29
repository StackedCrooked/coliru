template<typename T, typename S=void> struct Array2;
template<typename T, typename S=void> struct Array3;

template<typename T, int N0, int N1, int S0, int S1>
struct Array2<T[N0][N1], T[S0][S1]> {};

template<typename T, int N0, int N1>
struct Array2<T[N0][N1], void> : Array2<T[N0][N1], T[N1][1]> {};

template<typename T, int N0, int N1, int N2, int S0, int S1, int S2>
struct Array3<T[N0][N1][N2], T[S0][S1][S2]> {

  template<int B0, int E0, int B1, int E1, int B2, int E2>
  Array3<T[E0 - B0][E1 - B1][E2 - B2], T[S0][S1][S2]>
  get() {
    return Array3<T[E0 - B0][E1 - B1][E2 - B2], T[S0][S1][S2]>();
  }
};

template<typename T, int N0, int N1, int N2>
struct Array3<T[N0][N1][N2], void> : Array3<T[N0][N1][N2], T[N1 * N2][N2][1]> {};

int main() {
  Array3<float[3][4][4], float[16][4][1]> a;

  auto b = a.get<0, 2, 0, 2, 0, 1>();
  return 0;
}