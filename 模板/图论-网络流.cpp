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
    dis[u] = mindis + 1; gap[dis[u]]++; u = pre[u];
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
int ISAP(int src, int sink) {
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
  dep[sink] = 0; gap[0] = 1;
  queue<int> que;
  que.push(sink);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    for (int i = head[u]; ~i; i = Next[i]) {
      int v = to[i];
      if (~dep[v]) { continue; }
      dep[v] = dep[u] + 1; gap[dep[v]]++; que.push(v);
    }
  }
}
int ISAP(int src, int sink) {
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
    if (--gap[dep[u]] == 0) { break; }
    dep[u] = mindis + 1; gap[dep[u]]++;
    if (u != src) { u = to[S[--top] ^ 1]; }
  }
  return maxflow;
}
//ISAP + bfs + queue + 邻接表 O(V^2*E)
const int N = 505;
const int M = 20005;
const int INF = 0x3f3f3f3f;
int n, m, head[N], to[M], Next[M], cap[M], tot;
int dep[N], pre[N], cur[N], gap[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, int w, int rw = 0) {
  to[tot] = y; cap[tot] = w; Next[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = rw; Next[tot] = head[y]; head[y] = tot++;
}
void bfs(int sink) {
  memset(dep, -1, sizeof(dep));
  memset(gap, 0, sizeof(gap));
  dep[sink] = 0; gap[0] = 1;
  queue<int> que;
  que.push(sink);
  while (Front < End) {
    int u = que.front(); que.pop();
    for (int i = head[u]; ~i; i = Next[i]) {
      int v = to[i];
      if (~dep[v]) { continue; }
      dep[v] = dep[u] + 1; gap[dep[v]]++; que.push(v);
    }
  }
}
int ISAP(int src, int sink) {
  bfs(sink);
  memcpy(cur, head, sizeof(head));
  int u = pre[src] = src, v, maxflow = 0, i;
  while (dep[sink] < n) {
    if (u == sink) {
      int mindis = INF, inser;
      for (i = src; i != sink; i = to[cur[i]]) {
        if (mindis > cap[cur[i]]) { mindis = cap[cur[i]]; inser = i; }
      }
      for (i = src; i != sink; i = to[cur[i]]) {
        cap[cur[i]] -= mindis; cap[cur[i] ^ 1] += mindis;
      }
      maxflow += mindis; u = inser;
    }
    for (i = cur[u]; ~i; i = Next[i]) {
      v = to[i];
      if (dep[v] + 1 == dep[u] && cap[i]) { break; }
    }
    if (~i) { cur[u] = i; pre[to[i]] = u; u = to[i]; }
    else {
      if (--gap[dep[u]] == 0) { break; }
      int mindis = n;
      for (i = head[u]; ~i; i = Next[i]) {
        if (cap[i] && mindis > dep[to[i]]) { cur[u] = i; mindis = dep[to[i]]; }
      }
      dep[u] = mindis + 1; gap[dep[u]]++; u = pre[u];
    }
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
int Dinic() {
  int ret = 0;
  while (bfs()) {
    for (int i = 0; i <= sink; ++i) { cur[i] = head[i]; }
    ret += dfs(src, INF);
  }
  return ret;
}
//HLPP Highest Label Preflow Push O(V^3)
const int N = 505;
const int M = 20005;
struct Edge {
  int v, c;
} edge[M << 1];
vector<int> e[N];
int n, m, src, sink;
int c[N << 1], d[N], w[N], done[N];
bool vis[N];
void init(int _n, int _src, int _sink) {
  n = _n; m = 0; src = _src; sink = _sink;
  for (int i = 0; i <= n; ++i) { e[i].clear(); }
}
void addEdge(int a, int b, int c, int rc = 0) {
  edge[m].v = b; edge[m].c = c; e[a].push_back(m++);
  edge[m].v = a; edge[m].c = rc; e[b].push_back(m++);
}
void bfs() {
  memset(c, 0, sizeof(c));
  fill(d, d + n, n + 1);
  queue<int> que;
  c[n + 1] = n - 1; d[src] = n; d[sink] = 0;
  que.push(sink);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    c[n + 1]++; c[d[u]]++;
    for (int i = 0; i < e[u].size(); i++) {
      Edge &cra = edge[e[u][i] ^ 1];
      int v = edge[e[u][i]].v;
      if (d[v] == n + 1 && cra.c > 0) {
        d[v] = d[u] + 1; que.push(v);
      }
    }
  }
}
int HLPP() {
  memset(w, 0, sizeof(w));
  memset(done, 0, sizeof(done));
  memset(vis, 0, sizeof(vis));
  bfs();
  int todo = -1;
  vector<queue<int> > que(n << 1);
  vis[src] = vis[sink] = true;
  for (int i = 0; i < e[src].size(); i++) {
    Edge &arc = edge[e[src][i]], &cra = edge[e[src][i] ^ 1];
    int v = arc.v;
    w[v] += arc.c; cra.c += arc.c; arc.c = 0;
    if (!vis[v]) { vis[v] = true; que[d[v]].push(v); todo = max(todo, d[v]); }
  }
  while (todo >= 0) {
    if (que[todo].empty()) { todo--; continue; }
    int u = que[todo].front(); que[todo].pop();
    vis[u] = false;
    while (done[u] < e[u].size()) {
      Edge &arc = edge[e[u][done[u]]];
      int v = arc.v;
      if (d[u] == d[v] + 1 && arc.c > 0) {
        Edge &cra = edge[e[u][done[u]] ^ 1];
        int f = min(w[u], arc.c);
        w[u] -= f; w[v] += f; arc.c -= f; cra.c += f;
        if (!vis[v]) { vis[v] = true; que[d[v]].push(v); }
        if (w[u] == 0) { break; }
      }
      done[u]++;
    }
    if (w[u] > 0) {
      int du = d[u];
      c[d[u]]--; d[u] = n << 1;
      for (int i = 0; i < e[u].size(); i++) {
        Edge &arc = edge[e[u][i]];
        int v = arc.v;
        if (d[u] > d[v] + 1 && arc.c > 0) { d[u] = d[v] + 1; done[u] = i; }
      }
      c[d[u]]++;
      if (c[du] == 0) {
        for (int i = 0; i < n; ++i) {
          if (d[i] > du && d[i] < n + 1) { c[d[i]]--; c[n + 1]++; d[i] = n + 1; }
        }
      }
      vis[u] = true; que[d[u]].push(u); todo = d[u];
    }
  }
  return w[sink];
}
//最小费用最大流 MCMF O(V*E*f)
//ver.kuangbin
//求最大费用只需要取相反数, 结果取相反数即可
const int N = 1005;
const int M = 100005;
const int INF = 0x3f3f3f3f;
int n, head[N], to[M], Next[M], cap[M], flow[M], cost[M], tot;
int dis[N], pre[N];
bool vis[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, int w, int c) {
  to[tot] = y; cap[tot] = w; flow[tot] = 0; cost[tot] = c; Next[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = 0; flow[tot] = 0; cost[tot] = -c; Next[tot] = head[y]; head[y] = tot++;
}
bool SPFA(int src, int sink) {
  memset(dis, 0x3f, sizeof(dis));
  memset(pre, -1, sizeof(pre));
  memset(vis, 0, sizeof(vis));
  queue<int> que;
  dis[src] = 0; vis[src] = true;
  que.push(src);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    vis[u] = false;
    for (int i = head[u]; ~i; i = Next[i]) {
      int v = to[i];
      if (cap[i] > flow[i] && dis[v] > dis[u] + cost[i]) {
        dis[v] = dis[u] + cost[i]; pre[v] = i;
        if (!vis[v]) { vis[v] = true; que.push(v); }
      }
    }
  }
  return pre[sink] != -1;
}
//返回的是最大流, cost存的是最小费用
int MCMF(int src, int sink, int &cost) {
  int maxflow = 0; cost = 0;
  while (SPFA(src, sink)) {
    int mn = INF;
    for (int i = pre[sink]; ~i; i = pre[to[i ^ 1]]) {
      if (mn > cap[i] - flow[i]) { mn = cap[i] - flow[i]; }
    }
    for (int i = pre[sink]; ~i; i = pre[edge[i ^ 1].to]) {
      flow[i] += mn; flow[i ^ 1] -= mn; cost += cost[i] * mn;
    }
    maxflow += mn;
  }
  return maxflow;
}
//ver.poursoul
const int N = 1005;
const int M = 100005;
const int INF = 0x3f3f3f3f;
int n, head[N], to[M], Next[M], cap[M], cost[M], tot;
int dis[N], cur[N], flow[N], mncost, mxflow; //结果
bool vis[N];
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, int w, int c) {
  to[tot] = y; cap[tot] = w; cost[tot] = c; Next[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = 0; cost[tot] = -c; Next[tot] = head[y]; head[y] = tot++;
}
bool SPFA(int src, int sink) {
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, 0, sizeof(vis));
  dis[src] = 0; cur[src] = -1; flow[src] = INF;
  queue<int> que;
  que.push(src);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    vis[u] = false;
    for (int i = head[u]; ~i; i = Next[i]) {
      int v = to[i];
      if (cap[i] > 0 && dis[v] > dis[u] + cost[i]) {
        dis[v] = dis[u] + cost[i]; flow[v] = min(flow[u], cap[i]); cur[v] = i;
        if (!vis[v]) { vis[v] = true; que.push(v); }
      }
    }
  }
  if (d[sink] == INF) { return false; }
  mxflow += flow[sink]; mncost += flow[sink] * dis[sink];
  for (int i = cur[sink]; ~i; i = cur[to[i ^ 1]]) {
    cap[i] -= flow[sink]; cap[i ^ 1] += flow[sink];
  }
  return true;
}
int MCMF() {
  mxflow = mncost = 0;
  while (SPFA());
  return mncost;
}
