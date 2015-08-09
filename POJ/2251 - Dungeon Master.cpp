#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define N 35
#define judge(x,y,z) (x>=0&&x<X&&y>=0&&y<Y&&z>=0&&z<Z)

struct Node {
	int x, y, z, step;
};
char mp[N][N][N];
bool vis[N][N][N];
int X, Y, Z, sx, sy, sz, ans, mov[6][3] = {{ -1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};

int bfs() {
	memset(vis, 0, sizeof(vis));
	Node t, p = {sx, sy, sz, 0};
	queue<Node> que;
	vis[sz][sx][sy] = true;
	que.push(p);
	while (!que.empty()) {
		p = que.front(); que.pop();
		for (int d = 0; d < 6; d++) {
			t.x = p.x + mov[d][0]; t.y = p.y + mov[d][1]; t.z = p.z + mov[d][2]; t.step = p.step + 1;
			if (judge(t.x, t.y, t.z) && mp[t.z][t.x][t.y] != '#' && !vis[t.z][t.x][t.y]) {
				if (mp[t.z][t.x][t.y] == 'E') { return t.step; }
				vis[t.z][t.x][t.y] = true;
				que.push(t);
			}
		}
	}
	return 0;
}

int main() {
	while (scanf("%d%d%d", &Z, &X, &Y), Z) {
		getchar();
		for (int k = 0; k < Z; k++) {
			for (int i = 0; i < X; i++) {
				gets(mp[k][i]);
				for (int j = 0; j < Y; j++) {
					if (mp[k][i][j] == 'S') {
						sx = i; sy = j; sz = k;
					}
				}
			}
			getchar();
		}
		ans = bfs();
		if (ans != 0) { printf("Escaped in %d minute(s).\n", ans); }
		else { puts("Trapped!"); }
	}
}
