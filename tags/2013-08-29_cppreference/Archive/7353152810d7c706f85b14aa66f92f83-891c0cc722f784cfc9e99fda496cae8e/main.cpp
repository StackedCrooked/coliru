#include <iostream>
#include <iterator>
#include <sstream>

template <int tabwidth, typename In, typename Out>
    Out mogrify(In f, const In l, Out out)
{
    intmax_t ws = -1, col = 0;

    auto emit = [&]() mutable { 
    	if (ws >= 0 && col>ws) {
			while (ws<col && (ws/tabwidth+1)*tabwidth <= col) {
				*out++ = '\t';
                ws  = (ws/tabwidth+1)*tabwidth;
			}

			auto spaces	= (col-ws);
			while (spaces--) *out++ = ' ';

			ws = -1;
		}
    };

    while (f!=l) {
        switch(*f) {
            case ' ':
                 ws = ws<0? col : ws;
				 col++;
                 break;
            case '\t':
                 ws = ws<0? col : ws;
                 col = ((col/tabwidth)+1) * tabwidth;
                 break;
            case '\n': 
                 emit();
                 col = 0; *out++ = '\n';
                 break;
            default: 
                 emit();
				 col++;
                 *out++ = *f;
        }
        ++f;
    }
	emit();

    return out;
}


int main()
{
	std::istreambuf_iterator<char> f(std::cin), l;

	mogrify<4>(f, l, std::ostream_iterator<char>(std::cout));
}
