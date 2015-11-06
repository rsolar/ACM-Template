//http://blog.csdn.net/wjf_wzzc/article/details/24820525

//最大流
//SAP + 邻接矩阵 O(V^2*E) (点的编号默认从0开始)
const int N = 505;
int n, g[N][N];
int dis[N], pre[N], cur[N], flow[N][N], gap[N];
int SAP(int src, int sink) {
  memset(dis, 0, sizeof(dis));
  memset(cur, 0, sizeof(cur));
  memset(flow, 0, sizeof(flow));
  memset(gap, 0, sizeof(gap));
  int u = src, maxflow = 0, aug = -1;
  pre[src] = src; gap[0] = n;
  while (dis[src] < n) {
loop:
    for (int v = cur[u]; v < n; ++v) {
      if (g[u][v] - flow[u][v] && dis[u] == dis[v] + 1) {
        if (aug == -1 || aug > g[u][v] - flow[u][v]) { aug = g[u][v] - flow[u][v]; }
        pre[v] = u; u = cur[u] = v;
        if (v == sink) {
          maxflow += aug;
          for (u = pre[u]; v != src; v = u, u = pre[u]) {
            flow[u][v] += aug; flow[v][u] -= aug;
          }
          aug = -1;
        }
        goto loop;
      }
    }
    int mindis = n - 1;
    for (int v = 0; v < n; v++) {
      if (g[u][v] - flow[u][v] && mindis > dis[v]) { cur[u] = v; mindis = dis[v]; }
    }
    if (--gap[dis[u]] == 0) { break; }
    dis[u] = mindis + 1; gap[dis[u]]++;
    u = pre[u];
  }
  return maxflow;
}
//ISAP + 邻接表 O(V^2*E)
const int N = 505;
const int M = 20005;
const int INF = 0x3f3f3f3f;
int n, head[N], to[M], Next[M], cap[M], flow[M], tot;
int dep[N], pre[N], cur[N], gap[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, int w, int rw = 0) {
  to[tot] = y; cap[tot] = w; flow[tot] = 0; Next[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = rw; flow[tot] = 0; Next[tot] = head[y]; head[y] = tot++;
}
int SAP(int src, int sink) {
  memset(dep, 0, sizeof(dep));
  memset(gap, 0, sizeof(gap));
  memcpy(cur, head, sizeof(head));
  int u = src, v, maxflow = 0;
  pre[u] = -1; gap[0] = n;
  while (dep[src] < n) {
    if (u == sink) {
      int mindis = INF;
      for (int i = pre[u]; ~i; i = pre[to[i ^ 1]]) {
        if (mindis > cap[i] - flow[i]) { mindis = cap[i] - flow[i]; }
      }
      for (int i = pre[u]; ~i; i = pre[to[i ^ 1]]) {
        flow[i] += mindis; flow[i ^ 1] -= mindis;
      }
      u = src; maxflow += mindis;
      continue;
    }
    bool flag = false;
    for (int i = cur[u]; ~i; i = Next[i]) {
      v = to[i];
      if (cap[i] - flow[i] && dep[v] + 1 == dep[u]) {
        flag = true; cur[u] = pre[v] = i; break;
      }
    }
    if (flag) { u = v; continue; }
    int mindis = n;
    for (int i = head[u]; ~i; i = Next[i]) {
      if (cap[i] - flow[i] && dep[to[i]] < mindis) { mindis = dep[to[i]]; cur[u] = i; }
    }
    if (--gap[dep[u]] == 0) { return maxflow; }
    dep[u] = mindis + 1; gap[dep[u]]++;
    if (u != src) { u = to[pre[u] ^ 1]; }
  }
  return maxflow;
}
//ISAP + bfs + stack + 邻接表 O(V^2*E)
const int N = 505;
const int M = 20005;
const int INF = 0x3f3f3f3f;
int n, head[N], to[M], Next[M], cap[M], flow[M], tot;
int dep[N], cur[N], gap[N], S[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, int w, int rw = 0) {
  to[tot] = y; cap[tot] = w; flow[tot] = 0; Next[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = rw; flow[tot] = 0; Next[tot] = head[y]; head[y] = tot++;
}
void bfs(int sink) {
  memset(dep, -1, sizeof(dep));
  memset(gap, 0, sizeof(gap));
  gap[0] = 1; dep[sink] = 0;
  queue<int> que;
  que.push(sink);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    for (int i = head[u]; ~i; i = Next[i]) {
      int v = to[i];
      if (dep[v] != -1) { continue; }
      dep[v] = dep[u] + 1; gap[dep[v]]++; que.push(v);
    }
  }
}
int SAP(int src, int sink) {
  bfs(sink);
  memcpy(cur, head, sizeof(head));
  int u = src, v, maxflow = 0, top = 0;
  while (dep[src] < n) {
    if (u == sink) {
      int mindis = INF, inser;
      for (int i = 0; i < top; i++) {
        if (mindis > cap[S[i]] - flow[S[i]]) { mindis = cap[S[i]] - flow[S[i]]; inser = i; }
      }
      for (int i = 0; i < top; ++i) {
        flow[S[i]] += mindis; flow[S[i] ^ 1] -= mindis;
      }
      maxflow += mindis; top = inser; u = to[S[top] ^ 1];
      continue;
    }
    bool flag = false;
    for (int i = cur[u]; ~i; i = Next[i]) {
      v = to[i];
      if (cap[i] - flow[i] && dep[v] + 1 == dep[u]) { flag = true; cur[u] = i; break; }
    }
    if (flag) { S[top++] = cur[u]; u = v; continue; }
    int mindis = n;
    for (int i = head[u]; ~i; i = Next[i]) {
      if (cap[i] - flow[i] && dep[to[i]] < mindis) { mindis = dep[to[i]]; cur[u] = i; }
    }
    if (--gap[dep[u]] == 0) { return maxflow; }
    dep[u] = mindis + 1; gap[dep[u]]++;
    if (u != src) { u = to[S[--top] ^ 1]; }
  }
  return maxflow;
}
//Dinic O(V^2*E)
const int N = 505;
const int M = 20005;
const int INF = 0x3f3f3f3f;
int n, head[N], to[M], Next[M], cap[M], flow[M], tot;
int dis[N], cur[N], src, sink;
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, int w, int rw = 0) {
  to[tot] = y; cap[tot] = w; flow[tot] = 0; Next[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = rw; flow[tot] = 0; Next[tot] = head[y]; head[y] = tot++;
}
bool bfs() {
  memset(dis, 0, sizeof(dis));
  queue<int> que;
  dis[src] = 1;
  que.push(src);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    for (int i = head[u]; ~i; i = Next[i]) {
      int v = to[i];
      if (cap[i] > flow[i] && !dis[v]) { dis[v] = dis[u] + 1; que.push(v); }
    }
  }
  return dis[sink];
}
int dfs(int u, int delta) {
  if (u == sink || delta == 0) { return delta; }
  int ret = 0;
  for (int &i = cur[u]; delta && ~i; i = Next[i]) {
    int v = to[i];
    if (cap[i] > flow[i] && dis[v] == dis[u] + 1) {
      int aug = dfs(v, min(cap[i] - flow[i], delta));
      if (!aug) { continue; }
      cap[i] -= aug; cap[i ^ 1] += aug;
      delta -= aug; ret += aug;
      if (!delta) { break; }
    }
  }
  return ret;
}
int dinic() {
  int ret = 0;
  while (bfs()) {
    for (int i = 0; i <= sink; ++i) { cur[i] = head[i]; }
    ret += dfs(src, INF);
  }
  return ret;
}
//最小费用最大流
const int N = 10005;
const int M = 100005;
const int INF = 0x3f3f3f3f;
struct Edge {
  int to, next, cap, flow, cost;
} edge[M];
int n, tol, head[N], pre[N], dis[N];
bool vis[N];
void init() {
  tol = 0; memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int cap, int cost) {
  edge[tol].to = v;
  edge[tol].cap = cap;
  edge[tol].cost = cost;
  edge[tol].flow = 0;
  edge[tol].next = head[u];
  head[u] = tol++;
  edge[tol].to = u;
  edge[tol].cap = 0;
  edge[tol].cost = -cost;
  edge[tol].flow = 0;
  edge[tol].next = head[v];
  head[v] = tol++;
}
bool spfa(int s, int t) {
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, 0, sizeof(vis));
  memset(pre, -1, sizeof(pre));
  queue<int> que;
  dis[s] = 0;
  vis[s] = true;
  que.push(s);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    vis[u] = false;
    for (int i = head[u]; i != -1; i = edge[i].next) {
      int v = edge[i].to;
      if (edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost) {
        dis[v] = dis[u] + edge[i].cost; pre[v] = i;
        if (!vis[v]) { vis[v] = true; que.push(v); }
      }
    }
  }
  if (pre[t] == -1) { return false; }
  else { return true; }
}
//返回的是最大流，cost存的是最小费用
int minCostMaxflow(int s, int t, int &cost) {
  int flow = 0; cost = 0;
  while (spfa(s, t)) {
    int mn = INF;
    for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
      if (mn > edge[i].cap - edge[i].flow) {
        mn = edge[i].cap - edge[i].flow;
      }
    }
    for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
      edge[i].flow += mn;
      edge[i ^ 1].flow -= mn;
      cost += edge[i].cost * mn;
    }
    flow += mn;
  }
  return flow;
}
