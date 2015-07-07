#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 28

bool mp[N][N], flag;
int n, ans, ch[N];

bool judge(int num) {
	for (int i = 0; i < n; i++) {
		if (mp[num][i] && ch[num] == ch[i]) {
			return false;
		}
	}
	return true;
}

void dfs(int num) {
	if (num == n) {
		flag = true;
		return;
	}
	for (int i = 1; i <= ans; i++) {
		ch[num] = i;
		if (judge(num)) {
			dfs(num + 1);
		}
		ch[num] = 0;
	}
}

int main() {
	char s[N];
	while (scanf("%d", &n), n) {
		getchar();
		flag = false;
		memset(mp, 0, sizeof(mp));
		for (int i = 0; i < n; i++) {
			gets(s);
			for (int j = 2; s[j]; j++) {
				mp[i][s[j] - 'A'] = true;
			}
		}
		for (ans = 1; !flag; ans++) {
			dfs(0);
		}
		printf("%d channel%s needed.\n", ans - 1, (ans > 2 ? "s" : ""));
	}
}
