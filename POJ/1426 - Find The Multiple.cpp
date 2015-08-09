#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
#define N 205

ll que[3500], n, p, t;
bool vis[N];

ll bfs() {
	memset(vis, 0, sizeof(vis));
	int front = 0, back = 0;
	que[back++] = 1;
	while (front < back) {
		p = que[front++];
		t = p % n;
		if (t == 0) { return p; }
		vis[t] = true;
		t = p * 10;
		if (!vis[t % n]) { que[back++] = t; }
		if (!vis[(t + 1) % n]) { que[back++] = t + 1; }
	}
}

int main() {
	while (scanf("%I64d", &n), n) {
		printf("%I64d\n", bfs());
	}
}
