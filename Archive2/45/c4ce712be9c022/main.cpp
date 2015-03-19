#include <iostream>
#include <vector>
#include <stdexcept>

void parse_file(std::istream &in) {
    enum states { BEGIN, MIDDLE, END };
	states state = BEGIN;

	std::vector<std::vector<int>> rows;

	std::vector<int> current_row;

	char ch;

	while (in.get(ch)) {
		switch (state) {
		case BEGIN:
			if (ch == '{')
				state = MIDDLE;
			break;
		case MIDDLE:
			if (ch == 'x' || ch == 'X' || ch == '0')
				current_row.push_back(-1);
			else if (isdigit(ch))
				current_row.push_back(ch - '0');
			else if (ch == '}') {
				if (current_row.size() != 9)
					throw std::runtime_error("Row size != 9");
				state = END;
			}
			break;
		case END:
			if (ch == '\n') {
				rows.push_back(current_row);
				current_row.clear();
				state = BEGIN;
			}			
		}
	}
}
