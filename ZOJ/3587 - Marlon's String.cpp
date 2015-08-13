#include <iostream>
#include <cstdio>
#include <algorithm>
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

char x[N], y[N];
int Next1[N], Next2[N], cnt1[N], cnt2[N];

void getNext(char x[], int m, int Next[]) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

void KMP_Count(char x[], int m, char y[], int n, int Next[], int cnt[]) {
	int i = 0, j = 0;
	while (i < n) {
		while (j != -1 && y[i] != x[j]) { j = Next[j]; }
		i++; j++; cnt[j]++;
	}
	for (i = m; i >= 0; i--) {
		if (Next[i] != -1) { cnt[Next[i]] += cnt[i]; }
	}
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		memset(cnt1, 0, sizeof(cnt1));
		memset(cnt2, 0, sizeof(cnt2));
		gets(y); gets(x);
		int lenx = strlen(x), leny = strlen(y);
		getNext(x, lenx, Next1);
		KMP_Count(x, lenx, y, leny, Next1, cnt1);
		reverse(x, x + lenx);
		reverse(y, y + leny);
		getNext(x, lenx, Next2);
		KMP_Count(x, lenx, y, leny, Next2, cnt2);
		ll ans = 0;
		for (int i = 1; i < lenx; i++) {
			ans += (ll)cnt1[i] * cnt2[lenx - i];
		}
		printf("%I64d\n", ans);
	}
}
