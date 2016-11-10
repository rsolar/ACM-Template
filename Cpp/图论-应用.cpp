//拓扑排序 O(V^2)
//queue->普通判断用, priority_queue->字典序
//邻接矩阵
int n, mp[N][N], in[N], ret[N];
int topoSort() {
  queue<int> que; int k = 0; bool flag = false;
  for (int i = 0; i < n; i++) { if (in[i] == 0) { que.push(i); } }
  while (!que.empty()) {
    if (que.size() > 1) { flag = true; }
    int u = que.front(); que.pop(); ret[k++] = u;
    for (int v = 0; v < n; v++) {
      if (mp[u][v] && --in[v] == 0) { que.push(v); }
    }
  }
  return k < n ? -1 : flag ? 0 : 1; //有环, 不唯一, 唯一
}
//邻接表
int head[N], to[M], nxt[M], tot, n, in[N], ret[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) { to[tot] = y; nxt[tot] = head[x]; head[x] = tot++; }
bool topoSort() {
  priority_queue<int> que; int k = 0;
  for (int i = 0; i < n; i++) { if (in[i] == 0) { que.push(i); } }
  while (!que.empty()) {
    int u = que.top(); que.pop(); ret[k++] = u;
    for (int i = head[u]; ~i; i = nxt[i]) {
      if (--in[to[i]] == 0) { que.push(to[i]); }
    }
  }
  return k == n;
}
//染色判断二分图
bool col[N];
bool Color(int u) {
  for (int i = head[u]; ~i; i = nxt[i]) {
    int v = to[i];
    if (!col[v]) {
      col[v] = !col[u];
      if (!Color(v)) { return false; }
    } else if (col[v] == col[u]) { return false; }
  }
  return true;
}
//欧拉回路: 每条边只经过一次, 要求回到起点
//欧拉路径: 每条边只经过一次, 不要求回到起点
//欧拉路径的判断:
//无向图: 连通(不考虑度为0的点), 每个顶点度数都为偶数或者有且仅有两个点的度数不为偶数
//有向图: 基图连通(把边当成无向边, 同样不考虑度为0的点), 每个顶点出度等于入度
//或者有且仅有一个点的出度比入度多1, 有且仅有一个点的出度比入度少1, 其余出度等于入度
//混合图: 如果存在欧拉回路, 一点存在欧拉路径了。否则如果有且仅有两个点的(出度 - 入度)是奇数,
//那么给这个两个点加边, 判断是否存在欧拉回路
//欧拉回路判断:
//无向图: 连通(不考虑度为0的点), 每个顶点度数都为偶数
//有向图: 基图连通(同样不考虑度为0的点), 每个顶点出度等于入度
//混合图: 基图连通(不考虑度为0的点), 然后借助网络流判定
//首先给原图中的每条无向边随便指定一个方向, 将原图改为有向图G'
//设D[i]为G'中(点i的出度 - 点i的入度), 若存在D[i]为奇数, 或者图不连通, 则无解
//若初始D值都是偶数, 则将G'改装成网络: 设立源点S和汇点T
//对于每个D[i] > 0的点i, 连边<S, i>, 容量为D[i] / 2; 对于每个D[j] < 0的点j, 连边<j, T>, 容量为-D[j] / 2
//G'中的每条边在网络中仍保留, 容量为1, 求这个网络的最大流, 若S引出的所有边均满流, 则原混合图是欧拉图
//将网络中所有流量为1的不与S或T关联的边在G'中改变方向,形成的新图G''一定是有向欧拉图
//Best Theorem: 有向图中以i为起点的欧拉回路个数 = 以i为根的树形图个数 * ((每个点度数 - 1)!)。
//从某个点i出发并回到i的欧拉回路个数 = 以i为起点的欧拉回路个数 * i的度数
//欧拉回路 + 邻接矩阵 O(N^2)
//求欧拉路径/回路经过的点 支持自环和重边
int n, mp[N][N], path[N], cnt;
void dfsu(int u) {
  for (int v = n - 1; v >= 0; v--) {
    while (mp[u][v]) { mp[u][v]--; mp[v][u]--; dfsu(v); }
  }
  path[cnt++] = u;
}
void dfsd(int u) {
  for (int v = n - 1; v >= 0; v--) {
    while (mp[u][v]) { mp[u][v]--; dfsd(v); }
  }
  path[cnt++] = u;
}
//无向图 SGU101
int head[N], to[M], nxt[M], tot, deg[N], path[M], cnt;
bool vis[M];
void init() {
  tot = 0; cnt = 0;
  memset(head, -1, sizeof(head)); memset(vis, 0, sizeof(vis)); memset(deg, 0, sizeof(deg));
}
void addedge(int x, int y) {
  to[tot] = y; nxt[tot] = head[x]; head[x] = tot++;
  to[tot] = x; nxt[tot] = head[y]; head[y] = tot++;
}
void dfs(int u) {
  for (int &i = head[u]; ~i;) {
    if (!vis[i]) { vis[i] = vis[i ^ 1] = true; int t = i; dfs(to[i]); path[cnt++] = t; }
    else { i = nxt[i]; }
  }
}
int main() {
  int n, u, v;
  while (~scanf("%d", &n)) {
    init();
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &u, &v); addedge(u, v); deg[u]++; deg[v]++;
    }
    int s = -1, cnto = 0;
    for (int i = 0; i <= 6; i++) {
      if (s == -1 && deg[i] > 0) { s = i; }
      if (deg[i] & 1) { cnto++; s = i; }
    }
    if (cnto != 0 && cnto != 2) { puts("No solution"); continue; }
    dfs(s);
    if (cnt != n) { puts("No solution"); continue; }
    for (int i = 0; i < cnt; i++) {
      printf("%d %c\n", (path[i] >> 1) + 1, path[i] & 1 ? '+' : '-');
    }
  }
}
//有向图 POJ2337
//给出n个小写字母组成的单词, 要求将n个单词连接起来, 输出字典序最小的解
int head[N], to[M], nxt[M], tot, in[N], out[N], path[N], cnt;
bool vis[M];
string str[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) {
  to[tot] = y; nxt[tot] = head[x]; head[x] = tot++;
}
void dfs(int u) {
  for (int &i = head[u]; ~i;) {
    if (!vis[i]) { vis[i] = true; int t = i; dfs(to[i]); path[cnt++] = n - t - 1; }
    else { i = nxt[i]; }
  }
}
int main() {
  int T, n;
  char s[25];
  scanf("%d", &T);
  while (T--) {
    init(); cnt = 0;
    memset(vis, 0, sizeof(vis));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    scanf("%d", &n);
    for (int i = 0; i < n; i++) { scanf("%s", s); str[i] = s; }
    sort(str, str + n);
    int s = 26;
    for (int i = n - 1; i >= 0; i--) { //字典序大的先加入
      int u = str[i][0] - 'a', v = str[i][str[i].size() - 1] - 'a';
      addedge(u, v); out[u]++; in[v]++;
      s = min(s, min(u, v));
    }
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < 26; i++) {
      if (out[i] - in[i] == 1) { cnt1++; s = i; } //如果有一个出度比入度大1的点, 就从这个点出发, 否则从最小的点出发
      else if (out[i] - in[i] == -1) { cnt2++; }
      else if (out[i] - in[i] != 0) { cnt1 = 3; }
    }
    if (!((cnt1 == 0 && cnt2 == 0) || (cnt1 == 1 && cnt2 == 1))) { puts("***"); continue; }
    dfs(s);
    if (cnt != n) { puts("***"); continue; }
    for (int i = cnt - 1; i >= 0; i--) {
      printf("%s%c", str[path[i]].c_str(), i > 0 ? '.' : '\n');
    }
  }
}
//有向图 并查集 HDU1116
//判断所有单词能不能连成一串, 如果有多个重复的单词, 也必须满足这样的条件
int n, fa[N], in[N], out[N], p[N];
bool vis[N];
char s[M];
void init() {
  memset(vis, 0, sizeof(vis)); memset(in, 0, sizeof(in)); memset(out, 0, sizeof(out));
  for (int i = 0; i < N; i++) { fa[i] = i; }
}
int findfa(int n) { return n == fa[n] ? n : fa[n] = findfa(fa[n]); }
inline void unite(int x, int y) {
  x = findfa(x); y = findfa(y);
  if (x != y) { fa[y] = x; }
}
int main() {
  int T, n;
  scanf("%d", &T);
  while (T--) {
    init();
    scanf("%d", &n);
    while (n--) {
      scanf("%s", s); int u = s[0] - 'a', v = s[strlen(s) - 1] - 'a';
      unite(u, v); out[u]++; in[v]++; vis[u] = vis[v] = true;
    }
    int cnt = 0, k = 0;
    for (int i = 0; i < N; i++) {
      fa[i] = findfa(i);
      if (vis[i] && fa[i] == i) { cnt++; }
    }
    if (cnt > 1) { puts("The door cannot be opened."); continue; } //不连通
    for (int i = 0; i < N; i++) {
      if (in[i] != out[i]) { p[k++] = i; if (k > 2) { break; } }
    }
    if (k == 0 || (k == 2 && ((out[p[0]] - in[p[0]] == 1 && in[p[1]] - out[p[1]] == 1) ||
                              (out[p[1]] - in[p[1]] == 1 && in[p[0]] - out[p[0]] == 1)))) {
      puts("Ordering is possible.");
    } else { puts("The door cannot be opened."); }
  }
}
//混合图 POJ1637 (本题保证连通)
//判断欧拉回路 需ISAP + 邻接表 O(V^2*E)
int in[N], out[N];
int main() {
  int T, u, v, w;
  scanf("%d", &T);
  while (T--) {
    init();
    memset(in, 0, sizeof(in)); memset(out, 0, sizeof(out));
    scanf("%d%d", &n, &m);
    while (m--) {
      scanf("%d%d%d", &u, &v, &w); out[u]++; in[v]++;
      if (w == 0) { addedge(u, v, 1); } //双向
    }
    bool flag = true;
    for (int i = 1; i <= n; i++) {
      if (out[i] - in[i] > 0) { addedge(0, i, (out[i] - in[i]) >> 1); }
      else if (in[i] - out[i] > 0) { addedge(i, n + 1, (in[i] - out[i]) >> 1); }
      if (out[i] - in[i] & 1) { flag = false; break; }
    }
    if (!flag) { puts("impossible"); continue; }
    ISAP(0, n + 1, n + 2);
    for (int i = head[0]; ~i; i = nxt[i]) {
      if (cap[i] > 0 && cap[i] > flow[i]) { flag = false; break; }
    }
    puts(flag ? "possible" : "impossible");
  }
}
//2-SAT
//染色法 可求字典序 O(V * E) HDU 1814
int n, m;
int head[N], to[M], nxt[M], tot;
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) { to[tot] = y; nxt[tot] = head[x]; head[x] = tot++; }
int S[N], top;
bool vis[N];
bool dfs(int u) {
  if (vis[u ^ 1]) { return false; }
  if (vis[u]) { return true; }
  vis[u] = true; S[top++] = u;
  for (int i = head[u]; ~i; i = nxt[i]) {
    int v = to[i];
    if (!dfs(v)) { return false; }
  }
  return true;
}
bool twoSAT(int n) {
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n << 1; i += 2) {
    if (vis[i] || vis[i ^ 1]) { continue; }
    top = 0;
    if (!dfs(i)) {
      while (top) { vis[S[--top]] = false; }
      if (!dfs(i ^ 1)) { return false; }
    }
  }
  return true;
}
int main() {
  while (~scanf("%d%d", &n, &m)) {
    init();
    for (int i = 0, u, v; i < m; i++) {
      scanf("%d%d", &u, &v); u--; v--;
      addedge(u, v ^ 1); addedge(v, u ^ 1);
    }
    if (twoSAT(n)) {
      for (int i = 0; i < n << 1; i++) {
        if (vis[i]) { printf("%d\n", i + 1); }
      }
    } else { puts("NIE"); }
  }
}
//Tarjan强连通缩点 + 拓扑排序 求任意一组解 O(V + E) POJ 3648
int n, m;
vector<int> e[N];
int low[N], dfn[N], idx, belong[N], scc;
stack<int> stk;
bool instack[N];
inline void addedge(int u, int v) { e[u].push_back(v); }
void Tarjan(int u) {
  int v; low[u] = dfn[u] = ++idx; stk.push(u); instack[u] = true;
  for (int i = 0; i < (int)e[u].size(); i++) {
    int v = e[u][i];
    if (!dfn[v]) { Tarjan(v); low[u] = min(low[u], low[v]); }
    else if (instack[v] && low[u] > dfn[v]) { low[u] = dfn[v]; }
  }
  if (low[u] == dfn[u]) {
    scc++;
    do {
      v = stk.top(); stk.pop();
      instack[v] = false; belong[v] = scc;
    } while (v != u);
  }
}
void SCC(int n) {
  memset(dfn, 0, sizeof(dfn)); memset(instack, 0, sizeof(instack)); idx = scc = 0;
  while (!stk.empty()) { stk.pop(); }
  for (int i = 0; i < n; i++) { if (!dfn[i]) { Tarjan(i); } }
}
bool solvable(int n) {
  SCC(n << 1);
  for (int i = 0; i < n << 1; i += 2) {
    if (belong[i] == belong[i ^ 1]) { return false; }
  }
  return true;
}
vector<int> dag[N]; //缩点后的逆向DAG图
char color[N]; //染色, 为'R'是选择的
int cf[N], in[N];
void solve(int n) {
  for (int i = 1; i <= scc; i++) { dag[i].clear(); }
  memset(in, 0, sizeof(in)); memset(color, 0, sizeof(color));
  for (int u = 0; u < n << 1; u++) {
    for (int i = 0; i < (int)e[u].size(); i++) {
      int v = e[u][i];
      if (belong[u] != belong[v]) { dag[belong[v]].push_back(belong[u]); in[belong[u]]++; }
    }
  }
  for (int i = 0; i < n << 1; i += 2) {
    cf[belong[i]] = belong[i ^ 1]; cf[belong[i ^ 1]] = belong[i];
  }
  queue<int> que;
  for (int i = 1; i <= scc; i++) { if (in[i] == 0) { que.push(i); } }
  while (!que.empty()) {
    int u = que.front(); que.pop();
    if (color[u] == 0) { color[u] = 'R'; color[cf[u]] = 'B'; }
    for (int i = 0; i < (int)dag[u].size(); i++) {
      if (--in[dag[u][i]] == 0) { que.push(dag[u][i]); }
    }
  }
}
inline int get(char *s) {
  int ret = 0;
  while (isdigit(*s)) { ret = ret * 10 + *s++ - '0'; }
  return ret * 2 + (*s == 'h');
}
int main() {
  char s1[10], s2[10];
  while (scanf("%d%d", &n, &m), (n || m)) {
    for (int i = 0; i < n << 1; i++) { e[i].clear(); }
    addedge(1, 0);
    for (int i = 0, u, v; i < m; i++) {
      scanf("%s%s", s1, s2);
      u = get(s1); v = get(s2);
      addedge(u ^ 1, v); addedge(v ^ 1, u);
    }
    if (solvable(n)) {
      solve(n);
      for (int i = 1; i < n; i++) {
        printf("%d%c%c", i, color[belong[i << 1]] == 'R' ? 'w' : 'h', i == n - 1 ? '\n' : ' ');
      }
    } else { puts("bad luck"); }
  }
}
//最大团
//搜索 O(n*2^n)
bool mp[N][N]; int stk[N][N], dp[N], ansn, ans[N], tmp[N];
bool dfs(int crt, int tot) {
  if (!crt) {
    if (tot > ansn) {
      for (int i = 0; i < tot; i++) { ans[i] = tmp[i]; }
      ansn = tot; return true;
    }
    return false;
  }
  for (int i = 0, u, nxt; i < crt; i++) {
    u = stk[tot][i]; nxt = 0;
    if (crt - i + tot <= ansn) { return false; }
    if (dp[u] + tot <= ansn) { return false; }
    for (int j = i + 1; j < crt; j++) {
      int v = stk[tot][j];
      if (mp[u][v]) { stk[tot + 1][nxt++] = v; }
    }
    tmp[tot] = u;
    if (dfs(nxt, tot + 1)) { return true; }
  }
  return false;
}
int maxClique(int n) {
  ansn = 0;
  for (int i = n - 1, j, k; i >= 0; i--) {
    for (j = i + 1, k = 0; j < n; j++) {
      if (mp[i][j]) { stk[1][k++] = j; }
    }
    tmp[0] = i; dfs(k, 1); dp[i] = ansn;
  }
  return ansn;
}
//随机 O(T*n^2)
const int T = 1000;
bool mp[N][N]; int id[N], ansn, ans[N]; bool del[N];
void solve(int n) {
  memset(del, 0, sizeof(del)); int k = 0;
  for (int i = 0, j; i < n; i++) {
    if (del[i]) { continue; }
    for (j = i + 1, k++; j < n; j++) { if (!mp[id[i]][id[j]]) { del[j] = true; } }
  }
  if (k > ansn) {
    ansn = k;
    for (int i = k = 0; i < n; i++) { if (!del[i]) { ans[k++] = id[i]; } }
  }
}
void maxClique(int n) {
  for (int i = 0; i < n; i++) { id[i] = i; }
  for (int t = 0; t < T; t++) {
    for (int i = 0; i < n; i++) { swap(id[i], id[rand() % n]); } solve();
  }
}
//最大独立集
//随机 O(T*(V+E))
const int T = 1000;
int q[N], pos[N]; bool del[N];
int solve(int n) {
  int ans = 0;
  for (int t = 0; t < T; t++) {
    int ret = 0, top = n; memset(del, 0, sizeof(del));
    for (int i = 1; i <= n; i++) { q[i] = pos[i] = i; }
    while (top) {
      int x = rand() % top + 1, u = q[x]; q[x] = q[top--]; pos[q[x]] = x; ret++;
      for (int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if (!del[v]) { del[v] = true; x = pos[v]; q[x] = q[top--]; pos[q[x]] = x; }
      }
    }
    ans = max(ans, ret);
  }
  return ans;
}
