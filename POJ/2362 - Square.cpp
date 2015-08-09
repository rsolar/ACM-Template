#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 25

int s[N], sn, len;
bool vis[N];

bool cmp(int a, int b) {
	return a > b;
}

bool dfs(int currentn, int currentpos, int currentlen) {
	int now = 0;
	for (int i = currentpos; i < sn; i++) {
		if ((s[i] != now || currentlen == len) && !vis[i] && s[i] <= currentlen) {
			now = s[i];
			vis[i] = true;
			if (currentlen == s[i]) {
				if (currentn == 3) { return true; }
				else if (dfs(currentn + 1, 0, len)) { return true; }
				else { vis[i] = false; return false; }
			} else if (currentlen > s[i]) {
				if (dfs(currentn, i, currentlen - s[i])) { return true; }
				else {
					vis[i] = false;
					if (currentlen == len) { return false; }
				}
			}
		}
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int totallen = 0;
		scanf("%d", &sn);
		for (int i = 0; i < sn; i++) {
			scanf("%d", &s[i]);
			totallen += s[i];
		}
		if (sn < 4 || totallen % 4 != 0) { puts("no"); }
		else {
			len = totallen >> 2;
			sort(s, s + sn, cmp);
			if (s[0] > len) { puts("no"); }
			else {
				memset(vis, 0, sizeof(vis));
				puts((dfs(1, 0, len) ? "yes" : "no"));
			}
		}
	}
}
