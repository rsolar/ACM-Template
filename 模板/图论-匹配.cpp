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
struct Edge {
  int to, next;
} edge[M];
int head[N], tot, uN;
int linker[N];
bool used[N];
void init() {
  tot = 0; memset(head, -1, sizeof(head));
}
void addedge(int u, int v) {
  edge[tot].to = v; edge[tot].next = head[u]; head[u] = tot++;
}
bool dfs(int u) {
  for (int i = head[u]; ~i; i = edge[i].next) {
    int v = edge[i].to;
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
struct Edge {
  int to, next;
} edge[M];
int head[N], tot, uN;
int Mx[N], My[N], pre[N], check[N];
void init() {
  tot = 0; memset(head, -1, sizeof(head));
}
void addedge(int u, int v) {
  edge[tot].to = v; edge[tot].next = head[u]; head[u] = tot++;
}
bool bfs(int src) {
  queue<int> que;
  que.push(src);
  pre[src] = -1;
  bool flag = false;
  while (!que.empty() && !flag) {
    int u = que.front(); que.pop();
    for (int i = head[u]; ~i && !flag; i = edge[i].next) {
      int v = edge[i].to;
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
//一般图最大匹配 + 邻接表 O(N*E)
struct edge_t {
  int from, to;
  edge_t *next;
};
int aug(int n, edge_t *lst[], int *match, int *v, int now) {
  int t, ret = 0; edge_t *e;
  v[now] = 1;
  for (e = lst[now]; e; e = e->next)
    if (!v[t = e->to]) {
      if (match[t] < 0) {
        match[now] = t, match[t] = now, ret = 1;
      } else {
        v[t] = 1;
        if (aug(n, lst, match, v, match[t])) {
          match[now] = t, match[t] = now, ret = 1;
        }
        v[t] = 0;
      }
      if (ret) {
        break;
      }
    }
  v[now] = 0;
  return ret;
}
int graph_match(int n, edge_t *lst[], int *match) {
  int v[N] = {0}, i, j;
  memset(match, -1, sizeof(match));
  for (i = 0, j = n; i < n && j >= 2;) {
    if (match[i] < 0 && aug(n, lst, match, v, i)) { i = 0, j -= 2; }
    else { i++; }
  }
  for (i = j = 0; i < n; i++) { j += (match[i] >= 0); }
  return j >> 1;
}
//一般图匹配带花树 + 邻接矩阵
int n; //点的编号从1到n
bool Graph[N][N];
int Match[N];
bool InQueue[N], InPath[N], InBlossom[N];
int Head, Tail, Queue[N];
int Start, Finish, NewBase;
int Father[N], Base[N];
inline void Push(int u) {
  InQueue[u] = true; Queue[Tail++] = u;
}
inline int Pop() {
  return Queue[Head++];
}
int FindCommonAncestor(int u, int v) {
  memset(InPath, 0, sizeof(InPath));
  while (true) {
    u = Base[u];
    InPath[u] = true;
    if (u == Start) { break; }
    u = Father[Match[u]];
  }
  while (true) {
    v = Base[v];
    if (InPath[v]) { break; }
    v = Father[Match[v]];
  }
  return v;
}
void ResetTrace(int u) {
  while (Base[u] != NewBase) {
    int v = Match[u];
    InBlossom[Base[u]] = InBlossom[Base[v]] = true;
    u = Father[v];
    if (Base[u] != NewBase) { Father[u] = v; }
  }
}
void BloosomContract(int u, int v) {
  NewBase = FindCommonAncestor(u, v);
  memset(InBlossom, 0, sizeof(InBlossom));
  ResetTrace(u); ResetTrace(v);
  if (Base[u] != NewBase) { Father[u] = v; }
  if (Base[v] != NewBase) { Father[v] = u; }
  for (int tu = 1; tu <= n; tu++) {
    if (InBlossom[Base[tu]]) {
      Base[tu] = NewBase;
      if (!InQueue[tu]) { Push(tu); }
    }
  }
}
void FindAugmentingPath() {
  memset(InQueue, 0, sizeof(InQueue));
  memset(Father, 0, sizeof(Father));
  for (int i = 1; i <= n; i++) { Base[i] = i; }
  Head = Tail = 1;
  Push(Start);
  Finish = 0;
  while (Head < Tail) {
    int u = Pop();
    for (int v = 1; v <= n; v++)
      if (Graph[u][v] && (Base[u] != Base[v]) && (Match[u] != v)) {
        if ((v == Start) || ((Match[v] > 0) && Father[Match[v]] > 0)) {
          BloosomContract(u, v);
        } else if (Father[v] == 0) {
          Father[v] = u;
          if (Match[v] > 0) { Push(Match[v]); }
          else { Finish = v; return; }
        }
      }
  }
}
void AugmentPath() {
  int u = Finish, v, w;
  while (u > 0) {
    v = Father[u]; w = Match[v];
    Match[v] = u; Match[u] = v;
    u = w;
  }
}
void Edmonds() {
  memset(Match, 0, sizeof(Match));
  for (int u = 1; u <= n; u++) {
    if (Match[u] == 0) {
      Start = u;
      FindAugmentingPath();
      if (Finish > 0) { AugmentPath(); }
    }
  }
}
//ural 1099
int main() {
  int u, v;
  scanf("%d", &n);
  while (~scanf("%d%d", &u, &v)) {
    Graph[u][v] = Graph[v][u] = true;
  }
  Edmonds();
  int Count = 0;
  for (int u = 1; u <= n; u++) {
    Count += (Match[u] > 0);
  }
  printf("%d\n", Count);
  for (int u = 1; u <= n; u++) {
    if (u < Match[u]) { printf("%d %d\n", u, Match[u]); }
  }
}
