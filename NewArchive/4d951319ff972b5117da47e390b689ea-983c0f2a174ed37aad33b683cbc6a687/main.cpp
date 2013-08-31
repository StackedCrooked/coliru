#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>

int main()
{
    double neg_zero = -0.0;
    double pos_zero =  0.0;
    uint64_t raw_neg_zero;
    uint64_t raw_pos_zero;
    memcpy(&raw_neg_zero, &neg_zero, sizeof(raw_neg_zero));
    memcpy(&raw_pos_zero, &pos_zero, sizeof(raw_pos_zero));
    std::cout << std::scientific << std::hex;
    std::cout << neg_zero << ' ' << " 0x" << raw_neg_zero << std::endl;
    std::cout << pos_zero << ' ' << " 0x" << raw_pos_zero << std::endl;
    std::cout << "0.0 == -0.0: " <<  (pos_zero == neg_zero) << std::endl;
    std::cout << "0.0 < -0.0: " <<  (pos_zero < neg_zero) << std::endl;
    std::cout << "0.0 > -0.0: " <<  (pos_zero > neg_zero) << std::endl;
    std::cout << "0.0 <= -0.0: " <<  (pos_zero <= neg_zero) << std::endl;
    std::cout << "0.0 >= -0.0: " <<  (pos_zero >= neg_zero) << std::endl;
    std::cout << "0.0 != -0.0: " <<  (pos_zero != neg_zero) << std::endl;
    std::cout << "-0.0 < 0.0: " <<  (neg_zero < pos_zero) << std::endl;
    std::cout << "-0.0 > 0.0: " <<  (neg_zero > pos_zero) << std::endl;
    std::cout << "-0.0 <= 0.0: " <<  (neg_zero <= pos_zero) << std::endl;
    std::cout << "-0.0 >= 0.0: " <<  (neg_zero >= pos_zero) << std::endl;
    std::cout << "-0.0 != 0.0: " <<  (neg_zero != pos_zero) << std::endl;
}
