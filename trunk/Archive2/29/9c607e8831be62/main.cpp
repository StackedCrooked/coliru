#include <vector>
#include <iostream>

using namespace std;

static const int NOT_FOUND = -1;

template <class sequence, class T>
int binarySearch(sequence& seq, int low, int high, T& item)
{
    return 0;
}

template <class sequence, class T>
int binarySearch(sequence& seq, T& item)
{
    if (seq.size() == 0)
        return NOT_FOUND;
    return binarySearch(seq, 0, seq.size() - 1, item);
}

int main()
{
    vector<int> t1 = {0, 3 ,45, 94};
    int i = 0;
    cout << binarySearch(t1, i);
    //binarySearch(t1, 0, t1.size() - 1, 45);
    return 0;
}