template<typename Tx, typename Ty>
struct PointGeneric {};

template <typename Tx = float, typename Ty = Tx>
static PointGeneric<Tx, Ty> Point(Tx&& x, Ty&& y);

int main() {

    auto myPt1 = Point(5, 6);
 
    float someNum = 5;
    auto myPt2 = Point(someNum, someNum);

    auto myPt3 = Point(someNum, 6);
    auto myPt4 = Point(6, someNum);
}



