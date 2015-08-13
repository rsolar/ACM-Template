#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 10005
#define M 80

template <class T>
inline bool getInt(T &x) {
	char c; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

char x[N][M], y[M][N];
int h, w, Next[N];

void getNextX(char x[][M], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && strcmp(x[i], x[j]) != 0) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

void getNextY(char x[][N], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && strcmp(x[i], x[j]) != 0) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

int main() {
	while (getInt(h)) {
		getInt(w);
		for (int i = 0; i < h; i++) { gets(x[i]); }
		for (int i = 0, j; i < h; i++) {
			for (j = 0; j < w; j++) {
				y[j][i] = x[i][j];
			}
			y[j][h] = 0;
		}
		getNextX(x, h);
		int t = h - Next[h];
		getNextY(y, w);
		printf("%d\n", t * (w - Next[w]));
	}
}
