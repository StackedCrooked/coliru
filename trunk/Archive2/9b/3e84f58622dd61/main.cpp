struct villain
{
    villain();
    //lots of other stuff
    bool Type1EnemyBlasts() {return true;}
    bool Type2EnemyBlasts() {return false;}
    bool (villain::*OnFire)();
};

villain::villain()
{
    //lots of other stuff
    OnFire = &villain::Type1EnemyBlasts;
}

int main()
{
    //lots and lots of other stuff
    villain *targets[100];
    targets[0] = new villain();
    villain& v = *targets[0];

    if ((v.*v.OnFire)())
    {
        return 1;
    }

    return 0;
}
