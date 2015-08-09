#include <iostream>
#include <cstdio>
using namespace std;

#define N 10

char mp[N][N];
bool col[N];
int n, k, ans;

void dfs(int row, int k) {
	if (k == 0) { ans++; return; }
	for (int i = row; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (mp[i][j] == '#' && !col[j]) {
				col[j] = true;
				dfs(i + 1, k - 1);
				col[j] = false;
			}
	}
}

int main() {
	while (scanf("%d %d", &n, &k), n >= 0) {
		getchar();
		for (int i = 0; i < n; i++) {
			gets(mp[i]);
			col[i] = false;
		}
		ans = 0;
		dfs(0, k);
		printf("%d\n", ans);
	}
}
