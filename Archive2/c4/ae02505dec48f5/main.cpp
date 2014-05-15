class Foo{
    class Bar;
};

class Foo::Bar
{
    enum class PositionsEnum : int
    {
        Extended, Retracted
    };
    void MoveToPosition(PositionsEnum pos);
    PositionsEnum GetPosition();
};

void Foo::Bar::MoveToPosition(PositionsEnum  pos) {}

Foo::Bar::PositionsEnum Foo::Bar::GetPosition() { return Foo::Bar::PositionsEnum::Retracted; }

int main(){
    Foo f;
    return 0;
}
