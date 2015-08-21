#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

template<class T> inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

int main() {
	int h, w, x, sum, mn, mnx, mny;
	while (~scanf("%d %d", &h, &w)) {
		sum = 0; mn = INT_MAX;
		for (int i = 1; i <= h; i++) {
			for (int j = 1; j <= w; j++) {
				getInt(x); sum += x;
				if (mn > x && ((i + j) & 1)) { mn = x; mnx = i; mny = j; }
			}
		}
		if (h & 1) {
			printf("%d\n", sum);
			for (int i = 1; i <= h; i++) {
				for (int j = 1; j <= w - (i == h); j++) {
					if (j != w) { putchar(i & 1 ? 'R' : 'L'); }
					else { putchar('D'); }
				}
			}
		} else if (!(h & 1) && (w & 1)) {
			printf("%d\n", sum);
			for (int j = 1; j <= w; j++) {
				for (int i = 1; i <= h - (j == w); i++) {
					if (i != h) { putchar(j & 1 ? 'D' : 'U'); }
					else { putchar('R'); }
				}
			}
		} else {
			printf("%d\n", sum - mn);
			int pre = mnx & 1 ? mnx : mnx - 1;
			for (int i = 1; i < pre; i++) {
				for (int j = 1; j <= w; j++) {
					if (j != w) { putchar(i & 1 ? 'R' : 'L'); }
					else { putchar('D'); }
				}
			}
			for (int j = 1, pos = 0; j <= w; j++) {
				if (j == mny) { if (pre + 1 != h || mny != w) { putchar(j == w ? 'D' : 'R'); } }
				else {
					if (pos == 0) { putchar('D'); if (pre + 1 != h || j != w) { putchar(j == w ? 'D' : 'R'); } }
					else { putchar('U'); putchar('R'); }
					pos = !pos;
				}
			}
			for (int i = pre + 2; i <= h; i++) {
				for (int j = 1; j <= w - (i == h); j++) {
					if (j != w) { putchar(i & 1 ? 'L' : 'R'); }
					else { putchar('D'); }
				}
			}
		}
		putchar('\n');
	}
}
