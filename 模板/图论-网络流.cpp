//http://blog.csdn.net/wjf_wzzc/article/details/24820525

//最大流
//SAP + 邻接矩阵 O(N^2*M) (点的编号默认从0开始)
const int N = 505;
int g[N][N];
int gap[N], dis[N], pre[N], cur[N], flow[N][N];
int SAP(int src, int sink, int nodenum) {
  memset(cur, 0, sizeof(cur));
  memset(dis, 0, sizeof(dis));
  memset(gap, 0, sizeof(gap));
  memset(flow, 0, sizeof(flow));
  int u = src, maxflow = 0, aug = -1;
  pre[src] = src;
  gap[0] = nodenum;
  while (dis[src] < nodenum) {
loop:
    for (int v = cur[u]; v < nodenum; ++v) {
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
    int mindis = nodenum - 1;
    for (int v = 0; v < nodenum; v++) {
      if (g[u][v] - flow[u][v] && mindis > dis[v]) { cur[u] = v; mindis = dis[v]; }
    }
    if (--gap[dis[u]] == 0) { break; }
    dis[u] = mindis + 1;
    gap[dis[u]]++;
    u = pre[u];
  }
  return maxflow;
}
//ISAP + 邻接表 O(N^2*M)
const int N = 505;
const int M = 20005;
const int INF = 0x3f3f3f3f;
struct Edge {
  int to, next, cap, flow;
} edge[M];
int tot, head[N], gap[N], dep[N], pre[N], cur[N];
void init() {
  tot = 0; memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int w, int rw = 0) {
  edge[tot].to = v; edge[tot].cap = w; edge[tot].flow = 0; edge[tot].next = head[u]; head[u] = tot++;
  edge[tot].to = u; edge[tot].cap = rw; edge[tot].flow = 0; edge[tot].next = head[v]; head[v] = tot++;
}
int SAP(int src, int sink, int nodenum) {
  memset(gap, 0, sizeof(gap));
  memset(dep, 0, sizeof(dep));
  memcpy(cur, head, sizeof(head));
  int u = src, ans = 0;
  pre[u] = -1;
  gap[0] = nodenum;
  while (dep[src] < nodenum) {
    if (u == sink) {
      int mindis = INF;
      for (int i = pre[u]; ~i; i = pre[edge[i ^ 1].to]) {
        if (mindis > edge[i].cap - edge[i].flow) { mindis = edge[i].cap - edge[i].flow; }
      }
      for (int i = pre[u]; ~i; i = pre[edge[i ^ 1].to]) {
        edge[i].flow += mindis; edge[i ^ 1].flow -= mindis;
      }
      u = src;
      ans += mindis;
      continue;
    }
    bool flag = false;
    int v;
    for (int i = cur[u]; ~i; i = edge[i].next) {
      v = edge[i].to;
      if (edge[i].cap - edge[i].flow && dep[v] + 1 == dep[u]) {
        flag = true; cur[u] = pre[v] = i; break;
      }
    }
    if (flag) { u = v; continue; }
    int mindis = nodenum;
    for (int i = head[u]; ~i; i = edge[i].next) {
      if (edge[i].cap - edge[i].flow && dep[edge[i].to] < mindis) {
        mindis = dep[edge[i].to]; cur[u] = i;
      }
    }
    if (--gap[dep[u]] == 0) { return ans; }
    dep[u] = mindis + 1;
    gap[dep[u]]++;
    if (u != src) { u = edge[pre[u] ^ 1].to; }
  }
  return ans;
}
//ISAP + bfs + stack + 邻接表 O(N^2*M)
const int N = 505;
const int M = 20005;
const int INF = 0x3f3f3f3f;
struct Edge {
  int to, next, cap, flow;
} edge[M];
int tot, head[N], gap[N], dep[N], cur[N], S[N];
void init() {
  tot = 0; memset(head, 0xff, sizeof(head));
}
void addedge(int u, int v, int w, int rw = 0) {
  edge[tot].to = v; edge[tot].cap = w; edge[tot].flow = 0; edge[tot].next = head[u]; head[u] = tot++;
  edge[tot].to = u; edge[tot].cap = rw; edge[tot].flow = 0; edge[tot].next = head[v]; head[v] = tot++;
}
void bfs(int src, int sink) {
  memset(dep, 0xff, sizeof(dep));
  memset(gap, 0, sizeof(gap));
  gap[0] = 1;
  dep[sink] = 0;
  queue<int> q;
  q.push(sink);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int i = head[u]; ~i; i = edge[i].next) {
      int v = edge[i].to;
      if (dep[v] != -1) { continue; }
      q.push(v);
      dep[v] = dep[u] + 1;
      gap[dep[v]]++;
    }
  }
}
int SAP(int src, int sink, int nodenum) {
  bfs(src, sink);
  memcpy(cur, head, sizeof(head));
  int top = 0, u = src, ans = 0;
  while (dep[src] < nodenum) {
    if (u == sink) {
      int mindis = INF, inser;
      for (int i = 0; i < top; ++i) {
        if (mindis > edge[S[i]].cap - edge[S[i]].flow) {
          mindis = edge[S[i]].cap - edge[S[i]].flow; inser = i;
        }
      }
      for (int i = 0; i < top; ++i) {
        edge[S[i]].flow += mindis;
        edge[S[i] ^ 1].flow -= mindis;
      }
      ans += mindis;
      top = inser;
      u = edge[S[top] ^ 1].to;
      continue;
    }
    bool flag = false;
    int v;
    for (int i = cur[u]; ~i; i = edge[i].next) {
      v = edge[i].to;
      if (edge[i].cap - edge[i].flow && dep[v] + 1 == dep[u]) {
        flag = true; cur[u] = i; break;
      }
    }
    if (flag) { S[top++] = cur[u]; u = v; continue; }
    int mindis = nodenum;
    for (int i = head[u]; ~i; i = edge[i].next)
      if (edge[i].cap - edge[i].flow && dep[edge[i].to] < mindis) {
        mindis = dep[edge[i].to]; cur[u] = i;
      }
    if (--gap[dep[u]] == 0) { return ans; }
    dep[u] = mindis + 1;
    ++gap[dep[u]];
    if (u != src) { u = edge[S[--top] ^ 1].to; }
  }
  return ans;
}
//Dinic O(N^2*M)
const int N = 505;
const int M = 20005;
const int INF = 0x3f3f3f3f;
struct Edge {
  int to, next, cap, flow;
} edge[M];
int tot, head[N], dis[N], cur[N], src, sink;
void init() {
  tot = 0; memset(head, 0xff, sizeof(head));
}
void addedge(int u, int v, int w, int rw = 0) {
  edge[tot].to = v;
  edge[tot].cap = w;
  edge[tot].flow = 0;
  edge[tot].next = head[u];
  head[u] = tot++;
  edge[tot].to = u;
  edge[tot].cap = rw;
  edge[tot].flow = 0;
  edge[tot].next = head[v];
  head[v] = tot++;
}
bool bfs() {
  memset(dis, 0, sizeof(dis));
  queue<int> q;
  dis[src] = 1;
  q.push(src);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int i = head[u]; ~i; i = edge[i].next) {
      int v = edge[i].to;
      if (edge[i].cap > edge[i].flow && !dis[v]) {
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }
  }
  return dis[sink];
}
int dfs(int u, int delta) {
  if (u == sink || delta == 0) { return delta; }
  int ret = 0;
  for (int &i = cur[u]; delta && ~i; i = edge[i].next) {
    int v = edge[i].to;
    if (edge[i].cap > edge[i].flow && dis[v] == dis[u] + 1) {
      int aug = dfs(v, min(edge[i].cap - edge[i].flow, delta));
      if (!aug) { continue; }
      edge[i].cap -= aug;
      edge[i ^ 1].cap += aug;
      delta -= aug;
      ret += aug;
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
