/**
 * ParseRequestLines calls the LineHandler function for each line it encounters.
 * Returns pointer to start of message body or end if no body was found.
 */
template<typename LineHandler>
const char* ParseRequestLines(const char* begin, const char* end, LineHandler&& handler)
{
    enum State
    {
        Normal,
        CR, // carriage return ('\r') encountered
        LF, // line feed ('\n') encountered
        CR_LF,
        CR_LF_CR
    };

    State state = Normal;
    auto lineBegin = begin;
    auto lineEnd = begin;
    auto i = begin;
    for (; i != end; ++i)
    {
        char c = *i;
        if (c == '\r')
        {
            if (state == Normal)
            {
                // We got "\r", which indicates end of line data.
                // We must still wait for "\n".
                lineEnd = i;
                state = CR;
                continue;
            }
            else if (state == CR)
            {
                // We got "\r\r", which is bad.
                return end;
            }
            else if (state == LF)
            {
                // We got "\n\r", which is bad.
                return end;
            }
            else if (state == CR_LF)
            {
                // We got "\r\n\r"
                state = CR_LF_CR;
                continue;
            }
            else if (state == CR_LF_CR)
            {
                // We got "\r\n\r\r", which is bad.
                return end;
            }
            else
            {
                assert(!"This should be unreachable.");
            }
        }
        else if (c == '\n')
        {
            if (state == Normal)
            {
                // We got "\n", which indicates end of line.
                // (Both "\r\n" and "\n" must be accepted.)
                state = LF;
                lineEnd = i;
                if (lineBegin != lineEnd)
                {
                    handler(lineBegin, lineEnd);
                }
                lineEnd = lineBegin = i + 1;
                state = Normal;
                continue;
            }
            else if (state == CR)
            {
                // We got "\r\n", which indicates end of line.
                state = CR_LF;
                if (lineBegin != lineEnd)
                {
                    handler(lineBegin, lineEnd);
                }
                lineEnd = lineBegin = i + 1;
                state = Normal;
                continue;
            }
            else if (state == LF)
            {
                // We got "\n\n" which means end of header list.
                // Return the pointer to begin of message body.
                return i + 1;
            }
            else if (state == CR_LF)
            {
                // We got "\r\n\n", which is bad.
                return end;
            }
            else if (state == CR_LF_CR)
            {
                // We got "\r\n\r\n" which means end of header list.
                // Return the pointer to begin of message body.
                return i + 1;
            }
            else
            {
                assert(!"This should be unreachable.");
            }
        }
        else
        {
            continue;
        }
    }
    assert(!"This should be unreachable.");
    return end;
}
