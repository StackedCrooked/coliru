#include <boost/filesystem.hpp>
using namespace boost::filesystem;
using namespace std;

int main()
{

    path dummy_path;

    // Snippet 1
    // Two paths
    // Succeeds
    //
    // vector<pair<path, path>> myvec;
    // myvec.emplace_back(dummy_path, dummy_path);

    // Snippet 2
    // Two unique_ptr's
    // Succeeds
    //
    // vector<pair<unique_ptr<int>, unique_ptr<int>>> myvec;
    // myvec.emplace_back(unique_ptr<int>(new int(13)), unique_ptr<int>(new int(12)));

    // Snippet 3
    // A path and a unique_ptr.
    //
    // **FAILS** on Clang, succeeds in Visual Studio
    //
    vector<pair<path, unique_ptr<int>>> myvec;
    myvec.emplace_back(dummy_path, unique_ptr<int>(new int(12)));

}