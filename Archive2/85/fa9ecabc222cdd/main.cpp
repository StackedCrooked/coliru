#include <algorithm>
#include <functional>
#include <utility>

struct {
    bool operator()(Card a, Card b) {
     return (a.face_index() < b.face_index());   
    }
} cmp_cards

std::sort(hand.begin(), hand.end(), cmp_cards);