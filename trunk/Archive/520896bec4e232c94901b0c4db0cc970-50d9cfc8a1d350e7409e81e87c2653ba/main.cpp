template <int N>
struct Tensor
{
        Tensor<N - 1> x;
        Tensor<N - 1> y;
        Tensor<N - 1> z;

        Tensor() {}

        Tensor(const Tensor<N-1> &X, const Tensor<N-1> &Y, const Tensor<N-1> &Z) :
                x(X), y(Y), z(Z)
        {
        }
};

template <int N, int M>
Tensor<N + M> Outer(const Tensor<N> &lhs, const Tensor<M> &rhs)
{
        Tensor<N + M> result;

        result.x = Outer(lhs.x, rhs);
        result.y = Outer(lhs.y, rhs);
        result.z = Outer(lhs.z, rhs);

        return result;
}

template <int N>
Tensor<N + 1> Outer(const Tensor<N> &lhs, const Tensor<1> &rhs)
{
        Tensor<N + 1> result;

        result.x = Outer(lhs.x, rhs);
        result.y = Outer(lhs.y, rhs);
        result.z = Outer(lhs.z, rhs);

        return result;
}

template <>
Tensor<2> Outer(const Tensor<1> &lhs, const Tensor<1> &rhs)
{
        Tensor<2> result;

        result.x.x = lhs.x * rhs.x;
        result.x.y = lhs.x * rhs.y;
        result.x.z = lhs.x * rhs.z;

        return result;
}

template <>
struct Tensor<1>
{
        double x;
        double y;
        double z;

        Tensor() = default;

        Tensor(double x, double y, double z) : x(x), y(y), z(z)
        {
        }
};

int main()
{
        return 0;
}
