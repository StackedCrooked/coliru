#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

template <typename InputIterator, typename Func>
typename std::enable_if<
    		std::is_const<InputIterator>::value,
				double>::type
MedianEx(InputIterator src_begin, InputIterator src_end, Func func) {
  using value_type = typename std::iterator_traits<InputIterator>::value_type;
  size_t count = std::distance(src_begin, src_end);
  std::nth_element(src_begin, src_begin + (count / 2), src_cpy_end,
	  [&](value_type a, value_type b) { return func(a) < func(b); });
  return count > 0 ? func(*(src_begin + (count / 2))) : 0;
}

template <typename InputIterator, typename Func>
typename std::enable_if<
			!std::is_const<InputIterator>::value,
				double>::type
MedianEx(InputIterator src_begin, InputIterator src_end, Func func) {
  using value_type = typename std::iterator_traits<InputIterator>::value_type;
  std::vector<value_type> src_cpy(src_begin, src_end);
  auto src_cpy_begin = src_cpy.begin();
  auto src_cpy_end = src_cpy.end();

  size_t count = std::distance(src_cpy_begin, src_cpy_end);
  std::nth_element(src_cpy_begin, src_cpy_begin + (count / 2), src_cpy_end, 
	  [&](value_type a, value_type b) { return func(a) < func(b); });
  return count >0 ? func(*(src_cpy_begin +( count / 2))) : 0;
}

using EcvPoints = vector<cv::Point>;
using EcvPointIt = vector<cv::Point>::const_iterator;
cv::Point2f getPointsCenterMedian(EcvPointIt begin, EcvPointIt end) {
  size_t lenght = std::distance(begin, end);
  Point2f center;
  vector<Point> p;
  center.y = MedianEx(begin, end, [](const cv::Point& pnt) { return pnt.y; });
  return center;
}
int main() {}