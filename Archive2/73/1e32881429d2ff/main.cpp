#include <cstdint>
#include <iostream>
#include <vector>

void MaximumCircularSubarraySum(std::vector<int> A) {
    std::size_t bg_max_negative = 0;
	std::size_t end_max_negative = 0;
	int max_negative_sum = 0;

	std::size_t bg_negative = 0;
	int current_sum = 0;

	// Standard algorithm for non-circular subarrays
	for(std::size_t i = 0; i < A.size(); ++i) {
		int tentative_sum = current_sum + A[i];

		if(tentative_sum < 0 && current_sum >= 0)
			bg_negative = i;

		current_sum = tentative_sum;

		if(current_sum > 0) {
			current_sum = 0;
		}
		else if(current_sum < max_negative_sum) {
			bg_max_negative = bg_negative;
			end_max_negative = i;
			max_negative_sum = current_sum;
		}
	}

	// Spanning case
	for(std::size_t i = 0; current_sum < 0 && i < bg_negative; ++i) {
		current_sum += A[i];

		if(current_sum < max_negative_sum) {
			bg_max_negative = bg_negative;
			end_max_negative = i;
			max_negative_sum = current_sum;
		}
	}

	// Result
	std::size_t actual_begin = end_max_negative + 1;
	std::size_t actual_end = bg_max_negative - 1;
	int actual_result = 0;
	for(std::size_t i = 0; i < A.size() - 1; ++i) {
		if(actual_begin < actual_end) {
			if(i < actual_begin)
				i = actual_begin;
			else if(i > actual_end)
				break;
		}
		else {
			if(i == actual_end + 1)
				i = actual_begin;
		}

		actual_result += A[i];
	}

	// Output
	if(bg_max_negative == 0 && end_max_negative == A.size() - 1) {
		std::cout << "Array is negative. Sum over nothing, value 0." << std::endl;
		return;
	}
	std::cout << "Sum from " << actual_begin << " to " << actual_end << ", value " << actual_result << std::endl;
}

int main() {
	std::vector<int> a1 { {5, 4, -1, -1, 1, -1, -1, 5} };
	std::vector<int> a2 { {-3, 5, 4, 5, -1} };
	std::vector<int> a3 { {1, -5, 5, 4, -1, 5, -6, 3} };

	MaximumCircularSubarraySum(a1);
	MaximumCircularSubarraySum(a2);
	MaximumCircularSubarraySum(a3);
}