#include <random>
#include <iostream>
#include <string>
#include <cmath>





std::string WhatIsTheAnswerTo(const std::string& question) {
    std::random_device m_randomD;
    std::mt19937 m_mt(m_randomD());
    std::uniform_real_distribution<double> dist(1, 10);    
    
    const int sentence = static_cast<int>(dist(m_mt));
    std::string answer = "";
    for (int i = 0; i < sentence; i++) {
        std::string choice[] = {
            "maybe", "but", "perhaps",
            "yes", "no", "unlikely",
            "twelve", "just do it", "ship it"
        };
        int pick = std::floor(dist(m_mt));
        answer += choice[pick];
    }
    answer[0] -= 32;
    answer += ".";
    return answer;
}





int main() {
    WhatIsTheAnswerTo("rel.cpp");
}