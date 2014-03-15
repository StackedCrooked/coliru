#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <cmath>

class fast_istream {
    static const int buffersize = 4096;
	char buffer[buffersize];
	char* beg;
	char* end;
	void read() {
		if (end-beg)
			memmove(buffer, beg, (size_t)(end-beg));
		beg = buffer;
		*beg = '\0';
		end = buffer + fread(buffer, 1, buffersize, stdin);
	}
	bool is_whitespace(char rhs)
	{ return rhs<33;}
	char getc_non_whitespace() {
		while(beg<end && is_whitespace(*beg))
			++beg;
		while (end==beg) {
			read();
			while(beg<end && is_whitespace(*beg))
				++beg;
		}
		return *beg++;
	}
	bool is_numeric(char rhs)
	{return rhs>='0'/*&&rhs<='9'*/;}
	char getc() {
		while (end==beg)
			read();
		return *beg++;
	}
	void push_back() {
		--beg;
	}
	fast_istream(const fast_istream& b);
	fast_istream& operator=(const fast_istream& b);
public:
	fast_istream() :beg(buffer), end(buffer) {}
	void read(char& rhs) {
		rhs = getc_non_whitespace();
	}
	void read(unsigned int& rhs) {
		rhs=0;
		char next = getc_non_whitespace();
		while(is_numeric(next)) {
			rhs = rhs * 10 + next-'0';
			next = getc();
		}
	}
	void read(signed int& rhs) {
		rhs=0;
		bool neg = false;
		char next = getc_non_whitespace();
		if (next == '-') {
			neg = true;
			next = getc();
		}
		while(is_numeric(next)) {
			rhs = rhs * 10 + next-'0';
			next = getc();
		}
		if (neg)
			rhs *= -1;
	}
	void read(unsigned long long& rhs) {
		rhs=0;
		char next = getc_non_whitespace();
		while(is_numeric(next)) {
			rhs = rhs * 10ull + next-'0';
			next = getc();
		}
	}
	void read(signed long long& rhs) {
		rhs=0;
		bool neg = false;
		char next = getc_non_whitespace();
		if (next == '-') {
			neg = true;
			next = getc();
		}
		while(is_numeric(next)) {
			rhs = rhs * 10ll + next-'0';
			next = getc();
		}
		if (neg)
			rhs *= -1ll;
	}
	void read(std::string& rhs) {
		rhs.clear();
		char next;
		next = getc_non_whitespace();
		char* endstr = beg;
		do {
			while(endstr<end && is_whitespace(*endstr)==false)
				++endstr;
			rhs.reserve((size_t)(rhs.size() + endstr-beg+1));
			if (next)
				rhs.append(1, next);
			if (endstr-beg)
				rhs.append(beg, (size_t)(endstr-beg));
		} while(endstr == end && is_whitespace(next=getc()) == false);
	}
	size_t read(char* buffer, size_t len, char delim='\n') {
		size_t r=0;
		while(true) {
			char* endstr = beg;
			while((endstr<end) && ((size_t)(endstr-beg)<len) && *endstr!=delim && *endstr!='\0')
				++endstr;
			size_t t = (size_t)(endstr-beg);
			r += t;
			if (t)
				memcpy(buffer, beg, t);
			beg = endstr;
			if (beg == end && len-r)
				read();
			else 
				break;
		}
		buffer[r] = '\0';
		if (beg<end && *beg==delim)
			++beg;
		return r;
	}
	fast_istream& operator>>(char& rhs) { read(rhs); return *this; }
	fast_istream& operator>>(signed char& rhs) { char t; read(t); rhs=(signed char)t; return *this; }
	fast_istream& operator>>(unsigned char& rhs) { char t; read(t); rhs=(unsigned char)t; return *this; }
	fast_istream& operator>>(signed short& rhs) { int t; read(t); rhs=(signed short)t; return *this; }
	fast_istream& operator>>(unsigned short& rhs) { unsigned int t; read(t); rhs=(unsigned short)t; return *this; }
	fast_istream& operator>>(unsigned int& rhs) { read(rhs); return *this; }
	fast_istream& operator>>(signed int& rhs) { read(rhs); return *this; }
	fast_istream& operator>>(unsigned long long& rhs) { read(rhs); return *this; }
	fast_istream& operator>>(signed long long& rhs) { read(rhs); return *this; }
	fast_istream& operator>>(std::string& rhs) { read(rhs); return *this; }
};
class fast_ostream {
	fast_ostream(const fast_ostream& b);
	fast_ostream& operator=(const fast_ostream& b);
public:
	fast_ostream() {}
	void write(char rhs) {
		fwrite(&rhs, 1, 1, stdout);
	}
	void write(unsigned int rhs) {
		char buf[21];
		buf[20] = '\0';
		int index=19;
		do {
			buf[index--] = (char)(rhs%10 + '0');
			rhs /= 10;
		} while(rhs);
		fwrite(buf+index+1, 1, (size_t)(19-index), stdout);
	}
	void write(unsigned long long rhs) {
		char buf[21];
		buf[20] = '\0';
		int index=19;
		do {
			buf[index--] = (char)(rhs%10 + '0');
			rhs /= 10;
		} while(rhs);
		fwrite(buf+index+1, 1, (size_t)(19-index), stdout);
	}
	void write(double rhs, unsigned int precision) {
		assert(precision<=20);
		unsigned int big = (unsigned int)rhs;
		write(big);
		rhs -= big;
		if (precision) {
			char buf[22] = {'.'};
			for(unsigned int i=1; i<precision+1; ++i) {
				rhs *= 10;
				if (i==precision)
					rhs += .5;
				char t = char(rhs);
				buf[i] = t+'0';
				rhs -= t;
			}
		    fwrite(buf, 1, precision+1, stdout);
		}
	}
	void write(const std::string& rhs) 
	{
		fwrite(rhs.c_str(), 1, rhs.size(), stdout);
	}
	void write(const char* rhs, size_t size=0) {
		if( size==0) {
			while(rhs[size]!='\0')
				++size;
		}
		fwrite(rhs, 1, size, stdout);
	}
	fast_ostream& operator<<(char rhs) { write(rhs); return *this; }
	fast_ostream& operator<<(signed char rhs) { write(char(rhs)); return *this; }
	fast_ostream& operator<<(unsigned char rhs) { write(char(rhs)); return *this; }
	fast_ostream& operator<<(unsigned short rhs) { write((unsigned int)rhs); return *this; }
	fast_ostream& operator<<(signed short rhs) { if (rhs<0) {write('-'); write((unsigned int)(-rhs));} else write((unsigned int)(rhs)); return *this; }
	fast_ostream& operator<<(unsigned int rhs) { write(rhs); return *this; }
	fast_ostream& operator<<(signed int rhs) { if (rhs<0) {write('-'); write((unsigned int)(-rhs));} else write((unsigned int)(rhs)); return *this; }
	fast_ostream& operator<<(unsigned long rhs) { write((unsigned int)(rhs)); return *this; }
	fast_ostream& operator<<(signed long rhs) { if (rhs<0) {write('-'); write((unsigned int)(-rhs));} else write((unsigned int)(rhs)); return *this; }
	fast_ostream& operator<<(unsigned long long rhs) { write(rhs); return *this; }
	fast_ostream& operator<<(signed long long rhs) { if (rhs<0) {write('-'); write((unsigned long long)(-rhs));} else write((unsigned long long)(rhs)); return *this; }
	fast_ostream& operator<<(const char* rhs) { write(rhs); return *this; }
	fast_ostream& operator<<(float rhs) { write((double)(rhs), 2); return *this; }
	fast_ostream& operator<<(double rhs) { write(rhs, 2); return *this; }
	fast_ostream& operator<<(const std::string& rhs) { write(rhs); return *this; }
};