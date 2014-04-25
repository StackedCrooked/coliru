class TestCls { public:     TestCls(TestCls *aa)    {   } }; 

int main(int argc, char **argv) {
    TestCls tt(&tt);
}