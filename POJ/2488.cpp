#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 27
#define judge(x,y) ((x)>=0&&(x)<h&&(y)>=0&&(y)<w)

int h, w, total, path[N][2], mov[8][2] = {{ -1, -2}, {1, -2}, { -2, -1}, {2, -1}, { -2, 1}, {2, 1}, { -1, 2}, {1, 2}};
bool vis[N][N];

bool dfs(int x, int y, int m) {
	path[m][0] = x; path[m][1] = y;
	if (m == total) {
		return true;
	}
	for (int i = 0; i < 8; i++) {
		int xx = x + mov[i][0], yy = y + mov[i][1];
		if (judge(xx, yy) && !vis[xx][yy]) {
			vis[xx][yy] = true;
			if (dfs(xx, yy, m + 1)) {
				return true;
			}
			vis[xx][yy] = false;
		}
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	for (int C = 1; C <= T; C++) {
		scanf("%d %d", &h, &w);
		memset(vis, 0, sizeof(vis));
		vis[0][0] = true;
		total = h * w;
		printf("Scenario #%d:\n", C);
		if (((h > 1 && w > 1) || (h == 1 && w == 1)) && dfs(0, 0, 1)) {
			for (int i = 1; i <= total; i++) {
				printf("%c%d", path[i][1] + 'A', path[i][0] + 1);
			}
			putchar('\n');
		} else {
			puts("impossible");
		}
		if (C != T) {
			putchar('\n');
		}
	}
}
