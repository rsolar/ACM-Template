//图论点、边集和二分图的相关概念和性质
//点覆盖: 点覆盖集即一个点集, 使得所有边至少有一个端点在集合里
//边覆盖: 边覆盖集即一个边集, 使得所有点都与集合里的边邻接
//独立集: 独立集即一个点集, 集合中任两个结点不相邻, 则称V为独立集
//团: 团即一个点集, 集合中任两个结点相邻
//边独立集: 边独立集即一个边集, 满足边集中的任两边不邻接
//支配集: 支配集即一个点集, 使得所有其他点至少有一个相邻点在集合里
//边支配集: 边支配集即一个边集, 使得所有边至少有一条邻接边在集合里
//最小路径覆盖: 用尽量少的不相交简单路径覆盖有向无环图G的所有顶点, 即每个顶点严格属于一条路径, 路径的长度可能为0(单个点)
//匹配: 匹配是一个边集, 满足边集中的边两两不邻接
//在匹配中的点称为匹配点或饱和点；反之, 称为未匹配点或未饱和点
//交错轨(alternating path): 图的一条简单路径, 满足任意相邻的两条边, 一条在匹配内, 一条不在匹配内
//增广轨(augmenting path): 是一个始点与终点都为未匹配点的交错轨
//最大匹配(maximum matching): 具有最多边的匹配
//匹配数(matching number): 最大匹配的大小
//完美匹配(perfect matching): 匹配了所有点的匹配
//完备匹配(complete matching): 匹配了二分图较小集合（二分图X, Y中小的那个）的所有点的匹配
//增广轨定理: 一个匹配是最大匹配当且仅当没有增广轨
//所有匹配算法都是基于增广轨定理: 一个匹配是最大匹配当且仅当没有增广轨
//最大匹配数 = 最小覆盖数 = 左边匹配点 + 右边未匹配点
//最小边覆盖 = 图中点的个数 - 最大匹配数 = 独立数

