//二分图最大权匹配
//Hungary + dfs + 邻接矩阵 O(V*E)
int g[N][N], uN, vN; //左右点的数目, 使用前赋值
int linker[N];
bool used[N];
bool dfs(int u) {
  for (int v = 0; v < vN; v++) {
    if (g[u][v] && !used[v]) {
      used[v] = true;
      if (linker[v] == -1 || dfs(linker[v])) {
        linker[v] = u; return true;
      }
    }
  }
  return false;
}
int Hungary() {
  int res = 0;
  memset(linker, -1, sizeof(linker));
  for (int u = 0; u < uN; u++) {
    memset(used, 0, sizeof(used));
    if (dfs(u)) { res++; }
  }
  return res;
}
//Hungary + dfs + 邻接表 O(V*E)
int head[N], to[M], Next[M], tot;
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, int z) { to[tot] = y; Next[tot] = head[x]; head[x] = tot++; }
int uN, linker[N];
bool dfs(int u) {
  for (int i = head[u]; ~i; i = Next[i]) {
    int v = to[i];
    if (!used[v]) {
      used[v] = true;
      if (linker[v] == -1 || dfs(linker[v])) {
        linker[v] = u; return true;
      }
    }
  }
  return false;
}
int Hungary() {
  int res = 0;
  memset(linker, -1, sizeof(linker));
  for (int u = 0; u < uN; u++) {
    memset(used, false, sizeof(used));
    if (dfs(u)) { res++; }
  }
  return res;
}
//Hungary + bfs + 邻接矩阵 O(V*E)
int g[N][N], uN, vN;
int Mx[N], My[N], check[N], pre[N];
bool bfs(int src) {
  queue<int> que;
  que.push(src);
  pre[src] = -1;
  bool flag = false;
  while (!que.empty() && !flag) {
    int u = que.front(); que.pop();
    for (int v = 0; v < vN && !flag; v++) {
      if (g[u][v] && check[v] != src) {
        check[v] = src;
        que.push(My[v]);
        if (~My[v]) { pre[My[v]] = u; }
        else {
          flag = true;
          int a = u, b = v;
          while (~a) {
            int t = Mx[a];
            Mx[a] = b; My[b] = a;
            a = pre[a]; b = t;
          }
        }
      }
    }
  }
  return Mx[src] != -1;
}
int Hungary() {
  memset(Mx, -1, sizeof(Mx));
  memset(My, -1, sizeof(My));
  memset(check, -1, sizeof(check));
  int res = 0;
  for (int i = 0; i < uN; i++) {
    if (Mx[i] == -1 && bfs(i)) { res++; }
  }
  return res;
}
//Hungary + bfs + 邻接表 O(V*E)
int head[N], to[M], Next[M], tot;
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, int z) { to[tot] = y; Next[tot] = head[x]; head[x] = tot++; }
int uN, Mx[N], My[N], pre[N], check[N];
bool bfs(int src) {
  queue<int> que;
  que.push(src);
  pre[src] = -1;
  bool flag = false;
  while (!que.empty() && !flag) {
    int u = que.front(); que.pop();
    for (int i = head[u]; ~i && !flag; i = Next[i]) {
      int v = to[i];
      if (check[v] != src) {
        check[v] = src;
        que.push(My[v]);
        if (~My[v]) { pre[My[v]] = u; }
        else {
          int a = u, b = v;
          flag = true;
          while (~a) {
            int t = Mx[a];
            Mx[a] = b; My[b] = a;
            a = pre[a]; b = t;
          }
        }
      }
    }
  }
  return Mx[src] != -1;
}
int Hungary() {
  memset(Mx, -1, sizeof(Mx));
  memset(My, -1, sizeof(My));
  memset(check, -1, sizeof(check));
  int ret = 0;
  for (int i = 0; i < uN; i++) {
    if (Mx[i] == -1 && bfs(i)) { ret++; }
  }
  return ret;
}
//Hopcroft-Karp + vector存边 + O(V^0.5*E)
const int INF = 0x3f3f3f3f;
vector<int> g[N];
int uN;
int Mx[N], My[N], dx[N], dy[N], dis;
bool used[N];
bool SearchP() {
  queue<int> que;
  dis = INF;
  memset(dx, -1, sizeof(dx));
  memset(dy, -1, sizeof(dy));
  for (int i = 0; i < uN; i++) { if (Mx[i] == -1) { dx[i] = 0; que.push(i); } }
  while (!que.empty()) {
    int u = que.front(); que.pop();
    if (dx[u] > dis) { break; }
    for (int i = 0; i < g[u].size(); i++) {
      int v = g[u][i];
      if (dy[v] == -1) {
        dy[v] = dx[u] + 1;
        if (My[v] == -1) { dis = dy[v]; }
        else { dx[My[v]] = dy[v] + 1; que.push(My[v]); }
      }
    }
  }
  return dis != INF;
}
bool dfs(int u) {
  for (int i = 0; i < g[u].size(); i++) {
    int v = g[u][i];
    if (!used[v] && dy[v] == dx[u] + 1) {
      used[v] = true;
      if (My[v] != -1 && dy[v] == dis) { continue; }
      if (My[v] == -1 || dfs(My[v])) {
        My[v] = u; Mx[u] = v; return true;
      }
    }
  }
  return false;
}
int HopcroftKarp() {
  memset(Mx, -1, sizeof(Mx));
  memset(My, -1, sizeof(My));
  int res = 0;
  while (SearchP()) {
    memset(used, 0, sizeof(used));
    for (int i = 0; i < uN; i++)
      if (Mx[i] == -1 && dfs(i)) { res++; }
  }
  return res;
}
//二分图最佳匹配
//Kuhn-Munkers + 邻接矩阵 O(uN^2*vN)
//若求最小权匹配,可将权值取相反数,结果取相反数 点的编号从0开始
const int INF = 0x3f3f3f3f;
int uN, vN, g[N][N]; //点数 二分图描述
int linker[N], lx[N], ly[N]; //y中各点匹配状态, x,y中的点标号
int slack[N];
bool visx[N], visy[N];
bool dfs(int x) {
  visx[x] = true;
  for (int y = 0; y < vN; y++) {
    if (visy[y]) { continue; }
    int tmp = lx[x] + ly[y] - g[x][y];
    if (tmp == 0) {
      visy[y] = true;
      if (linker[y] == -1 || dfs(linker[y])) {
        linker[y] = x; return true;
      }
    } else if (slack[y] > tmp) {
      slack[y] = tmp;
    }
  }
  return false;
}
int KM() {
  memset(linker, -1, sizeof(linker));
  memset(ly, 0, sizeof(ly));
  for (int i = 0; i < uN; i++) {
    lx[i] = -INF;
    for (int j = 0; j < vN; j++) {
      if (g[i][j] > lx[i]) { lx[i] = g[i][j]; }
    }
  }
  for (int x = 0; x < uN; x++) {
    memset(slack, 0x3f, sizeof(slack));
    for (;;) {
      memset(visx, false, sizeof(visx));
      memset(visy, false, sizeof(visy));
      if (dfs(x)) { break; }
      int d = INF;
      for (int i = 0; i < vN; i++) {
        if (!visy[i] && d > slack[i]) { d = slack[i]; }
      }
      for (int i = 0; i < uN; i++) {
        if (visx[i]) { lx[i] -= d; }
      }
      for (int i = 0; i < vN; i++) {
        if (visy[i]) { ly[i] += d; }
        else { slack[i] -= d; }
      }
    }
  }
  int res = 0;
  for (int i = 0; i < vN; i++) {
    if (linker[i] != -1) { res += g[linker[i]][i]; }
  }
  return res;
}
//一般图最大匹配 + 邻接矩阵 O(V^3)
//传入图的顶点数n和邻接阵mat
//返回匹配顶点对数, match返回匹配, 未匹配顶点match值为-1
int n, g[N][N], match[N];
bool vis[N];
bool aug(int now) {
  bool ret = false;
  vis[now] = true;
  for (int i = 0; i < n; i++) {
    if (!vis[i] && g[now][i]) {
      if (match[i] < 0) { match[now] = i; match[i] = now; ret = true; }
      else {
        vis[i] = true;
        if (aug(match[i])) { match[now] = i, match[i] = now, ret = true; }
        vis[i] = false;
      }
      if (ret) { break; }
    }
  }
  vis[now] = false;
  return ret;
}
int graphMatch() {
  memset(match, -1, sizeof(match));
  memset(vis, 0, sizeof(vis));
  int i, j;
  for (i = 0, j = n; i < n && j >= 2; i++) {
    if (match[i] < 0 && aug(i)) { i = -1, j -= 2; }
  }
  for (i = j = 0; i < n; i++) { j += (match[i] >= 0); }
  return j >> 1;
}
//一般图最大匹配 + 邻接表 O(V*E)
int head[N], to[M], Next[M], tot;
int match[N];
bool vis[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) { to[tot] = y; Next[tot] = head[x]; head[x] = tot++; }
bool aug(int now) {
  bool ret = false;
  vis[now] = true;
  for (int i = head[now]; ~i; i = Next[i]) {
    int v = to[i];
    if (!vis[v]) {
      if (match[v] < 0) { match[now] = v; match[v] = now; ret = true; }
      else {
        vis[v] = true;
        if (aug(match[v])) { match[now] = v; match[v] = now; ret = true; }
        vis[v] = false;
      }
      if (ret) { break; }
    }
  }
  vis[now] = false;
  return ret;
}
int graphMatch() {
  memset(match, -1, sizeof(match));
  memset(vis, 0, sizeof(vis));
  int i, j;
  for (i = 0, j = n; i < n && j >= 2; i++) {
    if (match[i] < 0 && aug(i)) { i = -1, j -= 2; }
  }
  for (i = j = 0; i < n; i++) { j += (match[i] >= 0); }
  return j >> 1;
}
//一般图匹配带花树 + 邻接矩阵 O(N^3)
int n; //点的编号从1到n
bool g[N][N], inqueue[N], inpath[N], inblossom[N];
int match[N], fa[N], base[N], newbase, st, ed;
queue<int> que;
int findCommonAncestor(int u, int v) {
  memset(inpath, 0, sizeof(inpath));
  for (;;) {
    u = base[u]; inpath[u] = true;
    if (u == st) { break; }
    u = fa[match[u]];
  }
  for (;;) {
    v = base[v];
    if (inpath[v]) { break; }
    v = fa[match[v]];
  }
  return v;
}
void resetTrace(int u) {
  while (base[u] != newbase) {
    int v = match[u];
    inblossom[base[u]] = inblossom[base[v]] = true; u = fa[v];
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
  memset(fa, 0, sizeof(fa));
  for (int i = 1; i <= n; i++) { base[i] = i; }
  while (!que.empty()) { que.pop(); }
  inqueue[st] = true; que.push(st);
  ed = 0;
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
  int u = ed, v, w;
  while (u > 0) { v = fa[u]; w = match[v]; match[v] = u; match[u] = v; u = w; }
}
void Edmonds() {
  memset(match, 0, sizeof(match));
  for (int u = 1; u <= n; u++) {
    if (match[u] == 0) {
      st = u;
      findAugmentingPath();
      if (ed > 0) { augmentPath(); }
    }
  }
}
//ural1099
int main() {
  int u, v;
  scanf("%d", &n);
  while (~scanf("%d%d", &u, &v)) {
    g[u][v] = g[v][u] = true;
  }
  Edmonds();
  int cnt = 0;
  for (int u = 1; u <= n; u++) { cnt += (match[u] > 0); }
  printf("%d\n", cnt);
  for (int u = 1; u <= n; u++) {
    if (u < match[u]) { printf("%d %d\n", u, match[u]); }
  }
}
