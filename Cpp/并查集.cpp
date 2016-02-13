//并查集 + 路径压缩 O(nlogn)
int fa[N];
void init(int n) { for (int i = 0; i <= n; i++) { fa[i] = i; } }
int findfa(int n) { return n == fa[n] ? n : fa[n] = findfa(fa[n]); }
inline void unite(int x, int y) {
  x = findfa(x); y = findfa(y);
  if (x != y) { fa[y] = x; }
}
//并查集 + 路径压缩 + 启发式合并 O(alpha(n))
int fa[N], rnk[N];
void init(int n) { for (int i = 0; i <= n; i++) { fa[i] = i; rnk[i] = 1; } }
int findfa(int n) { return n == fa[n] ? n : fa[n] = findfa(fa[n]); }
inline void unite(int x, int y) {
  x = findfa(x); y = findfa(y);
  if (x != y) {
    if (rnk[x] >= rnk[y]) { fa[y] = x; rnk[x] += rnk[y]; }
    else { fa[x] = y; rnk[y] += rnk[x]; }
  }
}
