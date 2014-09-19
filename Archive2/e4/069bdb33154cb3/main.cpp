#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <limits>
#include <algorithm>
#include <memory>

using namespace std;

template <typename T> using v = vector<T>;
using uint = unsigned int;

const int MAX_M = 100; // Max number of floors
const int MAX_N = 500; // Max number of rooms on a floor

vector<int> shortest_path(uint input[][MAX_N], int m, int n)
{
    vector<int> result;

    if (m <= 0 || n <= 0) return result;

    // First element of the pair is the min path to this cell from
    // the bottom; second element is the index of the first element
    // on the previous floor along the min path or -1 for the first
    // floor.
    pair<uint, int>(*min_paths)[MAX_N] = new pair<uint, int>[MAX_M][MAX_N];

    for (int k = 0; k < n; ++k)
        min_paths[0][k] = make_pair(input[0][k], -1);

    for (int i = 1; i < m; ++i)
    {
        uint(*paths_within_prev_floor)[MAX_N] = new uint[MAX_N][MAX_N];

        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                paths_within_prev_floor[j][k] = j == k ? input[i - 1][k] :
                                                k < j  ? paths_within_prev_floor[k][j] :
                                                         paths_within_prev_floor[j][k - 1] + input[i - 1][k];

        for (int k = 0; k < n; ++k)
        {
            min_paths[i][k] = make_pair(numeric_limits<uint>::max(), -1);

            for (int j = 0; j < n; ++j)
            {
                uint path_to_k_via_j = min_paths[i - 1][j].first - input[i - 1][j] + paths_within_prev_floor[j][k] + input[i][k];

                if (path_to_k_via_j < min_paths[i][k].first)
                    min_paths[i][k] = make_pair(path_to_k_via_j, j);
            }
        }

        delete[] paths_within_prev_floor;
    }

    auto p_point_in_min_path = min_element(min_paths[m - 1], min_paths[m - 1] + n - 1);
    int k = p_point_in_min_path - min_paths[m - 1];
    result.push_back(k);
    for (int i = m - 2; i >= 0; --i)
    {
        int j = p_point_in_min_path->second;
        int step = j < k ? -1 : j > k ? 1 : 0;
        while (k != j)
        {
            result.push_back(k);
            k += step;
        }
        result.push_back(k);
        p_point_in_min_path = min_paths[i] + k;
    }

    delete[] min_paths;

    reverse(begin(result), end(result));
    return result;
}

int main()
{
    int m; // Number of floors
    int n; // Number of rooms on each floor;

    uint ext_input[MAX_M][MAX_N];

    cin >> m >> n;

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> ext_input[i][j];

    vector<int> v = shortest_path(ext_input, m, n);

    for (auto e : v) cout << e + 1 << " ";
}
