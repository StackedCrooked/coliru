class CCoordinate
{
public:
    CCoordinate(float X = 0, float Y = 0) {}
    CCoordinate(CCoordinate& orig) {}
    ~CCoordinate() {}
};

auto main()
    -> int
{
    auto p = new CCoordinate[42];
    (void) p;
}
