#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 100001

int que[65000], mp[N], n, k;
bool vis[N];

int bfs() {
	memset(mp, 0, sizeof(mp));
	memset(vis, 0, sizeof(vis));
	int front = 0, back = 0, p, t;
	que[back++] = n;
	vis[n] = true;
	while (true) {
		p = que[front++];
		for (int i = 0; i < 3; ++i) {
			switch (i) {
				case 0: t = p << 1; break;
				case 1: t = p + 1; break;
				case 2: t = p - 1; break;
			}
			if (t >= 0 && t < N && !vis[t]) {
				mp[t] = mp[p] + 1;
				if (t == k) { return mp[t]; }
				vis[t] = true;
				que[back++] = t;
			}
		}
	}
}

int main() {
	while (~scanf("%d%d", &n, &k)) {
		printf("%d\n", (n >= k ? n - k : bfs()));
	}
}
