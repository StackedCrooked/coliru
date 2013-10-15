
enum class Method { Get, Post, Put, Other };


Method ParseMethod(const char* begin, const char* end)
{
    enum State
    {
        Initial,
        G, GE,      // GET
        P, PO, POS, // POST
           PU       // PUT
    };
    
    State state = Initial;

    for (auto i = begin; i != end; ++i)
    {
        char c = *i;
        switch (state)
        {
            case Initial: switch (c)
            {
                case 'G': state = G; continue;
                case 'P': state = P; continue;
                default: return Method::Other;
            }
            case G: switch (c)
            {
                case 'E': state = GE; continue;
                default: return Method::Other;
            }
            case GE: switch (c)
            {
                case 'T': return Method::Get;
                default: return Method::Other;
            }
            case P: switch (c)
            {
                case 'O': state = PO; continue;
                case 'U': state = PU; continue;
                default: return Method::Other;
            }
            case PO: switch (c)
            {
                case 'S': state = POS; continue;
                default: return Method::Other;
            }
            case PU: switch (c)
            {
                case 'T': return Method::Put;
                default: return Method::Other;
            }
            case POS: switch (c)
            {
                case 'T': return Method::Post;
                default: return Method::Other;
            }
            default: assert(!"Invalid state!"); return Method::Other;
        }
    }
    return Method::Other;
}