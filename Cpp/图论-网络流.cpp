//最大流
//SAP + 邻接矩阵 O(V^2*E) 点的编号默认从0开始
typedef long long ftype;
int n, dep[N], pre[N], cur[N], gap[N];
ftype cap[N][N];
ftype SAP(int src, int sink, int n = n) {
  memset(dep, 0, sizeof(dep));
  memset(cur, 0, sizeof(cur));
  memset(gap, 0, sizeof(gap));
  int u = src; ftype mxflow = 0, aug = -1; pre[src] = src; gap[0] = n;
  while (dep[src] < n) {
loop:
    for (int v = cur[u]; v < n; ++v) {
      if (cap[u][v] > 0 && dep[u] == dep[v] + 1) {
        if (aug == -1 || aug > cap[u][v]) { aug = cap[u][v]; }
        pre[v] = u; u = cur[u] = v;
        if (v == sink) {
          for (u = pre[u]; v != src; v = u, u = pre[u]) {
            cap[u][v] -= aug; cap[v][u] += aug;
          }
          mxflow += aug; aug = -1;
        }
        goto loop;
      }
    }
    int mndis = n - 1;
    for (int v = 0; v < n; v++) {
      if (cap[u][v] > 0 && mndis > dep[v]) { cur[u] = v; mndis = dep[v]; }
    }
    if (--gap[dep[u]] == 0) { break; }
    dep[u] = mndis + 1; gap[dep[u]]++; u = pre[u];
  }
  return mxflow;
}
//ISAP + 邻接表 O(V^2*E)
typedef long long ftype;
const ftype INF = 0x3f3f3f3f; //!!!
int n, head[N], to[M], nxt[M], tot, dep[N], pre[N], cur[N], gap[N];
ftype cap[M];
inline void init() { tot = 0; memset(head, -1, sizeof(head)); }
inline void addedge(int x, int y, ftype w, ftype rw = 0) {
  to[tot] = y; cap[tot] = w; nxt[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = rw; nxt[tot] = head[y]; head[y] = tot++;
}
ftype ISAP(int src, int sink, int n = n) {
  memset(dep, 0, sizeof(dep));
  memset(gap, 0, sizeof(gap));
  memcpy(cur, head, sizeof(head));
  int u = src, v; ftype mxflow = 0; pre[u] = -1; gap[0] = n;
  while (dep[src] < n) {
    if (u == sink) {
      ftype mndis = INF;
      for (int i = pre[u]; ~i; i = pre[to[i ^ 1]]) {
        if (mndis > cap[i]) { mndis = cap[i]; }
      }
      for (int i = pre[u]; ~i; i = pre[to[i ^ 1]]) {
        cap[i] -= mndis; cap[i ^ 1] += mndis;
      }
      u = src; mxflow += mndis;
      continue;
    }
    bool flag = false;
    for (int i = cur[u]; ~i; i = nxt[i]) {
      v = to[i];
      if (cap[i] > 0 && dep[v] + 1 == dep[u]) {
        flag = true; cur[u] = pre[v] = i; break;
      }
    }
    if (flag) { u = v; continue; }
    int mndis = n;
    for (int i = head[u]; ~i; i = nxt[i]) {
      if (cap[i] > 0 && dep[to[i]] < mndis) { mndis = dep[to[i]]; cur[u] = i; }
    }
    if (--gap[dep[u]] == 0) { return mxflow; }
    dep[u] = mndis + 1; gap[dep[u]]++;
    if (u != src) { u = to[pre[u] ^ 1]; }
  }
  return mxflow;
}
//ISAP + bfs标号 + queue + 邻接表 O(V^2*E)
typedef long long ftype;
const ftype INF = 0x3f3f3f3f; //!!!
int n, head[N], to[M], nxt[M], tot, dep[N], pre[N], cur[N], gap[N];
ftype cap[M];
inline void init() { tot = 0; memset(head, -1, sizeof(head)); }
inline void addedge(int x, int y, ftype w, ftype rw = 0) {
  to[tot] = y; cap[tot] = w; nxt[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = rw; nxt[tot] = head[y]; head[y] = tot++;
}
void bfs(int sink) {
  memset(dep, -1, sizeof(dep));
  memset(gap, 0, sizeof(gap));
  dep[sink] = 0; gap[0] = 1;
  queue<int> que; que.push(sink);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    for (int i = head[u], v; ~i; i = nxt[i]) {
      v = to[i];
      if (~dep[v]) { continue; }
      dep[v] = dep[u] + 1; gap[dep[v]]++; que.push(v);
    }
  }
}
ftype ISAP(int src, int sink, int n = n) {
  bfs(sink);
  memcpy(cur, head, sizeof(head));
  int u = pre[src] = src, v, i; ftype mxflow = 0;
  while (dep[sink] < n) {
    if (u == sink) {
      ftype mndis = INF; int inser;
      for (i = src; i != sink; i = to[cur[i]]) {
        if (mndis > cap[cur[i]]) { mndis = cap[cur[i]]; inser = i; }
      }
      for (i = src; i != sink; i = to[cur[i]]) {
        cap[cur[i]] -= mndis; cap[cur[i] ^ 1] += mndis;
      }
      mxflow += mndis; u = inser;
    }
    for (i = cur[u]; ~i; i = nxt[i]) {
      v = to[i];
      if (dep[v] + 1 == dep[u] && cap[i] > 0) { break; }
    }
    if (~i) { cur[u] = i; pre[to[i]] = u; u = to[i]; }
    else {
      if (--gap[dep[u]] == 0) { break; }
      int mndis = n;
      for (i = head[u]; ~i; i = nxt[i]) {
        if (cap[i] > 0 && mndis > dep[to[i]]) { cur[u] = i; mndis = dep[to[i]]; }
      }
      dep[u] = mndis + 1; gap[dep[u]]++; u = pre[u];
    }
  }
  return mxflow;
}
//Dinic O(V^2*E)
typedef long long ftype;
const ftype INF = 0x3f3f3f3f; //!!!
int head[N], to[M], nxt[M], tot, dep[N], cur[N], src, sink;
ftype cap[M];
inline void init() { tot = 0; memset(head, -1, sizeof(head)); }
inline void addedge(int x, int y, ftype w, ftype rw = 0) {
  to[tot] = y; cap[tot] = w; nxt[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = rw; nxt[tot] = head[y]; head[y] = tot++;
}
bool bfs() {
  memset(dep, 0, sizeof(dep)); dep[src] = 1;
  queue<int> que; que.push(src);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    for (int i = head[u], v; ~i; i = nxt[i]) {
      v = to[i];
      if (cap[i] > 0 && !dep[v]) { dep[v] = dep[u] + 1; que.push(v); }
    }
  }
  return dep[sink];
}
ftype dfs(int u, ftype delta) {
  if (u == sink || delta == 0) { return delta; }
  ftype ret = 0;
  for (int &i = cur[u], v; delta && ~i; i = nxt[i]) {
    v = to[i];
    if (cap[i] > 0 && dep[v] == dep[u] + 1) {
      ftype aug = dfs(v, min(cap[i], delta));
      if (!aug) { continue; }
      cap[i] -= aug; cap[i ^ 1] += aug; delta -= aug; ret += aug;
      if (!delta) { break; }
    }
  }
  return ret;
}
ftype Dinic() {
  ftype ret = 0;
  while (bfs()) {
    for (int i = 0; i <= sink; ++i) { cur[i] = head[i]; }
    ret += dfs(src, INF);
  }
  return ret;
}
//HLPP Highest Label Preflow Push O(V^3)
typedef long long ftype;
struct Edge { int v; ftype c; } edge[M];
vector<int> e[N];
int n, m, src, sink, c[N << 1], d[N], done[N];
ftype w[N];
bool vis[N];
void init(int _n, int _src, int _sink) {
  n = _n; m = 0; src = _src; sink = _sink;
  for (int i = 0; i <= n; ++i) { e[i].clear(); }
}
inline void addEdge(int x, int y, ftype w, ftype rw = 0) {
  edge[m].v = y; edge[m].c = w; e[x].push_back(m++);
  edge[m].v = x; edge[m].c = rw; e[y].push_back(m++);
}
void bfs() {
  memset(c, 0, sizeof(c));
  fill(d, d + n, n + 1);
  queue<int> que; que.push(sink);
  c[n + 1] = n - 1; d[src] = n; d[sink] = 0;
  while (!que.empty()) {
    int u = que.front(); que.pop();
    c[n + 1]++; c[d[u]]++;
    for (int i = 0, v; i < (int)e[u].size(); i++) {
      v = edge[e[u][i]].v; ftype c = edge[e[u][i] ^ 1].c;
      if (d[v] == n + 1 && c > 0) { d[v] = d[u] + 1; que.push(v); }
    }
  }
}
int HLPP(int n = n) {
  memset(w, 0, sizeof(w));
  memset(done, 0, sizeof(done));
  memset(vis, 0, sizeof(vis));
  bfs();
  int todo = -1;
  vector<queue<int>> que(n << 1);
  vis[src] = vis[sink] = true;
  for (int i = 0, v; i < (int)e[src].size(); i++) {
    Edge &arc = edge[e[src][i]], &cra = edge[e[src][i] ^ 1]; v = arc.v;
    w[v] += arc.c; cra.c += arc.c; arc.c = 0;
    if (!vis[v]) { vis[v] = true; que[d[v]].push(v); todo = max(todo, d[v]); }
  }
  while (todo >= 0) {
    if (que[todo].empty()) { todo--; continue; }
    int u = que[todo].front(); que[todo].pop();
    vis[u] = false;
    while (done[u] < (int)e[u].size()) {
      Edge &arc = edge[e[u][done[u]]]; int v = arc.v;
      if (d[u] == d[v] + 1 && arc.c > 0) {
        Edge &cra = edge[e[u][done[u]] ^ 1]; ftype f = min(w[u], arc.c);
        w[u] -= f; w[v] += f; arc.c -= f; cra.c += f;
        if (!vis[v]) { vis[v] = true; que[d[v]].push(v); }
        if (w[u] == 0) { break; }
      }
      done[u]++;
    }
    if (w[u] > 0) {
      int du = d[u];
      c[d[u]]--; d[u] = n << 1;
      for (int i = 0, v; i < (int)e[u].size(); i++) {
        Edge &arc = edge[e[u][i]]; v = arc.v;
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
//求最大费用只需取相反数, 结果取相反数即可
typedef long long ftype;
const ftype INF = 0x3f3f3f3f; //!!!
int head[N], to[M], nxt[M], tot, pre[N];
ftype cap[M], cost[M], dep[N], mxflow, mncost;
bool vis[N];
inline void init() { tot = 0; memset(head, -1, sizeof(head)); }
inline void addedge(int x, int y, ftype w, ftype c) {
  to[tot] = y; cap[tot] = w; cost[tot] = c; nxt[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = 0; cost[tot] = -c; nxt[tot] = head[y]; head[y] = tot++;
}
bool SPFA(int src, int sink) {
  memset(dep, 0x3f, sizeof(dep));
  memset(pre, -1, sizeof(pre));
  memset(vis, 0, sizeof(vis));
  queue<int> que; que.push(src);
  dep[src] = 0; vis[src] = true;
  while (!que.empty()) {
    int u = que.front(); que.pop();
    vis[u] = false;
    for (int i = head[u], v; ~i; i = nxt[i]) {
      v = to[i];
      if (cap[i] > 0 && dep[v] > dep[u] + cost[i]) {
        dep[v] = dep[u] + cost[i]; pre[v] = i;
        if (!vis[v]) { vis[v] = true; que.push(v); }
      }
    }
  }
  return pre[sink] != -1;
}
ftype MCMF(int src, int sink) {
  mxflow = mncost = 0;
  while (SPFA(src, sink)) {
    ftype mn = INF;
    for (int i = pre[sink]; ~i; i = pre[to[i ^ 1]]) {
      if (mn > cap[i]) { mn = cap[i]; }
    }
    for (int i = pre[sink]; ~i; i = pre[to[i ^ 1]]) {
      cap[i] -= mn; cap[i ^ 1] += mn; mncost += cost[i] * mn;
    }
    mxflow += mn;
  }
  return mncost;
}
//ver.poursoul
typedef long long ftype;
const ftype INF = 0x3f3f3f3f; //!!!
int head[N], to[M], nxt[M], tot, cur[N];
ftype cap[M], cost[M], flow[N], dep[N], mncost, mxflow;
bool vis[N];
inline void init() { tot = 0; memset(head, -1, sizeof(head)); }
inline void addedge(int x, int y, ftype w, ftype c) {
  to[tot] = y; cap[tot] = w; cost[tot] = c; nxt[tot] = head[x]; head[x] = tot++;
  to[tot] = x; cap[tot] = 0; cost[tot] = -c; nxt[tot] = head[y]; head[y] = tot++;
}
bool SPFA(int src, int sink) {
  memset(dep, 0x3f, sizeof(dep));
  memset(vis, 0, sizeof(vis));
  dep[src] = 0; cur[src] = -1; flow[src] = INF;
  queue<int> que; que.push(src);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    vis[u] = false;
    for (int i = head[u], v; ~i; i = nxt[i]) {
      v = to[i];
      if (cap[i] > 0 && dep[v] > dep[u] + cost[i]) {
        dep[v] = dep[u] + cost[i]; flow[v] = min(flow[u], cap[i]); cur[v] = i;
        if (!vis[v]) { vis[v] = true; que.push(v); }
      }
    }
  }
  if (dep[sink] == INF) { return false; }
  mxflow += flow[sink]; mncost += flow[sink] * dep[sink];
  for (int i = cur[sink]; ~i; i = cur[to[i ^ 1]]) {
    cap[i] -= flow[sink]; cap[i ^ 1] += flow[sink];
  }
  return true;
}
ftype MCMF(int src, int sink) {
  mxflow = mncost = 0;
  while (SPFA(src, sink));
  return mncost;
}
