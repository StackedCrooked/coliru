#include <exception>
#include <iostream>
#include <memory>

class shared_exit
{
    std::shared_ptr<shared_exit> finally;
 
    public:
 
    shared_exit() = default;
 
    template <typename T> shared_exit(T&& lambda):
        finally(this, std::forward<T>(lambda)) { }
};

int main()
{
    using namespace std;

    try
    {
        shared_exit block = [L = __LINE__, F = __FILE__](shared_exit* self)
        {
            cout << "Finally block " << self
                 << "\n\tIn source file: " << F
                 << "\n\tOn source line: " << L << "\n" << endl;
        };
        throw runtime_error("Runtime error #1");
    }
    catch (runtime_error const& error)
    {
        cerr << error.what() << endl;
    }
}
