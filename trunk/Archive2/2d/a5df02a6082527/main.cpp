using System;

class Program
{
    static void Main(string[] args)
    {
        Start("Foo");
        Start("Bar");
    }

    static void Start(string name)
    {
        ExternalAPI api = new ExternalAPI();
        api.StartSubscription(name, x => Callback(x, name));
    }

    static void Callback(ReturnValue ret, string name)
    {
        Console.WriteLine("K = {0} V = {1} N = {2}", ret.Key, ret.Value, name);
    }
}


class ReturnValue
{
    public int Value { get; set; }
    public string Key { get; set; }
}


class ExternalAPI
{
    public void StartSubscription(string name, Action<ReturnValue> callback)
    {
        callback(new ReturnValue { Value = 42, Key = "blah" });
    }
}