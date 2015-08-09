#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 45
#define judge(x,y) ((x)>=0&&(x)<h&&(y)>=0&&(y)<w)

struct Node {
	int x, y, step;
} que[1600];
char mp[N][N];
bool vis[N][N];
int h, w, sx, sy, ex, ey, mov[4][2] = {{ -1, 0}, {0, 1}, {1, 0}, {0, -1}};

int dfs(int x, int y, int ex, int ey, int d, int step) {
	if (x == ex && y == ey) { return step; }
	d = (d + 3) % 4;
	int xx = x + mov[d][0], yy = y + mov[d][1];
	while (!judge(xx, yy) || mp[xx][yy] == '#') {
		d = (d + 1) % 4;
		xx = x + mov[d][0]; yy = y + mov[d][1];
	}
	return dfs(xx, yy, ex, ey, d, step + 1);
}

int bfs() {
	int front = 0, back = 0;
	Node t, p = {sx, sy, 1};
	vis[sx][sy] = true;
	que[back++] = p;
	while (true) {
		p = que[front++];
		if (mp[p.x][p.y] == 'E') { return p.step; }
		for (int d = 0; d < 4; d++) {
			t.x = p.x + mov[d][0]; t.y = p.y + mov[d][1]; t.step = p.step + 1;
			if (judge(t.x, t.y) && mp[t.x][t.y] != '#' && !vis[t.x][t.y]) {
				vis[t.x][t.y] = true;
				que[back++] = t;
			}
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(vis, 0, sizeof(vis));
		scanf("%d %d", &w, &h);
		getchar();
		for (int i = 0; i < h; i++) {
			gets(mp[i]);
			for (int j = 0; j < w; j++) {
				if (mp[i][j] == 'S') { sx = i; sy = j; }
				else if (mp[i][j] == 'E') { ex = i; ey = j; }
			}
		}
		printf("%d %d %d\n", dfs(sx, sy, ex, ey, 0, 1), dfs(ex, ey, sx, sy, 0, 1), bfs());
	}
}
