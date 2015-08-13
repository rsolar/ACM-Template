#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
#define N 1005
#define M 55

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

char mp[N][N];
int h, w, t, p, q;
ll hs[N][N], hss[M];

bool judge() {
	for (int i = 0; i <= h - p; i++) {
		for (int j = q - 1; j < w; j++) {
			bool flag = true;
			for (int k = 0; k < p; k++) {
				if (hs[i + k][j] != hss[k]) { flag = false; break; }
			}
			if (flag) { return true; }
		}
	}
	return false;
}

int main() {
	int C = 0;
	while (getInt(h), getInt(w), getInt(t), getInt(p), getInt(q), h) {
		memset(hs, 0, sizeof(hs));
		for (int i = 0, j; i < h; i++) {
			scanf("%s", mp[i]);
			for (j = 0; j < q; j++) {
				if (mp[i][j] == '*') { hs[i][q - 1] |= (1LL << j); }
			}
			for (; j < w; j++) {
				if (mp[i][j - q] == '*') { hs[i][j] = hs[i][j - 1] - 1LL; }
				else { hs[i][j] = hs[i][j - 1]; }
				hs[i][j] >>= 1LL;
				if (mp[i][j] == '*') { hs[i][j] |= (1LL << (q - 1)); }
			}
		}
		int ans = 0;
		while (t--) {
			for (int i = 0; i < p; i++) {
				scanf("%s", mp[i]);
				hss[i] = 0;
				for (int j = 0; j < q; j++) {
					if (mp[i][j] == '*') { hss[i] |= (1LL << j); }
				}
			}
			if (judge()) { ans++; }
		}
		printf("Case %d: %d\n", ++C, ans);
	}
}
