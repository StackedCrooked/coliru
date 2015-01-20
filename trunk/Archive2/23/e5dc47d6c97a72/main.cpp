template <unsigned t>
void f()
{  
    using type = int[t+0];
    using type = int[t];
}

int main() {}