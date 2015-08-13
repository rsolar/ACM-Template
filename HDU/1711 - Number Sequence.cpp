#include <iostream>
#include <cstdio>
using namespace std;

#define N 1000005
#define M 10005

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

int n, m, a[N], b[M];
int Next[N];

void getNext(int x[], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

int KMP_Count(int x[], int m, int y[], int n) {
	int i = 0, j = 0;
	while (i < n) {
		while (j != -1 && y[i] != x[j]) { j = Next[j]; }
		i++; j++;
		if (j >= m) { return i - j + 1; }
	}
	return -1;
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		getInt(n); getInt(m);
		for (int i = 0; i < n; i++) { getInt(a[i]); }
		for (int i = 0; i < m; i++) { getInt(b[i]); }
		getNext(b, m);
		printf("%d\n", KMP_Count(b, m, a, n));
	}
}