//二分图最大匹配
//Hungary + dfs
//邻接矩阵 O(V^2)
int uN, vN, match[N]; //左右点的数目
bool g[N][N], check[N];
bool dfs(int u) {
  for (int v = 0; v < vN; v++) {
    if (g[u][v] && !check[v]) {
      check[v] = true;
      if (match[v] == -1 || dfs(match[v])) {
        match[v] = u; match[u] = v; return true;
      }
    }
  }
  return false;
}
//邻接表 O(V*E)
int head[N], to[M], nxt[M], tot, uN, match[N];
bool check[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) { to[tot] = y; nxt[tot] = head[x]; head[x] = tot++; }
bool dfs(int u) {
  for (int i = head[u]; ~i; i = nxt[i]) {
    int v = to[i];
    if (!check[v]) {
      check[v] = true;
      if (match[v] == -1 || dfs(match[v])) {
        match[v] = u; match[u] = v; return true;
      }
    }
  }
  return false;
}
int Hungary() {
  memset(match, -1, sizeof(match));
  int res = 0;
  for (int u = 0; u < uN; u++) {
    if (match[u] == -1) {
      memset(check, 0, sizeof(check));
      if (dfs(u)) { res++; }
    }
  }
  return res;
}
//Hungary + bfs + 邻接矩阵 O(V*E)
bool g[N][N];
int uN, vN, match[N], check[N], pre[N];
int Hungary() {
  memset(match, -1, sizeof(match));
  memset(check, -1, sizeof(check));
  queue<int> que;
  int res = 0;
  for (int i = 0; i < uN; i++) {
    if (match[i] == -1) {
      while (!que.empty()) { que.pop(); }
      que.push(i); pre[i] = -1;
      bool flag = false;
      while (!que.empty() && !flag) {
        int u = que.front(); que.pop();
        for (int v = 0; v < vN && !flag; v++) {
          if (g[u][v] && check[v] != i) {
            check[v] = i; que.push(match[v]);
            if (~match[v]) { pre[match[v]] = u; }
            else {
              flag = true;
              for (int a = u, b = v; ~a;) {
                int t = match[a]; match[a] = b; match[b] = a; a = pre[a]; b = t;
              }
            }
          }
        }
      }
      if (~match[i]) { res++; }
    }
  }
  return res;
}
//Hungary + bfs + 邻接表 O(V*E)
int head[N], to[M], nxt[M], tot, uN, match[N], check[N], pre[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) { to[tot] = y; nxt[tot] = head[x]; head[x] = tot++; }
int Hungary() {
  memset(match, -1, sizeof(match));
  memset(check, -1, sizeof(check));
  queue<int> que;
  int res = 0;
  for (int i = 0; i < uN; i++) {
    if (match[i] == -1) {
      while (!que.empty()) { que.pop(); }
      que.push(i); pre[i] = -1;
      bool flag = false;
      while (!que.empty() && !flag) {
        int u = que.front(); que.pop();
        for (int i = head[u]; ~i && !flag; i = nxt[i]) {
          int v = to[i];
          if (check[v] != i) {
            check[v] = i; que.push(match[v]);
            if (~match[v]) { pre[match[v]] = u; }
            else {
              flag = true;
              for (int a = u, b = v; ~a;) {
                int t = match[a]; match[a] = b; match[b] = a; a = pre[a]; b = t;
              }
            }
          }
        }
      }
      if (~match[i]) { res++; }
    }
  }
  return res;
}
//Hopcroft-Karp + vector + O(sqrt(V)*E)
const int INF = 0x3f3f3f3f;
vector<int> g[N];
int uN, matchx[N], matchy[N], dx[N], dy[N], dis;
bool check[N];
bool SearchP() {
  memset(dx, -1, sizeof(dx));
  memset(dy, -1, sizeof(dy));
  queue<int> que; dis = INF;
  for (int i = 0; i < uN; i++) { if (matchx[i] == -1) { dx[i] = 0; que.push(i); } }
  while (!que.empty()) {
    int u = que.front(); que.pop();
    if (dx[u] > dis) { break; }
    for (size_t i = 0; i < g[u].size(); i++) {
      int v = g[u][i];
      if (dy[v] == -1) {
        dy[v] = dx[u] + 1;
        if (matchy[v] == -1) { dis = dy[v]; }
        else { dx[matchy[v]] = dy[v] + 1; que.push(matchy[v]); }
      }
    }
  }
  return dis != INF;
}
bool dfs(int u) {
  for (size_t i = 0; i < g[u].size(); i++) {
    int v = g[u][i];
    if (!check[v] && dy[v] == dx[u] + 1) {
      check[v] = true;
      if (~matchy[v] && dy[v] == dis) { continue; }
      if (matchy[v] == -1 || dfs(matchy[v])) {
        matchy[v] = u; matchx[u] = v; return true;
      }
    }
  }
  return false;
}
int HK() {
  memset(matchx, -1, sizeof(matchx));
  memset(matchy, -1, sizeof(matchy));
  int res = 0;
  while (SearchP()) {
    memset(check, 0, sizeof(check));
    for (int i = 0; i < uN; i++) {
      if (matchx[i] == -1 && dfs(i)) { res++; }
    }
  }
  return res;
}
//二分图最佳匹配
//Kuhn-Munkers + 邻接矩阵 O(uN^2*vN)
//若求最小权匹配,可将权值取相反数,结果取相反数 点的编号从0开始
const int INF = 0x3f3f3f3f;
int uN, vN, g[N][N];
int match[N], lx[N], ly[N]; //y中各点匹配状态, 可行顶标
int slack[N]; //松弛数组
bool visx[N], visy[N];
bool dfs(int u) {
  visx[u] = true;
  for (int v = 0; v < vN; v++) {
    if (visy[v]) { continue; }
    int tmp = lx[u] + ly[v] - g[u][v];
    if (tmp == 0) {
      visy[v] = true;
      if (match[v] == -1 || dfs(match[v])) { match[v] = u; return true; }
    } else if (slack[v] > tmp) { slack[v] = tmp; }
  }
  return false;
}
int KM() {
  memset(match, -1, sizeof(match));
  memset(ly, 0, sizeof(ly));
  for (int i = 0; i < uN; i++) { lx[i] = *min_element(g[i], g[i] + vN); }
  for (int u = 0; u < uN; u++) {
    memset(slack, 0x3f, sizeof(slack));
    for (;;) {
      memset(visx, 0, sizeof(visx));
      memset(visy, 0, sizeof(visy));
      if (dfs(u)) { break; }
      int d = INF;
      for (int i = 0; i < vN; i++) { if (!visy[i] && d > slack[i]) { d = slack[i]; } }
      for (int i = 0; i < uN; i++) { if (visx[i]) { lx[i] -= d; } }
      for (int i = 0; i < vN; i++) { visy[i] ? ly[i] += d : slack[i] -= d; }
    }
  }
  int res = 0;
  for (int i = 0; i < vN; i++) { if (~match[i]) { res += g[match[i]][i]; } }
  return res;
}
//二分图多重匹配
int uN, vN, g[N][N], match[N][N]; //match[i][0]为个数
int num[N]; //右边最大的匹配数
bool check[N];
bool dfs(int u) {
  for (int v = 0; v < vN; v++) {
    if (g[u][v] && !check[v]) {
      check[v] = true;
      if (match[v][0] < num[v]) { match[v][++match[v][0]] = u; return true; }
      for (int i = 1; i <= num[0]; i++) {
        if (dfs(match[v][i])) { match[v][i] = u; return true; }
      }
    }
  }
  return false;
}
int Hungary() {
  int res = 0;
  for (int i = 0; i < vN; i++) { match[i][0] = 0; }
  for (int u = 0; u < uN; u++) {
    memset(check, false, sizeof(check));
    res += dfs(u);
  }
  return res;
}
//一般图最大匹配
//邻接矩阵 O(V^3)
int n, match[N];
bool g[N][N], check[N];
bool aug(int now) {
  bool ret = false; check[now] = true;
  for (int i = 0; i < n; i++) {
    if (!check[i] && g[now][i]) {
      if (match[i] == -1) { match[now] = i; match[i] = now; ret = true; }
      else {
        check[i] = true;
        if (aug(match[i])) { match[now] = i, match[i] = now, ret = true; }
        check[i] = false;
      }
      if (ret) { break; }
    }
  }
  check[now] = false; return ret;
}
//邻接表 O(V*E)
int head[N], to[M], nxt[M], tot, match[N];
bool check[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) { to[tot] = y; nxt[tot] = head[x]; head[x] = tot++; }
bool aug(int now) {
  bool ret = false; check[now] = true;
  for (int i = head[now]; ~i; i = nxt[i]) {
    int v = to[i];
    if (!check[v]) {
      if (match[v] == -1) { match[now] = v; match[v] = now; ret = true; }
      else {
        check[v] = true;
        if (aug(match[v])) { match[now] = v; match[v] = now; ret = true; }
        check[v] = false;
      }
      if (ret) { break; }
    }
  }
  check[now] = false; return ret;
}
int graphMatch() {
  memset(match, -1, sizeof(match));
  memset(check, 0, sizeof(check));
  for (int i = 0, j = n; i < n && j >= 2; i++) {
    if (match[i] == -1 && aug(i)) { i = -1, j -= 2; }
  }
  int ret = 0;
  for (int i = 0; i < n; i++) { ret += (match[i] != -1); }
  return ret >> 1;
}
//一般图匹配带花树 + 邻接矩阵 O(N^3) 点的编号从1到n
int n, match[N], fa[N], base[N], newbase, st, ed;
bool g[N][N], inqueue[N], inpath[N], inblossom[N];
queue<int> que;
int findCommonAncestor(int u, int v) {
  memset(inpath, 0, sizeof(inpath));
  for (;;) { u = base[u]; inpath[u] = true; if (u == st) { break; } u = fa[match[u]]; }
  for (;;) { v = base[v]; if (inpath[v]) { break; } v = fa[match[v]]; }
  return v;
}
void resetTrace(int u) {
  while (base[u] != newbase) {
    int v = match[u]; inblossom[base[u]] = inblossom[base[v]] = true; u = fa[v];
    if (base[u] != newbase) { fa[u] = v; }
  }
}
void bloosomContract(int u, int v) {
  newbase = findCommonAncestor(u, v);
  memset(inblossom, 0, sizeof(inblossom));
  resetTrace(u); resetTrace(v);
  if (base[u] != newbase) { fa[u] = v; }
  if (base[v] != newbase) { fa[v] = u; }
  for (int tu = 1; tu <= n; tu++) {
    if (inblossom[base[tu]]) {
      base[tu] = newbase;
      if (!inqueue[tu]) { inqueue[tu] = true; que.push(tu); }
    }
  }
}
void findAugmentingPath() {
  memset(inqueue, 0, sizeof(inqueue));
  memset(fa, 0, sizeof(fa)); ed = 0;
  for (int i = 1; i <= n; i++) { base[i] = i; }
  while (!que.empty()) { que.pop(); }
  inqueue[st] = true; que.push(st);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    for (int v = 1; v <= n; v++) {
      if (g[u][v] && base[u] != base[v] && match[u] != v) {
        if (v == st || (match[v] > 0 && fa[match[v]] > 0)) {
          bloosomContract(u, v);
        } else if (fa[v] == 0) {
          fa[v] = u;
          if (match[v] > 0) { inqueue[match[v]] = true; que.push(match[v]); }
          else { ed = v; return; }
        }
      }
    }
  }
}
void augmentPath() {
  for (int u = ed, v, w; u > 0;) { v = fa[u]; w = match[v]; match[v] = u; match[u] = v; u = w; }
}
void Edmonds() {
  memset(match, 0, sizeof(match));
  for (int u = 1; u <= n; u++) {
    if (match[u] == 0) {
      st = u; findAugmentingPath();
      if (ed > 0) { augmentPath(); }
    }
  }
}
//ural1099
int main() {
  int u, v;
  scanf("%d", &n);
  while (~scanf("%d%d", &u, &v)) { g[u][v] = g[v][u] = true; }
  Edmonds();
  int cnt = 0;
  for (int u = 1; u <= n; u++) { cnt += (match[u] > 0); }
  printf("%d\n", cnt);
  for (int u = 1; u <= n; u++) {
    if (u < match[u]) { printf("%d %d\n", u, match[u]); }
  }
}
