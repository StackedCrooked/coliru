#include <cstdio>

#define CREATE_HEADER(X, ...) \
  static const char header_left[][sizeof(X)/sizeof(X[0])] = { X, __VA_ARGS__ }; \
  static const size_t rows_in_header = sizeof(header_left) / sizeof(header_left[0]); \
  static const size_t columns_in_header = sizeof(X)/sizeof(X[0])

CREATE_HEADER(
    "         |          |  Raw  |  Raw  |",
    "         |          | Start |  End  |",
    "Interval#| Duration | Point | Point |",
    "---------+----------+-------+-------+",
);

int main()
{
  printf("%d", columns_in_header);
}