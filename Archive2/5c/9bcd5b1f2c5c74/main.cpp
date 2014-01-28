#include <vector>
#include <iostream>

class Dumb
{
    public:
        typedef const std::vector<double> result_type;
    private:
        result_type mat_;
    public:
        Dumb(const result_type& mat) : mat_(mat) {}
        const result_type& get() const { return mat_; }
        result_type& get() { return mat_; }
};

int main(int, char*[])
{
    const std::vector<double> B(5,1.0);
    const Dumb d(B);
    d.get().push_back(6);
}