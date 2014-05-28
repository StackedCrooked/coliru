
    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <chrono>


    int main() {
      using namespace std;
      vector<chrono::milliseconds::rep> times;
      /// vector<chrono::milliseconds> times;

      for(int z = 0; z < 10; z++) {
        auto start = chrono::high_resolution_clock::now();
        //... the application to measure
        auto end = chrono::high_resolution_clock::now();
        auto elapsedtime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        times.push_back(elapsedtime);
        /// times.push_back(chrono::milliseconds(elapsedtime));
      }

      std::sort(times.begin(), times.end());

      std::cout << "Median: " << times.at(times.size()/2) << "(ms)" << endl;
      /// std::cout << "Median: " << times.at(times.size()/2).count() << "(ms)" << endl;
    }
