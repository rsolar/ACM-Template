//最小生成树
//Prim O(V^2)
#define N 105
#define INF 0x3f3f3f3f
int lowc[N];
bool vis[N];
int prim(int cost[][N], int n) {
  memset(vis, 0, sizeof(vis));
  int ans = 0;
  vis[0] = true;
  for (int i = 1; i < n; i++) { lowc[i] = cost[0][i]; }
  for (int i = 1; i < n; i++) {
    int minc = INF, p = -1;
    for (int j = 0; j < n; j++)
      if (!vis[j] && minc > lowc[j]) {
        minc = lowc[j]; p = j;
      }
    if (minc == INF) { return -1; } //原图不连通
    ans += minc;
    vis[p] = true;
    for (int j = 0; j < n; j++) {
      if (!vis[j] && lowc[j] > cost[p][j]) {
        lowc[j] = cost[p][j];
      }
    }
  }
  return ans;
}

//Kruskal O(E*logE)
#define N 105
#define M 10005
struct Edge {
  int u, v, w;
  bool operator<(const Edge &obj) const { return w < obj.w; }
} edge[M];
int fa[N], tol; //加边前赋值为0

void addedge(int u, int v, int w) {
  edge[tol].u = u; edge[tol].v = v; edge[tol++].w = w;
}

int findfa(int x) {
  return fa[x] == -1 ? x : fa[x] = findfa(fa[x]);
}

int kruskal(int n) {
  memset(fa, -1, sizeof(fa));
  sort(edge, edge + tol);
  int cnt = 0, ans = 0;
  for (int i = 0; i < tol; i++) {
    int u = edge[i].u, v = edge[i].v, w = edge[i].w;
    int t1 = findfa(u), t2 = findfa(v);
    if (t1 != t2) {
      ans += w;
      fa[t1] = t2;
      cnt++;
    }
    if (cnt == n - 1) { break; }
  }
  if (cnt < n - 1) { return -1; } //不连通
  else { return ans; }
}
