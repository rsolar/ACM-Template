#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
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
int Next[N], cnt[N];

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
		memset(cnt, 0, sizeof(cnt));
		gets(x);
		int n = strlen(x); ll ans = 0;
		getNext(x, n);
		for (int i = 1; i <= n; i++) {
			cnt[i] = cnt[Next[i]];
			ans += ++cnt[i];
		}
		printf("%I64d\n", ans);
	}
}
