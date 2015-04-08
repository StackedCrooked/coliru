#include <random>
#include <chrono>
#include <vector>
#include <memory>
#include <iostream>

void setZeros(int **matrix, int m, int n) {
  bool set_row_0 = false;
  bool set_col_0 = false;

  // check first row and column for zeros
  for (int i = 0; i < m; i++) {
    if (matrix[i][0] == 0) {
      set_col_0 = true;
      break;
    }
  }
  for (int j = 0; j < n; j++) {
    if (matrix[0][j] == 0) {
      set_row_0 = true;
      break;
    }
  }

  // first row and column can be used as temp to mark rows/columns for blanking
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      if (matrix[i][j] == 0) {
        matrix[0][j] = 0;
        matrix[i][0] = 0;
      }
    }
  }

  // blanking pass
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      if (matrix[0][j] == 0 || matrix[i][0] == 0) {
        matrix[i][j] = 0;
      }
    }
  }
  // blank first row/col if necessary
  if (set_row_0) {
    for (int j = 0; j < n; j++) {
      matrix[0][j] = 0;
    }
  }
  if (set_col_0) {
    for (int i = 0; i < m; i++) {
      matrix[i][0] = 0;
    }
  }
}

class Solution {
public:
  void setZeros(std::vector<std::vector<int>> &matrix) {
    int m = matrix.size();
    if (m < 1) {
      return;
    }
    int n = matrix[0].size();

    bool set_row_0 = false;
    bool set_col_0 = false;

    // check first row and column for zeros
    for (int i = 0; i < m; i++) {
      if (matrix[i][0] == 0) {
        set_col_0 = true;
        break;
      }
    }
    for (int j = 0; j < n; j++) {
      if (matrix[0][j] == 0) {
        set_row_0 = true;
        break;
      }
    }

    // first row and column can be used as temp to mark rows/columns for
    // blanking
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        if (matrix[i][j] == 0) {
          matrix[0][j] = 0;
          matrix[i][0] = 0;
        }
      }
    }

    // blanking pass
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        if (matrix[0][j] == 0 || matrix[i][0] == 0) {
          matrix[i][j] = 0;
        }
      }
    }
    // blank first row/col if necessary
    if (set_row_0) {
      for (int j = 0; j < n; j++) {
        matrix[0][j] = 0;
      }
    }
    if (set_col_0) {
      for (int i = 0; i < m; i++) {
        matrix[i][0] = 0;
      }
    }
  }
};

int main(int argc, char *argv[]) {
  int n = argc < 2 ? 100 : std::stoi(argv[1]);

  std::random_device rd;
  std::seed_seq seed{rd(), rd(), rd(), rd(), rd(), rd()};
  std::mt19937 eng;
  std::uniform_int_distribution<> dist(0, n - 1);

  std::vector<std::unique_ptr<int[]>> rows(n);
  std::vector<int *> matrix;
  matrix.reserve(n);
  for (auto &&row : rows) {
    row.reset(new int[n]);
    for (int i = 0; i < n; ++i) {
      row[i] = dist(eng);
    }
    matrix.push_back(&row[0]);
  }
  std::vector<std::vector<int>> matrix2(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      matrix2[i][j] = matrix[i][j];
    }
  }

  Solution s;

  auto start = std::chrono::steady_clock::now();
  setZeros(&matrix[0], n, n);
  auto middle = std::chrono::steady_clock::now();
  s.setZeros(matrix2);
  auto end = std::chrono::steady_clock::now();
  std::cout << (middle - start) / std::chrono::nanoseconds(1) << '\n';
  std::cout << (end - middle) / std::chrono::nanoseconds(1) << '\n';
}

