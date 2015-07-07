#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 21
#define judge(x,y) ((x)>=0&&(x)<h&&(y)>=0&&(y)<w)

char mp[N][N];
int h, w, sx, sy, ans, mov[8][2] = {{ -1, 0}, {0, -1}, {0, 1}, {1, 0}, { -1, -1}, { -1, 1}, {1, -1}, {1, 1}};
bool vis[N][N];

void dfs(int x, int y) {
	vis[x][y] = 1;
	for (int d = 0; d < 4; d++) {
		int xx = x + mov[d][0], yy = y + mov[d][1];
		if (!judge(xx, yy) || mp[xx][yy] != 'X') {
			ans++;
		}
	}
	for (int d = 0; d < 8; d++) {
		int xx = x + mov[d][0], yy = y + mov[d][1];
		if (judge(xx, yy) && mp[xx][yy] == 'X' && !vis[xx][yy]) {
			dfs(xx, yy);
		}
	}
}

int main() {
	while (scanf("%d%d%d%d", &h, &w, &sx, &sy), h) {
		getchar();
		for (int i = 0; i < h; i++) {
			gets(mp[i]);
		}
		memset(vis, 0, sizeof(vis));
		ans = 0;
		dfs(sx - 1, sy - 1);
		printf("%d\n", ans);
	}
}
