#include <iostream>
#include <string>
#include <vector>
using namespace std;

int dirx[] = { 1, 0, -1, 0 };
int diry[] = { 0, -1, 0, 1 };

int main() {
    int w, h, r = 0;
	cin >> w >> h;
	while (w) {
		r++;
		cout << "HOUSE " << r << endl;
		int stx = 0, sty = 0, dir;

		vector<char> m(w * h);
		for (int i = 0; i < h; i++) {
			for (int o = 0; o < w; o++) {
				char s;
				cin >> s;
				m[i * w + o] = s;
				if (s == '*') {
					stx = o;
					sty = i;
					if (i == 0)
						dir = 3;
					else if (i == h - 1)
						dir = 1;
					else if (o == 0)
						dir = 0;
					else
						dir = 2;
				}
			}
		}

		while (m[stx + sty * w] != 'x') {
			//m[stx + sty * w] = 'O';
			stx += dirx[dir];
			sty += diry[dir];
			if (m[stx + sty * w] == '/')
				dir = (dir + ((dir % 2 == 0) ? 1 : 3)) % 4;
			else if (m[stx + sty * w] == '\\')
				dir = (dir + ((dir % 2 == 0) ? 3 : 1)) % 4;
		}

		for (int i = 0; i < w * h; i++) {
			if (stx + sty * w == i)
				cout << '&';
			else
				cout << m[i];

			if ((i + 1) % w == 0)
				cout << endl;
		}

		cin >> w >> h;
	}
}