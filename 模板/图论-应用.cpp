//拓扑排序 + 邻接阵 O(n^2)
bool topoSort(int n, int mp[][N], int *ret) {
  int d[N], i, j, k;
  for (i = 0; i < n; i++) {
    for (d[i] = j = 0; j < n; d[i] += mp[j++][i]);
  }
  for (k = 0; k < n; ret[k++] = i) {
    for (i = 0; d[i] && i < n; i++);
    if (i == n) { return false; }
    for (d[i] = -1, j = 0; j < n; j++) {
      d[j] -= mp[i][j];
    }
  }
  return true;
}

//欧拉回路 + 邻接阵 O(n^2)
//求欧拉回路或欧拉路
//返回路径长度,path返回路径(有向图时得到的是反向路径)
//可以有自环与重边,分为无向图和有向图
void find_path_u(int n, int mp[][N], int now, int &step, int *path) {
  for (int i = n - 1; i >= 0; i--) {
    while (mp[now][i]) {
      mp[now][i]--; mp[i][now]--;
      find_path_u(n, mp, i, step, path);
    }
  }
  path[step++] = now;
}

void find_path_d(int n, int mp[][N], int now, int &step, int *path) {
  for (int i = n - 1; i >= 0; i--) {
    while (mp[now][i]) {
      mp[now][i]--;
      find_path_d(n, mp, i, step, path);
    }
  }
  path[step++] = now;
}

int euclid_path(int n, int mp[][N], int start, int *path) {
  int ret = 0;
  find_path_u(n, mp, start, ret, path);
  //find_path_d(n, mp, start, ret, path);
  return ret;
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
void init() {
  tot = 0; memset(head, -1, sizeof(head));
}

void addedge(int u, int v) {
  edge[tot].to = v; edge[tot].next = head[u]; head[u] = tot++;
}

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
//HDU 1814
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

//强连通缩点
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
queue<int>q1, q2;
vector<vector<int> > dag; //缩点后的逆向DAG图
char color[N]; //染色，为'R'是选择的
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
    if (indeg[i] == 0) {
      q1.push(i);
    }
  }
  while (!q1.empty()) {
    int u = q1.front(); q1.pop();
    if (color[u] == 0) {
      color[u] = 'R';
      color[cf[u]] = 'B';
    }
    int sz = dag[u].size();
    for (int i = 0; i < sz; i++) {
      indeg[dag[u][i]]--;
      if (indeg[dag[u][i]] == 0) {
        q1.push(dag[u][i]);
      }
    }
  }
}

int change(char s[]) {
  int ret = 0;
  int i = 0;
  while (s[i] >= '0' && s[i] <= '9') {
    ret *= 10;
    ret += s[i] - '0';
    i++;
  }
  if (s[i] == 'w') { return 2 * ret; }
  else { return 2 * ret + 1; }
}
//POJ 3648
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
