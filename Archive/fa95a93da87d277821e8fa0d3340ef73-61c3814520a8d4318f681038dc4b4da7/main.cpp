#pragma once
#include "Document.hpp"
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <string>

template<typename to, typename from>to lexical_cast(from const &x) {
    std::stringstream os;
	to ret;
	os << x;
	os >> ret;
	return ret;  
}

namespace libpdf {
	// • A one-line header identifying the version of the PDF specification to which the file conforms 
	// • A body containing the objects that make up the document contained in the file
	// • A cross reference table containing information about the indirect objects in the file
	// • A trailer giving the location of the cross-reference table and of certain special objects within the body of the file
	template <class it>
	class Parser {
		private:
			it Cursor;
			it eof;
			Document doc;
			
		public:
			Parser(it begin, it end) : Cursor(begin), EOF(end) {
			}
			
			Document Parse() {
				ParseHeader();
				return doc;
			}
		
		private:
			void ParseHeader() {
				Expect("%PDF-");
				doc.Version = ParseFloat();
			}
			
			void Expect(std::string value) {
				if(std::equal(Cursor, Cursor + value.length(), value.begin())) {
					Cursor += value.length();
				} else {
					std::stringstream sstr;
					sstr << "Expected ";
					sstr << value;
					sstr << " but got ";
					sstr << std::string(Cursor, Cursor + value.length());
					throw std::runtime_error(sstr.string());
				}
			}
			
			float ParseFloat() {
				it start = Cursor;
				while(Cursor != eof && isdigit(*Cursor)) {
					Cursor++;
				}
				Expect(".");
				while(Cursor != eof && isdigit(*Cursor)) {
					Cursor++;
				}
				return lexical_cast<float>(std::string(start, Cursor));
			}
	};
}