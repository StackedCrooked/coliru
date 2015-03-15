import std.stdio;
import std.array;

template parse(string s, string ident)
{
    const char[] args = s
        .replace("%d", "int,")
        .replace("%f", "float,");
    const char[] def = "{ writeln(\"hello\"); }";
    const char[] parse = "void " ~ ident ~ "(" ~ args ~ ")" ~ def;
}

template test(string s)
{
    mixin(parse!(s, "test"));
}

void main(string[] args)
{
    test!("%d%f")(3, 3.);
}