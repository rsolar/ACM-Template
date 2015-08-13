#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 500005

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
int v[27], sum[N], Next[N], Extend1[N], Extend2[N];

void preExtend(char x[], int m) {
	int j = 0, k = 1;
	while (j + 1 < m && x[j] == x[j + 1]) { j++; }
	Next[0] = m; Next[1] = j;
	for (int i = 2; i < m; i++) {
		int p = Next[k] + k - 1, l = Next[i - k];
		if (i + l < p + 1) { Next[i] = l; }
		else {
			j = max(0, p - i + 1);
			while (i + j < m && x[i + j] == x[j]) { j++; }
			Next[i] = j;
			k = i;
		}
	}
}

void getExtend(char x[], int m, char y[], int n, int Extend[]) {
	preExtend(x, m);
	int j = 0, k = 0;
	while (j < n && j < m && x[j] == y[j]) { j++; }
	Extend[0] = j;
	for (int i = 1; i < n; i++) {
		int p = Extend[k] + k - 1, l = Next[i - k];
		if (i + l < p + 1) { Extend[i] = l; }
		else {
			j = max(0, p - i + 1);
			while (i + j < n && j < m && y[i + j] == x[j]) { j++; }
			Extend[i] = j;
			k = i;
		}
	}
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		for (int i = 0; i < 26; i++) { getInt(v[i]); }
		gets(x);
		int n = strlen(x), ans = 0;
		for (int i = 1; i <= n; i++) { sum[i] = sum[i - 1] + v[x[i - 1] - 'a']; }
		strcpy(y, x);
		reverse(y, y + n);
		getExtend(x, n, y, n, Extend1);
		getExtend(y, n, x, n, Extend2);
		for (int i = 1; i < n; i++) {
			int tmp = 0;
			if (Extend1[n - i] == i) { tmp += sum[i]; }
			if (Extend2[i] == n - i) { tmp += sum[n] - sum[i]; }
			ans = max(ans, tmp);
		}
		printf("%d\n", ans);
	}
}
