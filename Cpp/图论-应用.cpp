//拓扑排序 O(N^2)
//queue->普通判断用, priority_queue->字典序
//邻接矩阵
int n, mp[N][N], in[N], ret[N];
bool topoSort() {
  queue<int> que; int k = 0;
  for (int i = 0; i < n; i++) { if (in[i] == 0) { que.push(i); } }
  while (!que.empty()) {
    int u = que.top(); que.pop(); ret[k++] = u;
    for (int v = 0; v < n; v++) {
      if (mp[u][v] && --in[v] == 0) { que.push(v); }
    }
  }
  return k == n;
}
//邻接表
int head[N], to[M], Next[M], tot;
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) { to[tot] = y; Next[tot] = head[x]; head[x] = tot++; }
int n, in[N], ret[N];
bool topoSort() {
  priority_queue<int> que; int k = 0;
  for (int i = 0; i < n; i++) { if (in[i] == 0) { que.push(i); } }
  while (!que.empty()) {
    int u = que.top(); que.pop(); ret[k++] = u;
    for (int i = head[u]; ~i; i = Next[i]) {
      if (--in[to[i]] == 0) { que.push(to[i]); }
    }
  }
  return k == n;
}
//欧拉回路: 每条边只经过一次, 要求回到起点
//欧拉路径: 每条边只经过一次, 不要求回到起点
//欧拉路径的判断:
//无向图: 连通(不考虑度为0的点), 每个顶点度数都为偶数或者仅有两个点的度数为偶数。
//有向图: 基图连通(把边当成无向边, 同样不考虑度为0的点), 每个顶点出度等于入度
//或者有且仅有一个点的出度比入度多1, 有且仅有一个点的出度比入度少1, 其余出度等于入度。
//混合图: 如果存在欧拉回路, 一点存在欧拉路径了。否则如果有且仅有两个点的(出度 - 入度)是奇数,
//那么给这个两个点加边, 判断是否存在欧拉回路。
//欧拉回路判断:
//无向图: 连通(不考虑度为0的点), 每个顶点度数都为偶数
//有向图: 基图连通(同样不考虑度为0的点), 每个顶点出度等于入度
//混合图: 基图连通(不考虑度为0的点), 然后借助网络流判定
//首先给原图中的每条无向边随便指定一个方向(称为初始定向), 将原图改为有向图G'
//然后的任务就是改变G'中某些边(无向边转化来的)的方向使其满足每个点的入度等于出度
//设D[i]为G'中(点i的出度 - 点i的入度), 可以发现, 在改变G'中边的方向的过程中, 任何点的D值的奇偶性都不会发生改变
//而最终要求的是每个点的入度等于出度, 即每个点的D值都为0, 是偶数, 故可得:
//若初始定向得到的G'中任意一个点的D值是奇数, 那么原图中一定不存在欧拉环
//若初始D值都是偶数, 则将G'改装成网络: 设立源点S和汇点T,
//对于每个D[i] > 0的点i, 连边<S, i>, 容量为D[i] / 2; 对于每个D[j] < 0的点j, 连边<j, T>, 容量为-D[j] / 2
//G'中的每条边在网络中仍保留, 容量为1(表示该边最多只能被改变方向一次)
//求这个网络的最大流, 若S引出的所有边均满流, 则原混合图是欧拉图, 将网络中所有流量为1的中间边(就是不与S或T关联的边)
//在G'中改变方向,形成的新图G''一定是有向欧拉图; 若S引出的边中有的没有满流, 则原混合图不是欧拉图
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
int head[N], to[M], Next[M], tot, deg[N], path[M], cnt;
bool vis[M];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) {
  to[tot] = y; Next[tot] = head[x]; head[x] = tot++;
  to[tot] = x; Next[tot] = head[y]; head[y] = tot++;
}
void dfs(int u) {
  for (int &i = head[u]; ~i;) {
    if (!vis[i]) { vis[i] = vis[i ^ 1] = true; int t = i; dfs(to[i]); path[cnt++] = t; }
    else { i = Next[i]; }
  }
}
int main() {
  int n, u, v;
  while (~scanf("%d", &n)) {
    init(); cnt = 0;
    memset(vis, 0, sizeof(vis)); memset(deg, 0, sizeof(deg));
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
int head[N], to[M], Next[M], tot, in[N], out[N], path[N], cnt;
bool vis[M];
string str[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y) {
  to[tot] = y; Next[tot] = head[x]; head[x] = tot++;
}
void dfs(int u) {
  for (int &i = head[u]; ~i;) {
    if (!vis[i]) { vis[i] = true; int t = i; dfs(to[i]); path[cnt++] = n - t - 1; }
    else { i = Next[i]; }
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
int findfa(int n) {
  return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}
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
    for (int i = head[0]; ~i; i = Next[i]) {
      if (cap[i] > 0 && cap[i] > flow[i]) { flag = false; break; }
    }
    puts(flag ? "possible" : "impossible");
  }
}
//2-SAT
//染色法
const int N = 20005;
const int M = 100005;
struct Edge {
  int to, next;
} edge[M];
int head[N], tot;
bool vis[N]; //染色标记
int S[N], top; //栈
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int u, int v) { edge[tot].to = v; edge[tot].next = head[u]; head[u] = tot++; }
bool dfs(int u) {
  if (vis[u ^ 1]) { return false; }
  if (vis[u]) { return true; }
  vis[u] = true;
  S[top++] = u;
  for (int i = head[u]; i != -1; i = edge[i].next) {
    if (!dfs(edge[i].to)) { return false; }
  }
  return true;
}
bool twoSat(int n) {
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n; i += 2) {
    if (vis[i] || vis[i ^ 1]) { continue; }
    top = 0;
    if (!dfs(i)) {
      while (top) { vis[S[--top]] = false; }
      if (!dfs(i ^ 1)) { return false; }
    }
  }
  return true;
}
//HDU1814
int main() {
  int n, m, u, v;
  while (scanf("%d%d", &n, &m) == 2) {
    init();
    while (m--) {
      scanf("%d%d", &u, &v); u--; v--;
      addedge(u, v ^ 1); addedge(v, u ^ 1);
    }
    if (Twosat(n << 1)) {
      for (int i = 0; i < 2 * n; i++) {
        if (vis[i]) { printf("%d\n", i + 1); }
      }
    } else { printf("NIE\n"); }
  }
}
//Tarjan强连通缩点
const int N = 1005;
const int M = 100005;
struct Edge {
  int to, next;
} edge[M];
int head[N], tot;
void init() {
  tot = 0; memset(head, -1, sizeof(head));
}
void addedge(int u, int v) {
  edge[tot].to = v; edge[tot].next = head[u]; head[u] = tot++;
}
int Low[N], DFN[N], Stack[N], Belong[N]; //Belong数组的值1~scc
int Index, top;
int scc;
bool Instack[N];
int num[N];
void Tarjan(int u) {
  int v;
  Low[u] = DFN[u] = ++Index;
  Stack[top++] = u;
  Instack[u] = true;
  for (int i = head[u]; i != -1; i = edge[i].next) {
    v = edge[i].to;
    if (!DFN[v]) {
      Tarjan(v);
      if (Low[u] > Low[v]) { Low[u] = Low[v]; }
    } else if (Instack[v] && Low[u] > DFN[v]) {
      Low[u] = DFN[v];
    }
  }
  if (Low[u] == DFN[u]) {
    scc++;
    do {
      v = Stack[--top];
      Instack[v] = false;
      Belong[v] = scc;
      num[scc]++;
    } while (v != u);
  }
}
bool solvable(int n) { //n是总个数,需要选择一半
  memset(DFN, 0, sizeof(DFN));
  memset(Instack, false, sizeof(Instack));
  memset(num, 0, sizeof(num));
  Index = scc = top = 0;
  for (int i = 0; i < n; i++) {
    if (!DFN[i]) { Tarjan(i); }
  }
  for (int i = 0; i < n; i += 2) {
    if (Belong[i] == Belong[i ^ 1]) { return false; }
  }
  return true;
}
//拓扑排序求任意一组解部分
queue<int> q1, q2;
vector<vector<int>> dag; //缩点后的逆向DAG图
char color[N]; //染色, 为'R'是选择的
int indeg[N]; //入度
int cf[N];
void solve(int n) {
  dag.assign(scc + 1, vector<int>());
  memset(indeg, 0, sizeof(indeg));
  memset(color, 0, sizeof(color));
  for (int u = 0; u < n; u++) {
    for (int i = head[u]; i != -1; i = edge[i].next) {
      int v = edge[i].to;
      if (Belong[u] != Belong[v]) {
        dag[Belong[v]].push_back(Belong[u]);
        indeg[Belong[u]]++;
      }
    }
  }
  for (int i = 0; i < n; i += 2) {
    cf[Belong[i]] = Belong[i ^ 1];
    cf[Belong[i ^ 1]] = Belong[i];
  }
  while (!q1.empty()) { q1.pop(); }
  while (!q2.empty()) { q2.pop(); }
  for (int i = 1; i <= scc; i++) {
    if (indeg[i] == 0) { q1.push(i); }
  }
  while (!q1.empty()) {
    int u = q1.front(); q1.pop();
    if (color[u] == 0) {
      color[u] = 'R'; color[cf[u]] = 'B';
    }
    int sz = dag[u].size();
    for (int i = 0; i < sz; i++) {
      indeg[dag[u][i]]--;
      if (indeg[dag[u][i]] == 0) { q1.push(dag[u][i]); }
    }
  }
}
int change(char s[]) {
  int ret = 0, i = 0;
  while (s[i] >= '0' && s[i] <= '9') {
    ret *= 10; ret += s[i++] - '0';
  }
  if (s[i] == 'w') { return 2 * ret; }
  else { return 2 * ret + 1; }
}
//POJ3648
int main() {
  int n, m;
  char s1[10], s2[10];
  while (scanf("%d%d", &n, &m) == 2) {
    if (n == 0 && m == 0) { break; }
    init();
    while (m--) {
      scanf("%s%s", s1, s2);
      int u = change(s1);
      int v = change(s2);
      addedge(u ^ 1, v);
      addedge(v ^ 1, u);
    }
    addedge(1, 0);
    if (solvable(2 * n)) {
      solve(2 * n);
      for (int i = 1; i < n; i++) {
        //注意这一定是判断color[Belong[
        if (color[Belong[2 * i]] == 'R') { printf("%dw", i); }
        else { printf("%dh", i); }
        if (i < n - 1) { printf(" "); }
        else { printf("\n"); }
      }
    } else { printf("bad luck\n"); }
  }
}
