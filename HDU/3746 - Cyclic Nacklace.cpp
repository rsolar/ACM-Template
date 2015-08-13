#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 100005

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
int Next[N];

void getNext(char x[], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		gets(x);
		int len = strlen(x);
		getNext(x, len);
		int l = len - Next[len];
		if (Next[len] && len % l == 0) { puts("0"); }
		else { printf("%d\n", l - Next[len] % l); }
	}
}
