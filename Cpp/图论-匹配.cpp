//二分图最大匹配
//Hungary + dfs + 邻接矩阵 O(V*E)
bool g[N][N];
int uN, vN; //左右点的数目
int match[N];
bool check[N];
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
//Hungary + dfs + 邻接表 O(V*E)
int head[N], to[M], Next[M], tot;
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) { to[tot] = y; Next[tot] = head[x]; head[x] = tot++; }
int uN, match[N];
bool dfs(int u) {
  for (int i = head[u]; ~i; i = Next[i]) {
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
int uN, vN;
int match[N], check[N], pre[N];
int Hungary() {
  memset(match, -1, sizeof(match));
  memset(check, -1, sizeof(check));
  queue<int> que;
  int res = 0;
  for (int i = 0; i < uN; i++) {
    if (match[i] == -1) {
      while (!que.empty()) { que.pop(); }
      que.push(i);
      pre[i] = -1;
      bool flag = false;
      while (!que.empty() && !flag) {
        int u = que.front(); que.pop();
        for (int v = 0; v < vN && !flag; v++) {
          if (g[u][v] && check[v] != i) {
            check[v] = i;
            que.push(match[v]);
            if (~match[v]) { pre[match[v]] = u; }
            else {
              flag = true;
              int a = u, b = v;
              while (~a) {
                int t = match[a]; match[a] = b; match[b] = a;
                a = pre[a]; b = t;
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
int head[N], to[M], Next[M], tot;
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) { to[tot] = y; Next[tot] = head[x]; head[x] = tot++; }
int uN, match[N], check[N], pre[N];
int Hungary() {
  memset(match, -1, sizeof(match));
  memset(check, -1, sizeof(check));
  queue<int> que;
  int res = 0;
  for (int i = 0; i < uN; i++) {
    if (match[i] == -1) {
      while (!que.empty()) { que.pop(); }
      que.push(i);
      pre[i] = -1;
      bool flag = false;
      while (!que.empty() && !flag) {
        int u = que.front(); que.pop();
        for (int i = head[u]; ~i && !flag; i = Next[i]) {
          int v = to[i];
          if (g[u][v] && check[v] != i) {
            check[v] = i;
            que.push(match[v]);
            if (~match[v]) { pre[match[v]] = u; }
            else {
              flag = true;
              int a = u, b = v;
              while (~a) {
                int t = match[a]; match[a] = b; match[b] = a;
                a = pre[a]; b = t;
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
  queue<int> que;
  dis = INF;
  memset(dx, -1, sizeof(dx));
  memset(dy, -1, sizeof(dy));
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
