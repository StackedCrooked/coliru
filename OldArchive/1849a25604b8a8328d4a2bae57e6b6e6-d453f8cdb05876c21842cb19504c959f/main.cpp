#include <algorithm>
#include <vector>

class Person{
public:
    bool operator<(const Person& p) const; // sorts by weight
    friend bool compareWeight(const Person &p, int wt);
    friend bool compareWeight(int wt, const Person &p);
private:
    int age;
    int weight;
};

bool compareWeight(int wt, const Person &p)
{
    return wt < p.weight;
}
bool compareWeight(const Person &p, int wt)
{
    return wt < p.weight;
}

int main()
{
    std::vector<Person> v;
    typedef bool (*Comp)(const Person&, int);
    std::lower_bound(v.begin(), v.end(), 50, static_cast<Comp>(&compareWeight));
}