template<typename> struct C;

template<>
struct C<void> {
  private: typedef int type;
};

template<typename>
struct C       { using type = C<void>::type; };

int main(){
    C<int> c;
}