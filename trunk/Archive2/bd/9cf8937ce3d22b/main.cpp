#include <stdexcept>
#include <iostream>

using namespace std;

int main()
{
    try {
        throw runtime_error(":(");
    } catch(exception const& e) {
        cout << "exception: " << e.what() << endl;
    } catch(runtime_error const& e) {
        cout << "runtime_error: " << e.what() << endl;
    }
}
