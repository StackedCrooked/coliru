struct unused_tag_type {};
void elem( struct unused_tag_type ) = delete;
void elem();

template<typename M>
void func(M& mat, int cols, int rows)
{
    for(int j = 0; j < rows; ++j)
      for(int i = 0; i < cols; ++i)
         elem(mat, i, j);
}

namespace N {
struct S {};
}

int elem(N::S, int, int) { return 1; }


int main() {
    N::S s;
    func(s,1,1);
}