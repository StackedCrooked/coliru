class B{
    public:
        B(){
            this->val=0;
        }

        void setVal(){
            this->val = 2;
        }

    private:
        int val;
};

class A{
    public:
        A(){
            this->b = new B;
        }
        void changeMemberFromConstMethod() const {
            this->b->setVal();
        }
    private:
        B const *b;
};

int main() 
{
}
