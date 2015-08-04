#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 35

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

int a[N][N], b[N][N], c[N][N];

void turn90(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = b[n - j - 1][i];
		}
	}
	memcpy(b, c, sizeof(c));
}

int main() {
	int n;
	while (getInt(n), n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				getInt(a[i][j]);
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				getInt(b[i][j]);
			}
		}
		int ans = 0;
		for (int t = 0; t < 4; t++) {
			int countn = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (a[i][j] == b[i][j]) {
						countn++;
					}
				}
			}
			if (ans < countn) { ans = countn; }
			turn90(n);
		}
		printf("%d\n", ans);
	}
}
