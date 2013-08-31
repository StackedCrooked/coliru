#include <algorithm>
#include <iostream>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;
 
using namespace std;
 
int main(int argc, char* argv[])
{
    cout << "argv[0] = " << argv[0] << endl;
 
    path fullPath(argv[0]);
 
//    cout << (!1 ? "true" : "false") << endl;
 
//    boost::filesystem::system_complete(argv[0]);
 
//    cout << argv[0] << endl;
    path p (fullPath.parent_path());   // p reads clearer than argv[1] in the following code
 
      try
      {
        if (exists(p))    // does p actually exist?
        {
          if (is_regular_file(p))        // is p a regular file?
            cout << p << " size is " << file_size(p) << '\n';
 
          else if (is_directory(p))      // is p a directory?
          {
            cout << p << " is a directory containing:\n";
 
            typedef vector<path> vec;             // store paths,
            vec v;                                // so we can sort them later
 
//            for_each(directory_iterator(p), directory_iterator(), [](path it)
//            {
//                cout << it << endl;
//            });
            cout << "fullPath = " << fullPath << endl;
            copy_if(directory_iterator(p), directory_iterator(), back_inserter(v),
                    [&fullPath](path it)
            {
                cout << "it = " << it << endl;
                return true;
                return it.string().find(fullPath.string()) == std::string::npos;
            });
 
//            for_each(directory_iterator(p), directory_iterator(),
//                 [&v](path it){
//                cout << "it = " << it << endl;
//                v.push_back(it.string());
//            });
 
//            copy_if(directory_iterator(p), directory_iterator(), back_inserter(v),
//                    [&fullPathWhithExt](path it)
//            {
//                cout << "it = " << it << endl;
//                cout << "it.compare(fullPathWhithExt) = " <<
//                        it.compare(fullPath) << endl;
//                return true;
//                return it.string().find(fullPathWhithExt) == std::string::npos;
//            });
 
//            v.erase(remove(v.begin(), v.end()), v.end());
 
            sort(v.begin(), v.end());             // sort, since directory iteration
                                                  // is not ordered on some file systems
 
            for (vec::const_iterator it (v.begin()); it != v.end(); ++it)
            {
              cout << "   " << *it << '\n';
            }
          }
 
          else
            cout << p << " exists, but is neither a regular file nor a directory\n";
        }
        else
          cout << p << " does not exist\n";
      }
 
      catch (const filesystem_error& ex)
      {
        cout << ex.what() << '\n';
      }
 
 
    return 0;
}