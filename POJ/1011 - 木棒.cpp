#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 65

int s[N], sn, n, ans;
bool vis[N];

bool cmp(int a, int b) { return a > b; }

bool dfs(int currentn, int current, int currentlen) {
	if (currentn == n) { return true; }
	for (int i = current; i < sn; i++) {
		if (vis[i] || (i && !vis[i - 1] && s[i] == s[i - 1]) || currentlen < s[i]) { continue; }
		vis[i] = true;
		if (currentlen == s[i]) {
			if (dfs(currentn + 1, 0, ans)) { return true; }
			vis[i] = false;
			return false;
		} else {
			if (dfs(currentn, i + 1, currentlen - s[i])) { return true; }
			vis[i] = false;
			if (currentlen == ans) { return false; }
		}
	}
	return false;
}

int main() {
	while (scanf("%d", &sn), sn) {
		int totallen = 0;
		for (int i = 0; i < sn; i++) {
			scanf("%d", &s[i]);
			totallen += s[i];
		}
		sort(s, s + sn, cmp);
		for (ans = s[0]; ans < totallen; ans++) {
			if (totallen % ans == 0) {
				memset(vis, 0, sizeof(vis));
				n = totallen / ans;
				if (dfs(1, 0, ans)) { break; }
			}
		}
		printf("%d\n", ans);
	}
}
