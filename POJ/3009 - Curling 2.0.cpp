#include <iostream>
#include <cstdio>
using namespace std;

#define N 25
#define judge(x,y) ((x)>=0&&(x)<h&&(y)>=0&&(y)<w)

char mp[N][N];
int h, w, sx, sy, ans, mov[4][2] = {{ -1, 0}, {0, 1}, {1, 0}, {0, -1}};

void dfs(int x, int y, int step) {
	if (step >= ans) { return; }
	for (int i = 0; i < 4; i++) {
		int xx = x + mov[i][0], yy = y + mov[i][1];
		if (!judge(xx, yy) || mp[xx][yy] == '1') { continue; }
		while (mp[xx][yy] != '1') {
			if (mp[xx][yy] == '3') {
				if (step < ans) { ans = step; }
				return;
			}
			xx += mov[i][0], yy += mov[i][1];
			if (!judge(xx, yy)) { break; }
		}
		if (judge(xx, yy)) {
			mp[xx][yy] = '0';
			dfs(xx - mov[i][0], yy - mov[i][1], step + 1);
			mp[xx][yy] = '1';
		}
	}
}

int main() {
	while (scanf("%d %d", &w, &h), w) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				while ((mp[i][j] = getchar()) < '0' || mp[i][j] > '3');
				if (mp[i][j] == '2') { sx = i; sy = j; }
			}
		}
		ans = 11;
		dfs(sx, sy, 1);
		printf("%d\n", (ans > 10 ? -1 : ans));
	}
}
