#include <boost/asio.hpp>

static char const raw[] = { "This is \0 unusually \r\n\b hairy input" };

int main() {
    boost::asio::streambuf sb(256);

#if 0
    {
        std::ostream os(&sb);
        os.write(raw, sizeof(raw));
    }
#else
    sb.sputn(raw, sizeof raw);
    sb.pubseekpos(0);
#endif

    // let's read it out, unmunged:
    std::string roundtrip(std::istreambuf_iterator<char>(&sb), {});
    assert(std::end(raw) == std::mismatch(std::begin(raw), std::end(raw), std::begin(roundtrip)).first);
}
