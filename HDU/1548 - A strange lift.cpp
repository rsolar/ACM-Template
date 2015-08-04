#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define N 205

template <class T>
inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

struct Node {
	int x, step;
};
bool vis[N];
int k[N], n, a, b;

int bfs() {
	Node p = {a, 0}, t;
	queue<Node> que;
	memset(vis, 0, sizeof(vis));
	vis[a] = true;
	que.push(p);
	while (!que.empty()) {
		p = que.front(); que.pop();
		if (p.x == b) { return p.step; }
		t.step = p.step + 1;
		t.x = p.x + k[p.x];
		if (t.x > 0 && t.x <= n && !vis[t.x]) {
			vis[t.x] = true;
			que.push(t);
		}
		t.x = p.x - k[p.x];
		if (t.x > 0 && t.x <= n && !vis[t.x]) {
			vis[t.x] = true;
			que.push(t);
		}
	}
	return -1;
}

int main() {
	while (getInt(n), getInt(a), getInt(b), n) {
		for (int i = 1; i <= n; i++) { getInt(k[i]); }
		printf("%d\n", bfs());
	}
}
