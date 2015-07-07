#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define N 101
#define judge(x,y) (x>=0&&x<h&&y>=0&&y<w)

struct Node {
	int x, y, num, step;
} pos[5];
char mp[N][N];
bool flag, vis[N][N], posvis[5];
int h, w, k, ans, mov[4][2] = { { -1, 0}, {0, -1}, {0, 1}, {1, 0}}, posstep[5][5];

void bfs(Node s) {
	flag = false;
	int cnt = 0;
	Node t, p;
	queue<Node> que;
	que.push(s);
	while (!que.empty()) {
		p = que.front();
		que.pop();
		for (int i, d = 0; d < 4; d++) {
			t.x = p.x + mov[d][0]; t.y = p.y + mov[d][1]; t.step = p.step + 1;
			if (judge(t.x, t.y) && mp[t.x][t.y] != '#' && !vis[t.x][t.y]) {
				if (mp[t.x][t.y] == '$') {
					cnt++;
					for (i = 1; i <= k && (pos[i].x != t.x || pos[i].y != t.y); i++);
					if (t.step < posstep[s.num][i]) {
						posstep[s.num][i] = posstep[i][s.num] = t.step;
					}
				}
				vis[t.x][t.y] = 1;
				que.push(t);
			}
		}
	}
	if (cnt == k) {
		flag = true;
	}
}

void dfs(int n, int dis, int pre) {
	if (n == k) {
		if (dis < ans) {
			ans = dis;
		}
		return;
	}
	for (int i = 1; i <= k; i++) {
		if (!posvis[i]) {
			posvis[i] = true;
			dfs(n + 1, dis + posstep[pre][i], i);
			posvis[i] = false;
		}
	}
}

int main() {
	while (scanf("%d%d", &h, &w), h) {
		getchar();
		memset(pos, 0, sizeof(pos));
		memset(posstep, 0x7f, sizeof(posstep));
		memset(vis, 0, sizeof(vis));
		memset(posvis, 0, sizeof(posvis));
		ans = INT_MAX;
		for (int i = 0; i < h; i++) {
			gets(mp[i]);
			for (int j = 0; j < w; j++)
				if (mp[i][j] == '@') {
					pos[0].x = i;
					pos[0].y = j;
					vis[i][j] = 1;
				}
		}
		scanf("%d", &k);
		for (int x, y, i = 1; i <= k; i++) {
			scanf("%d%d", &x, &y);
			pos[i].x = x - 1;
			pos[i].y = y - 1;
			pos[i].num = i;
			mp[pos[i].x][pos[i].y] = '$';
		}
		bfs(pos[0]);
		if (flag) {
			for (int i = 1; i <= k; i++) {
				memset(vis, 0, sizeof(vis));
				vis[pos[i].x][pos[i].y] = 1;
				bfs(pos[i]);
			}
			dfs(0, 0, 0);
			printf("%d\n", ans);
		} else {
			printf("-1\n");
		}
	}
}
