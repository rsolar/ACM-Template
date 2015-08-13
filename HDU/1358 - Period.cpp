#include <iostream>
#include <cstdio>
using namespace std;

#define N 1000005

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

char x[N];
int m, Next[N];

void getNext(char x[], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

int main() {
	int C = 0;
	while (getInt(m), m) {
		gets(x);
		printf("Test case #%d\n", ++C);
		getNext(x, m);
		for (int sz = 2; sz <= m; sz++) {
			int l = sz - Next[sz];
			if (sz % l == 0 && sz / l > 1) {
				printf("%d %d\n", sz, sz / l);
			}
		}
		putchar('\n');
	}
}
