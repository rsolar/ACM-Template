#include <bits/stdc++.h>
using namespace std;

#define N 6
#define M 1000005

struct Node {
	int v, step;
};
int n, a[N], st, ed;
bool vis[M];

int Hash(int a[]) {
	int res = 0;
	for (int i = 0; i < 6; i++) { res = res * 10 + a[i]; }
	return res;
}

void deHash(int res) {
	for (int i = 5; i >= 0; i--) {
		a[i] = res % 10; res /= 10;
	}
}

int LR(int v) {
	deHash(v);
	int t = a[1];
	a[1] = a[2];
	a[2] = a[0];
	a[0] = a[3];
	a[3] = t;
	return Hash(a);
}

int RR(int v) {
	deHash(v);
	int t = a[1];
	a[1] = a[3];
	a[3] = a[0];
	a[0] = a[2];
	a[2] = t;
	return Hash(a);
}

int FR(int v) {
	deHash(v);
	int t = a[1];
	a[1] = a[4];
	a[4] = a[0];
	a[0] = a[5];
	a[5] = t;
	return Hash(a);
}

int BR(int v) {
	deHash(v);
	int t = a[1];
	a[1] = a[5];
	a[5] = a[0];
	a[0] = a[4];
	a[4] = t;
	return Hash(a);
}

int bfs() {
	memset(vis, 0, sizeof(vis));
	Node p = {st, 0}, t;
	queue<Node> que;
	vis[st] = true;
	que.push(p);
	while (!que.empty()) {
		p = que.front(); que.pop();
		if (p.v == ed) { return p.step; }
		t.step = p.step + 1;
		t.v = LR(p.v);
		if (!vis[t.v]) { vis[t.v] = true; que.push(t); }
		t.v = RR(p.v);
		if (!vis[t.v]) { vis[t.v] = true; que.push(t); }
		t.v = FR(p.v);
		if (!vis[t.v]) { vis[t.v] = true; que.push(t); }
		t.v = BR(p.v);
		if (!vis[t.v]) { vis[t.v] = true; que.push(t); }
	}
	return -1;
}

int main() {
	while (~scanf("%d %d %d %d %d %d", a, a + 1, a + 2, a + 3, a + 4, a + 5)) {
		st = Hash(a);
		scanf("%d %d %d %d %d %d", a, a + 1, a + 2, a + 3, a + 4, a + 5);
		ed = Hash(a);
		printf("%d\n", bfs());
	}
}
