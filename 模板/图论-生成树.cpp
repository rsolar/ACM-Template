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
int n, fa[N], tot; //加边前赋值为0
void addedge(int u, int v, int w) { edge[tot].u = u; edge[tot].v = v; edge[tot++].w = w; }
int findfa(int x) { return fa[x] == -1 ? x : fa[x] = findfa(fa[x]); }
int Kruskal() {
  memset(fa, -1, sizeof(fa));
  sort(edge, edge + tot);
  int cnt = 0, ret = 0;
  for (int i = 0; i < tot; i++) {
    int u = edge[i].u, v = edge[i].v, w = edge[i].w, t1 = findfa(u), t2 = findfa(v);
    if (t1 != t2) { ret += w; fa[t1] = t2; cnt++; }
    if (cnt == n - 1) { break; }
  }
  if (cnt < n - 1) { return -1; } //不连通
  return ret;
}
//曼哈顿距离最小生成树
//Kruskal O(VlogV)
const int N = 100005;
const int INF = 0x3f3f3f3f;
struct Point {
  int x, y, id;
  bool operator<(const Point &r)const { return x < r.x || (x == r.x && y < r.y); }
} p[N];
struct Edge { //有效边
  int u, v, w;
  bool operator<(const Edge &r)const { return w < r.w; }
} edge[N << 2];
struct BIT { //树状数组, 找y-x大于当前的, 但是y+x最小的
  int min_val, pos;
  void init() { min_val = INF; pos = -1; }
} bit[N];
int n, tot, fa[N];
int a[N], b[N];
void addedge(int u, int v, int w) { edge[tot].u = u; edge[tot].v = v; edge[tot++].w = w; }
int findfa(int x) { return fa[x] == -1 ? x : fa[x] = findfa(fa[x]); }
int dist(Point a, Point b) { return abs(a.x - b.x) + abs(a.y - b.y); }
int lowbit(int x) { return x & (-x); }
void update(int i, int val, int pos) {
  for (; i > 0; i -= lowbit(i)) {
    if (val < bit[i].min_val) { bit[i].min_val = val; bit[i].pos = pos; }
  }
}
int query(int i, int m) { //查询[i, m]的最小值位置
  int min_val = INF, pos = -1;
  for (; i <= m; i += lowbit(i)) {
    if (bit[i].min_val < min_val) { min_val = bit[i].min_val; pos = bit[i].pos; }
  }
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
    int m = unique(b, b + n) - b;
    for (int i = 1; i <= m; i++) { bit[i].init(); }
    for (int i = n - 1 ; i >= 0; i--) {
      int pos = lower_bound(b, b + m, a[i]) - b + 1, ans = query(pos, m);
      if (ans != -1) { addedge(p[i].id, p[ans].id, dist(p[i], p[ans])); }
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
  MMST(n, p);
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
//Kruskal + 邻接表 O(VElogE)
const int N = 1005;
const int M = 100005;
const int INF = 0x3f3f3f3f;
struct Edge {
  int u, v, w;
  bool operator<(const Edge &r)const { return w < r.w; }
} edge[M];
int n, fa[N], path[N], tot; //加边前赋值为0
void addedge(int u, int v, int w) { edge[tot].u = u; edge[tot].v = v; edge[tot++].w = w; }
int findfa(int x) { return fa[x] == -1 ? x : fa[x] = findfa(fa[x]); }
int Kruskal() {
  memset(fa, -1, sizeof(fa));
  sort(edge, edge + tot);
  int cnt = 0, ret = 0;
  for (int i = 0; i < tot; i++) {
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
    for (int i = 0; i < tot; i++) {
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
//最小树形图
//朱刘算法 O(VE)
typedef int T; //数据类型
const int N = 1005;
const int M = 40005;
const int INF = 0x3f3f3f3f;
struct Edge {
  int u, v; T w;
} edge[M];
int n, m, pre[N], id[N], vis[N];
T g[N][N], in[N];
T Zhuliu(int root) {
  T res = 0; int u, v;
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
    int tn = 0;
    in[root] = 0;
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
    int ans = Zhuliu(0);
    printf("Case #%d: ", C);
    if (ans == -1) { puts("Possums!"); }
    else { printf("%d\n", ans); }
  }
}
//生成树计数
//Matrix-Tree定理(Kirchhoff 矩阵-树定理)
//1、G的度数矩阵D[G]是一个n*n的矩阵, 并且满足: 当i ≠ j时,dij = 0; 当i = j时, dij等于vi的度数
//2、G的邻接矩阵A[G]也是一个n*n的矩阵, 并且满足: 如果vi vj之间有边直接相连, 则aij = 1, 否则为0
//我们定义G的Kirchhoff矩阵(也称为拉普拉斯算子)C[G]为C[G] = D[G] - A[G], 则Matrix-Tree定理可以
//描述为: G的所有不同的生成树的个数等于其Kirchhoff矩阵C[G]任何一个n - 1阶主子式的行列式的绝对值
//所谓n - 1阶主子式, 就是对于r(1 ≤ r ≤ n), 将C[G]的第r行、第r列同时去掉后得到的新矩阵, 用Cr[G]表示。
//HDU4305 计数对10007取模
const int M = 10007;
struct Matrix {
  int mat[N][N];
  void init() { memset(mat, 0, sizeof(mat)); }
  int det(int n) { //求行列式的值模上M，需要使用逆元
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        mat[i][j] = (mat[i][j] % M + M) % M;
      }
    }
    int res = 1;
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++)
        if (mat[j][i] != 0) {
          for (int k = i; k < n; k++) { swap(mat[i][k], mat[j][k]); }
          if (i != j) { res = (-res + M) % M; }
          break;
        }
      if (mat[i][i] == 0) { res = -1; break; } //不存在(也就是行列式值为0)
      for (int j = i + 1; j < n; j++) {
        //int mut = (mat[j][i] * Inv[mat[i][i]]) % M; //打表逆元
        int mut = (mat[j][i] * inv(mat[i][i], M)) % M;
        for (int k = i; k < n; k++) {
          mat[j][k] = (mat[j][k] - (mat[i][k] * mut) % M + M) % M;
        }
      }
      res = (res * mat[i][i]) % M;
    }
    return res;
  }
};
Matrix ret;
ret.init();
for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j++) {
    if (i != j && g[i][j]) {
      ret.mat[i][j] = -1; ret.mat[i][i]++;
    }
  }
}
printf("%d\n", ret.det(n - 1));
//SPOJ104 不取模
const double eps = 1e-8;
const int N = 105;
bool g[N][N];
double a[N][N], b[N][N];
inline int sgn(double x) {
  if (fabs(x) < eps) { return 0; }
  if (x < 0) { return -1; }
  else { return 1; }
}
double det(double a[][N], int n) {
  double ret = 1.0; int sign = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      b[i][j] = a[i][j];
    }
  }
  for (int i = 0, j; i < n; i++) {
    if (sgn(b[i][i]) == 0) {
      for (j = i + 1; j < n; j++) {
        if (sgn(b[j][i]) != 0) { break; }
      }
      if (j == n) { return 0; }
      for (int k = i; k < n; k++) { swap(b[i][k], b[j][k]); }
      sign++;
    }
    ret *= b[i][i];
    for (int k = i + 1; k < n; k++) { b[i][k] /= b[i][i]; }
    for (int j = i + 1; j < n; j++) {
      for (int k = i + 1; k < n; k++) {
        b[j][k] -= b[j][i] * b[i][k];
      }
    }
  }
  if (sign & 1) { ret = -ret; }
  return ret;
}
int main() {
  int T, n, m, u, v;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    memset(g, 0, sizeof(g));
    memset(a, 0, sizeof(a));
    while (m--) {
      scanf("%d%d", &u, &v); u--; v--;
      g[u][v] = g[v][u] = true;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i != j && g[i][j]) {
          a[i][j] = -1; a[i][i]++;
        }
      }
    }
    printf("%.0lf\n", det(a, n - 1));
  }
}
