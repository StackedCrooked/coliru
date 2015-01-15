class Quaternion
{
public:
    Quaternion(double angle, Vector3d v) /* */ { }
    // ...
};

class QuaternionFactory
{
    QuaternionFactory(Vector3d axis) : _axis{axis} { }
    
    Quaternion MakeQuaternion(double angle)
    {
        return {angle, _axis};
    }
    
    Vector3d _axis;
};

int main()
{
}