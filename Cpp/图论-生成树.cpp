//最小生成树
//Prim + 邻接矩阵 O(V^2)
typedef int wtype;
const wtype INF = 0x3f3f3f3f;
int n; wtype mp[N][N], cost[N];
bool vis[N];
wtype Prim(int src) {
  memset(vis, 0, sizeof(vis)); memcpy(cost, mp[src], sizeof(mp[src]));
  wtype ret = 0; vis[src] = true;
  for (int j = 1; j < n; j++) {
    int u = -1; wtype mn = INF;
    for (int i = 0; i < n; i++) {
      if (!vis[i] && mn > cost[i]) { mn = cost[i]; u = i; }
    }
    if (mn == INF) { return -1; } //原图不连通
    vis[u] = true; ret += mn;
    for (int v = 0; v < n; v++) {
      if (!vis[v] && cost[v] > mp[u][v]) { cost[v] = mp[u][v]; }
    }
  }
  return ret;
}
//Prim + priority_queue + 邻接表 O(ElogV)
typedef int wtype;
int head[N], to[M], nxt[M], tot; wtype len[M], cost[N];
bool vis[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, wtype z) { to[tot] = y; len[tot] = z; nxt[tot] = head[x]; head[x] = tot++; }
struct Node {
  int v; wtype w;
  bool operator<(const Node &r)const { return w > r.w; }
};
wtype Prim(int src) {
  memset(cost, 0x3f, sizeof(cost)); memset(vis, 0, sizeof(vis));
  wtype ret = 0;
  priority_queue<Node> que; que.push((Node) {src, cost[src] = 0});
  while (!que.empty()) {
    int u = que.top().v; que.pop();
    if (vis[u]) { continue; }
    vis[u] = true; ret += cost[u];
    for (int i = head[u]; ~i; i = nxt[i]) {
      int v = to[i];
      if (!vis[v] && cost[v] > len[i]) { cost[v] = len[i]; que.push((Node) {v, cost[v]}); }
    }
  }
  return ret;
}
//Kruskal + 邻接表 O(ElogE)
typedef int wtype;
struct Edge {
  int u, v; wtype w;
  bool operator<(const Edge &r)const { return w < r.w; }
} edge[M];
int n, fa[N], tot; //加边前赋值为0
void addedge(int u, int v, wtype w) { edge[tot].u = u; edge[tot].v = v; edge[tot++].w = w; }
int findfa(int x) { return fa[x] == -1 ? x : fa[x] = findfa(fa[x]); }
wtype Kruskal() {
  memset(fa, -1, sizeof(fa));
  sort(edge, edge + tot);
  int cnt = 0; wtype ret = 0;
  for (int i = 0; i < tot; i++) {
    int u = edge[i].u, v = edge[i].v, t1 = findfa(u), t2 = findfa(v); wtype w = edge[i].w;
    if (t1 != t2) { ret += w; fa[t1] = t2; cnt++; if (cnt == n - 1) { break; } }
  }
  if (cnt < n - 1) { return -1; } //不连通
  return ret;
}
//次小生成树
//Prim + 邻接矩阵 O(V^2 + E)
//求最小生成树时, 用数组Mx[i][j]来表示MST中i到j最大边权
//求完后, 直接枚举所有不在MST中的边, 替换掉最大边权的边, 更新答案
typedef int wtype;
const wtype INF = 0x3f3f3f3f;
int n, pre[N];
wtype mp[N][N], cost[N], Mx[N][N]; //Mx[i][j]表示在最小生成树中从i到j的路径中的最大边权
bool vis[N], used[N][N];
wtype Prim() {
  memset(Mx, 0, sizeof(Mx));
  memset(pre, 0, sizeof(pre));
  memset(vis, 0, sizeof(vis));
  memset(used, 0, sizeof(used));
  wtype ret = 0; vis[0] = true; pre[0] = -1;
  for (int i = 1; i < n; i++) { cost[i] = mp[0][i]; }
  for (int j = 1; j < n; j++) {
    int u = -1; wtype mn = INF;
    for (int j = 0; j < n; j++) {
      if (!vis[j] && mn > cost[j]) { mn = cost[j]; u = j; }
    }
    if (mn == INF) { return -1; } //原图不连通
    vis[u] = true; ret += mn;
    used[u][pre[u]] = used[pre[u]][u] = true;
    for (int v = 0; v < n; v++) {
      if (vis[v]) { Mx[v][u] = Mx[u][v] = max(Mx[v][pre[u]], cost[u]); }
      if (!vis[v] && cost[v] > mp[u][v]) { cost[v] = mp[u][v]; pre[v] = u; }
    }
  }
  return ret;
}
//最小树形图
//朱刘算法 O(VE)
typedef int wtype;
const int N = 1005;
const int M = 40005;
const wtype INF = 0x3f3f3f3f;
struct Edge { int u, v; wtype w; } edge[M];
int n, m, pre[N], id[N], vis[N];
wtype g[N][N], in[N];
wtype Zhuliu(int root) {
  wtype res = 0; int u, v;
  for (;;) {
    memset(in, 0x3f, sizeof(in));
    memset(id, -1, sizeof(id));
    memset(vis, -1, sizeof(vis));
    for (int i = 0; i < m; i++) {
      if (edge[i].u != edge[i].v && edge[i].w < in[edge[i].v]) {
        pre[edge[i].v] = edge[i].u; in[edge[i].v] = edge[i].w;
      }
    }
    for (int i = 0; i < n; i++) {
      if (i != root && in[i] == INF) { return -1; } //不存在最小树形图
    }
    int tn = 0; in[root] = 0;
    for (int i = 0; i < n; i++) {
      res += in[i]; v = i;
      while (vis[v] != i && id[v] == -1 && v != root) {
        vis[v] = i; v = pre[v];
      }
      if (v != root && id[v] == -1) {
        for (int u = pre[v]; u != v ; u = pre[u]) { id[u] = tn; }
        id[v] = tn++;
      }
    }
    if (tn == 0) { break; } //没有有向环
    for (int i = 0; i < n; i++) {
      if (id[i] == -1) { id[i] = tn++; }
    }
    for (int i = 0; i < m;) {
      v = edge[i].v; edge[i].u = id[edge[i].u]; edge[i].v = id[edge[i].v];
      if (edge[i].u != edge[i].v) { edge[i++].w -= in[v]; }
      else { swap(edge[i], edge[--m]); }
    }
    n = tn; root = id[root];
  }
  return res;
}
//POJ 3164
int main() {
  int C = 0, T, u, v, w;
  scanf("%d", &T);
  while (++C <= T) {
    memset(g, 0x3f, sizeof(g));
    scanf("%d%d", &n, &m);
    while (m--) {
      scanf("%d%d%d", &u, &v, &w);
      if (u == v) { continue; }
      g[u][v] = min(g[u][v], w);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (g[i][j] < INF) { edge[m].u = i; edge[m].v = j; edge[m++].w = g[i][j]; }
      }
    }
    wtype ans = Zhuliu(0);
    printf("Case #%d: ", C);
    if (ans == -1) { puts("Possums!"); }
    else { printf("%d\n", ans); }
  }
}
//曼哈顿距离最小生成树
//Kruskal O(VlogV)
const int INF = 0x3f3f3f3f;
int n, tot, fa[N], a[N], b[N];
struct Point {
  int x, y, id;
  bool operator<(const Point &r)const { return x < r.x || (x == r.x && y < r.y); }
} p[N];
struct Edge { //有效边
  int u, v, w;
  bool operator<(const Edge &r)const { return w < r.w; }
} edge[N << 2];
struct BIT { //树状数组, 找y - x大于当前的, 但是y + x最小的
  int mn, pos;
  void init() { mn = INF; pos = -1; }
} bit[N];
void addedge(int u, int v, int w) { edge[tot].u = u; edge[tot].v = v; edge[tot++].w = w; }
int findfa(int x) { return fa[x] == -1 ? x : fa[x] = findfa(fa[x]); }
inline int cost(const Point &a, const Point &b) { return abs(a.x - b.x) + abs(a.y - b.y); }
inline int lowbit(int x) { return x & -x; }
void update(int i, int val, int pos) {
  for (; i; i -= lowbit(i)) { if (val < bit[i].mn) { bit[i].mn = val; bit[i].pos = pos; } }
}
int query(int i, int nn) { //查询[i, nn]的最小值位置
  int mn = INF, pos = -1;
  for (; i <= nn; i += lowbit(i)) { if (bit[i].mn < mn) { mn = bit[i].mn; pos = bit[i].pos; } }
  return pos;
}
void MMST() {
  tot = 0;
  for (int d = 0; d < 4; d++) { //4种坐标变换
    if (d == 1 || d == 3) { for (int i = 0; i < n; i++) { swap(p[i].x, p[i].y); } }
    else if (d == 2) { for (int i = 0; i < n; i++) { p[i].x = -p[i].x; } }
    sort(p, p + n);
    for (int i = 0; i < n; i++) { a[i] = b[i] = p[i].y - p[i].x; }
    sort(b, b + n);
    int nn = unique(b, b + n) - b;
    for (int i = 1; i <= nn; i++) { bit[i].init(); }
    for (int i = n - 1; i >= 0; i--) {
      int pos = lower_bound(b, b + nn, a[i]) - b + 1, ans = query(pos, nn);
      if (ans != -1) { addedge(p[i].id, p[ans].id, cost(p[i], p[ans])); }
      update(pos, p[i].x + p[i].y, i);
    }
  }
}
int Kruskal() {
  MMST();
  memset(fa, -1, sizeof(fa));
  sort(edge, edge + tot);
  int ret = 0;
  for (int i = 0, k = 0; i < tot; i++) {
    int u = edge[i].u, v = edge[i].v, t1 = findfa(u), t2 = findfa(v);
    if (t1 != t2) {
      fa[t1] = t2; ret += edge[i].w;
      if (++k == n - 1) { return ret; }
    }
  }
}
//POJ3241 求曼哈顿最小生成树上第k大的边
int Kruskal(int k) {
  MMST();
  memset(fa, -1, sizeof(fa));
  sort(edge, edge + tot);
  for (int i = 0; i < tot; i++) {
    int u = edge[i].u, v = edge[i].v, t1 = findfa(u), t2 = findfa(v);
    if (t1 != t2) {
      fa[t1] = t2;
      if (--k == 0) { return edge[i].w; }
    }
  }
}
//Minimum Steiner tree O(V^3+V*2^K*(2^K+N))
//G(V, E), A是V的一个子集, 求至少包含A中所有点的最小子树
//mp[][]: 距离矩阵, 下标1 - n, id[]置为集合A中点的标号, 下标0 - n - 1
const int K = 10;
const int INF = 0x3f3f3f3f;
int mp[N][N], id[K], dp[1 << K][N], STV[N];
int MST(int n, int k) {
  memset(dp, 0x3f, sizeof(dp));
  for (int i = 0; i < k; i++) { dp[1 << i][id[i]] = 0; }
  for (int i = 1; i < 1 << k; i++) {
    for (int kk = 1; kk <= n; kk++) {
      STV[kk] = 0;
      for (int j = i & (i - 1); j; j = (j - 1) & i) {
        dp[i][kk] = min(dp[i][kk], dp[j][kk] + dp[~j & i][kk]);
      }
    }
    for (int j = 0, mn = INF, mnid = 0; j < n; j++, mn = INF) {
      for (int kk = 1; kk <= n; kk++) {
        if (dp[i][kk] <= mn && !STV[kk]) { mn = dp[i][mnid = kk]; }
      }
      STV[mnid] = 1;
      for (int kk = 1; kk <= n; kk++) {
        if (STV[kk] == 0) { dp[i][kk] = min(dp[i][kk], dp[i][mnid] + mp[mnid][kk]); }
      }
    }
  }
  return *min_element(dp[(1 << k) - 1] + 1, dp[(1 << k) - 1] + n + 1);
}
//生成树计数
//Matrix-Tree Theorem (Kirchhoff 矩阵-树定理)
//图G的度数矩阵D[G]是一个n*n的矩阵, 满足: 当i != j时,dij = 0; 当i = j时, dij等于vi的度数
//图G的邻接矩阵A[G]是一个n*n的矩阵, 满足: 如果vi vj之间有边直接相连, 则aij = 1, 否则为0
//则基尔霍夫矩阵C[G] = D[G] - A[G]
//以i为根的树形图个数 = 基尔霍夫矩阵去掉第i行第i列的行列式
