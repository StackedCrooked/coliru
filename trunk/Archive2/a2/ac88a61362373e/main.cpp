struct A
{
protected:
    virtual void call_me() = 0;
};

struct B : public A
{
	void call()
	{
		call_me();
	}

private:
	void call_me()
	{
		static_cast<A*>(this)->call_me();       // -> error: `virtual void A::call_me()` is protected
//		A::call_me();                           // -> error: undefined referece to `A::call_me()`
	}
};

int main()
{
	B b;
	b.call();
}
