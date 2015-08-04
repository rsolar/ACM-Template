#define N 100005

int fa[N];

void init(int n) {
	for (int i = 1; i <= n; i++) { fa[i] = i; }
}

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

inline void unite(int x, int y) {
	x = findfa(x); y = findfa(y);
	if (x != y) { fa[y] = x; }
}
