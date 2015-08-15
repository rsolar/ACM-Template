#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define N 20005
#define M 25

template <class T>
inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

char s[N][M];
int n, l, cnt[N];

int cmp(const void *a, const void *b) {
	return strcmp((char *)a, (char *)b);
}

int main() {
	while (getInt(n), getInt(l), n) {
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; i++) { gets(s[i]); }
		qsort(s, n, sizeof(s[0]), cmp);
		for (int i = 1, t = 1; i <= n; i++) {
			if (strcmp(s[i], s[i - 1]) == 0) { t++; }
			else { cnt[t]++; t = 1; }
		}
		for (int i = 1; i <= n; i++) {
			printf("%d\n", cnt[i]);
		}
	}
}
