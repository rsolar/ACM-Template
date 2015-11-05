//最小生成树
//Prim + 邻接矩阵 O(V^2)
const int N = 1005;
const int INF = 0x3f3f3f3f;
int n, cost[N][N];
int dist[N];
bool vis[N];
int Prim() {
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i < n; i++) { dist[i] = cost[0][i]; }
  int ret = 0;
  vis[0] = true;
  for (int i = 1; i < n; i++) {
    int minc = INF, p = -1;
    for (int j = 0; j < n; j++) {
      if (!vis[j] && minc > dist[j]) { minc = dist[j]; p = j; }
    }
    if (minc == INF) { return -1; } //原图不连通
    ret += minc; vis[p] = true;
    for (int j = 0; j < n; j++) {
      if (!vis[j] && dist[j] > cost[p][j]) { dist[j] = cost[p][j]; }
    }
  }
  return ret;
}
//Prim + priority_queue + 邻接表 O(ElogV)
const int N = 100005;
const int M = 200005;
const int INF = 0x3f3f3f3f;
int head[N], to[M], Next[M], len[M], tot;
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, int z) { to[tot] = y; len[tot] = z; Next[tot] = head[x]; head[x] = tot++; }
struct Node {
  int v, w;
  Node(int _v, int _w): v(_v), w(_w) {}
  bool operator<(const Node &r)const { return w > r.w; }
};
int dist[N];
bool vis[N];
int Prim() {
  memset(dist, 0x3f, sizeof(dist));
  memset(vis, 0, sizeof(vis));
  int ret = 0;
  priority_queue<Node> que;
  for (int i = head[0]; ~i; i = Next[i]) {
    int v = to[i];
    if (len[i] < dist[v]) {
      dist[v] = len[i];
      que.push(Node(v, dist[v]));
    }
  }
  vis[0] = true;
  while (!que.empty()) {
    int u = que.top().v; que.pop();
    if (vis[u]) { continue; }
    vis[u] = true;
    ret += dist[u];
    for (int i = head[u]; ~i; i = Next[i]) {
      int v = to[i];
      if (!vis[v] && dist[v] > len[i]) {
        dist[v] = len[i];
        que.push(Node(v, dist[v]));
      }
    }
  }
  return ret;
}
//Kruskal + 邻接表 O(ElogE)
const int N = 1005;
const int M = 100005;
struct Edge {
  int u, v, w;
  bool operator<(const Edge &r)const { return w < r.w; }
} edge[M];
int n, fa[N], tol; //加边前赋值为0
void addedge(int u, int v, int w) { edge[tol].u = u; edge[tol].v = v; edge[tol++].w = w; }
int findfa(int x) { return fa[x] == -1 ? x : fa[x] = findfa(fa[x]); }
int Kruskal() {
  memset(fa, -1, sizeof(fa));
  sort(edge, edge + tol);
  int cnt = 0, ret = 0;
  for (int i = 0; i < tol; i++) {
    int u = edge[i].u, v = edge[i].v, w = edge[i].w, t1 = findfa(u), t2 = findfa(v);
    if (t1 != t2) { ret += w; fa[t1] = t2; cnt++; }
    if (cnt == n - 1) { break; }
  }
  if (cnt < n - 1) { return -1; } //不连通
  return ret;
}
//次小生成树
//Prim + 邻接矩阵 O(V^2 + E)
//求最小生成树时, 用数组Max[i][j]来表示MST中i到j最大边权
//求完后, 直接枚举所有不在MST中的边, 替换掉最大边权的边, 更新答案
const int N = 1005;
const int INF = 0x3f3f3f3f;
int n, cost[N][N];
int dist[N], pre[N], Max[N][N]; //Max[i][j]表示在最小生成树中从i到j的路径中的最大边权
bool vis[N], used[N][N];
int Prim() {
  memset(Max, 0, sizeof(Max));
  memset(pre, 0, sizeof(pre));
  memset(vis, 0, sizeof(vis));
  memset(used, 0, sizeof(used));
  int ret = 0;
  vis[0] = true; pre[0] = -1;
  for (int i = 1; i < n; i++) { dist[i] = cost[0][i]; }
  for (int i = 1; i < n; i++) {
    int minc = INF, p = -1;
    for (int j = 0; j < n; j++)
      if (!vis[j] && minc > dist[j]) { minc = dist[j]; p = j; }
    if (minc == INF) { return -1; } //原图不连通
    ret += minc; vis[p] = true;
    used[p][pre[p]] = used[pre[p]][p] = true;
    for (int j = 0; j < n; j++) {
      if (vis[j]) { Max[j][p] = Max[p][j] = max(Max[j][pre[p]], dist[p]); }
      if (!vis[j] && dist[j] > cost[p][j]) { dist[j] = cost[p][j]; pre[j] = p; }
    }
  }
  return ret;
}
//Kruskal + 邻接表 O(V*ElogE)
const int N = 1005;
const int M = 100005;
const int INF = 0x3f3f3f3f;
struct Edge {
  int u, v, w;
  bool operator<(const Edge &r)const { return w < r.w; }
} edge[M];
int n, fa[N], path[N], tol; //加边前赋值为0
void addedge(int u, int v, int w) { edge[tol].u = u; edge[tol].v = v; edge[tol++].w = w; }
int findfa(int x) { return fa[x] == -1 ? x : fa[x] = findfa(fa[x]); }
int Kruskal() {
  memset(fa, -1, sizeof(fa));
  sort(edge, edge + tol);
  int cnt = 0, ret = 0;
  for (int i = 0; i < tol; i++) {
    int u = edge[i].u, v = edge[i].v, w = edge[i].w, t1 = findfa(u), t2 = findfa(v);
    if (t1 != t2) { ret += w; fa[t1] = t2; path[cnt++] = i; }
    if (cnt == n - 1) { break; }
  }
  if (cnt < n - 1) { return -1; } //不连通
  return ret;
}
int KruskalSec() {
  int ret = INF;
  for (int x = 0; x < n - 1; x++) {
    memset(fa, -1, sizeof(fa));
    int cnt = 0, tmp = 0;
    for (int i = 0; i < tol; i++) {
      if (i != path[x]) {
        int u = edge[i].u, v = edge[i].v, w = edge[i].w, t1 = findfa(u), t2 = findfa(v);
        if (t1 != t2) { tmp += w; fa[t1] = t2; cnt++; }
        if (cnt == n - 1) { if (tmp < ret) { ret = tmp; } break; }
      }
    }
  }
  if (ret == INF) { return -1; } //不存在
  return ret;
}
