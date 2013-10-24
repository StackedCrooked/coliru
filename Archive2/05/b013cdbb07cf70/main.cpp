

enum class color { red, green, blue };

const char* to_string(color c)
{
    switch (c)
    {
        case color::red: return "red";
        case color::green: return "blue";
        case color::blue: return "blue";
        default: return "(invalid)"; // assert, throw?
    }
}