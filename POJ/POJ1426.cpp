#include <cstdio>
#include <cstring>
using namespace std;

#define N 201
typedef long long ll;

ll que[3500], n, p, t;
bool vis[N];

ll bfs() {
	int front = 0, back = 0;
	que[back++] = 1;
	while (front < back) {
		p = que[front++];
		t = p % n;
		if (t == 0) {
			return p;
		}
		vis[t] = true;
		t = p * 10;
		if (!vis[t % n]) {
			que[back++] = t;
		}
		if (!vis[(t + 1) % n]) {
			que[back++] = t + 1;
		}
	}
}

int main() {
	while (scanf("%I64d", &n), n) {
		memset(vis, 0, sizeof(vis));
		printf("%I64d\n", bfs());
	}
}
