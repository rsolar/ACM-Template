#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 10000

bool isprime[N], vis[N];
int mp[N], n, m, ans;

void getpr() {
	memset(isprime, 0x7f, sizeof(isprime));
	isprime[0] = isprime[1] = false;
	for (int i = 2; i < N; ++i) {
		if (isprime[i]) {
			for (int j = i + i; j < N; j += i) {
				isprime[j] = false;
			}
		}
	}
}

bool bfs() {
	memset(mp, 0, sizeof(mp));
	memset(vis, 0, sizeof(vis));
	int que[N], front = 0, back = 0, p, t;
	vis[n] = true;
	que[back++] = n;
	while (front < back) {
		p = que[front++];
		if (p == m) {
			ans = mp[p];
			return true;
		}
		for (int i = 1; i <= 9; i += 2) {
			t = p - p % 10 + i;
			if (isprime[t] && !vis[t]) {
				mp[t] = mp[p] + 1;
				vis[t] = true;
				que[back++] = t;
			}
		}
		for (int i = 0; i <= 9; i++) {
			t = p - (p / 10 % 10 - i) * 10;
			if (isprime[t] && !vis[t]) {
				mp[t] = mp[p] + 1;
				vis[t] = true;
				que[back++] = t;
			}
		}
		for (int i = 0; i <= 9; i++) {
			t = p - (p / 100 % 10 - i) * 100;
			if (isprime[t] && !vis[t]) {
				mp[t] = mp[p] + 1;
				vis[t] = true;
				que[back++] = t;
			}
		}
		for (int i = 1; i <= 9; i++) {
			t = p - (p / 1000 % 10 - i) * 1000;
			if (isprime[t] && !vis[t]) {
				mp[t] = mp[p] + 1;
				vis[t] = true;
				que[back++] = t;
			}
		}
	}
	return false;
}

int main() {
	getpr();
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		if (n == m) {
			puts("0");
		} else if (bfs()) {
			printf("%d\n", ans);
		} else {
			puts("Impossible");
		}
	}
}
