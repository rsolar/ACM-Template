#include <iostream>
#include <cstdio>
using namespace std;

#define N 200005
#define M 10007

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
	int T, n;
	getInt(T);
	while (T--) {
		getInt(n);
		gets(x);
		getNext(x, n);
		int ans = n;
		for (int i = n; i >= 1; i--) {
			int l = Next[i];
			while (l) { ans++; l = Next[l]; }
			if (ans >= M) { ans -= M; }
		}
		printf("%d\n", ans);
	}
}
