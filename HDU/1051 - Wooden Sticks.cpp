#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 5005

struct Stick {
	int l, w;
} s[N];
bool vis[N];

bool cmp(Stick a, Stick b) {
	return a.l < b.l || a.l == b.l && a.w < b.w;
}

int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &s[i].l, &s[i].w);
			vis[i] = false;
		}
		sort(s, s + n, cmp);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				for (int j = i + 1, mn = s[i].w; j < n; j++) {
					if (!vis[j] && s[j].w >= mn) {
						vis[j] = 1;
						mn = s[j].w;
					}
				}
				ans++;
			}
		}
		printf("%d\n", ans);
	}
}
