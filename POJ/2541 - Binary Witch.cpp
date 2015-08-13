#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 1001005

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

char x[N], y[N];
int Next[N];

char getNext(char x[], int m) {
	int i = 0, j = -1, longest = 0, pos; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
		if (Next[i] > longest) { longest = Next[i]; pos = i - Next[i] - 1; }
		if (Next[i] == 13) { break; }
	}
	return longest == 0 ? '0' : x[pos];
}

int main() {
	int n, l;
	while (getInt(n)) {
		getInt(l);
		gets(x);
		int len = strlen(x);
		for (int i = 0; i < l; i++) {
			strcpy(y, x);
			reverse(y, y + len + i);
			x[len + i] = getNext(y, len + i); x[len + i + 1] = 0;
		}
		puts(x + len);
	}
}
