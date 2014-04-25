#include <cstdint>

struct list
{
    int val;
    list *next;
};

void sort(list *head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) return;
    
    list *queue = head, *stack = head->next;
    head = head->next->next;
    stack->next = nullptr;
    
    while (head != nullptr) {
        queue = queue->next = head;
        head = head->next;

        if (head == nullptr) break;

        queue->next = stack;
        stack = head->next;
        head->next = queue->next;

        intptr_t s = reinterpret_cast<intptr_t>(stack), h = reinterpret_cast<intptr_t>(head);
        s ^= h ^= s ^= h;
        stack = reinterpret_cast<list*>(s); head = reinterpret_cast<list*>(h);
    }
    queue->next = stack;
}

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
using namespace std;

vector<int> make_random(int n) {
    vector<int> v; v.reserve(n);
    mt19937 engine;
    
    int odd_low = -10*n, even_high = 10*n, last = even_high;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) { // odd "node"
            uniform_int_distribution<int> dist(odd_low + 1, last - 1 - n + i);
            last = odd_low = dist(engine);
        } else { // even "node"
            uniform_int_distribution<int> dist(odd_low + n - i + 1, even_high - 1);
            last = even_high = dist(engine);
        }
        v.push_back(last);
    }

    return v;
}

list* to_list(vector<int>& v) {
    list *head = nullptr, *current;
    for (auto i : v) {
        if (head == nullptr) {
            current = head = new list{i, nullptr};
        } else {
            current = current->next = new list{i, nullptr};
        }
    }
    return head;
}

vector<int> to_vector(list *head) {
    vector<int> v;
    while (head != nullptr) {
        v.push_back(head->val);
        head = head->next;
    }
    return v;
}

int main() {
    auto v = make_random(10);
    cout << "before: "; for (auto i : v) cout << i << ' '; cout << '\n';

    auto l = to_list(v);
    sort(l);
    v = to_vector(l);

    cout << "after:  "; for (auto i : v) cout << i << ' '; cout << '\n';
    cout << "is_sorted: " << boolalpha << is_sorted(v.begin(), v.end()) << '\n';
}
