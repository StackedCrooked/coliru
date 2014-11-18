template<typename T> foo_result FooCall(T&& t) {
    try
    {
        t();
        return FOO_OK;
    }
    catch (const MyException1&)
    {
        return FOO_ERROR1;
    }
    catch (const MyException2&)
    {
        return FOO_ERROR2;
    }
    catch (...)
    {
        return FOO_UNKNOWN;
    }
}
foo_Result foo_dothing()
{
    return FooCall([] {
        foo::DoThing();
    });
}