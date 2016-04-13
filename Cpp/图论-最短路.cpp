//邻接表
const int N = 100005;
const int M = 200005;
const int INF = 0x3f3f3f3f;
int head[N], to[M], nxt[M], len[M], tot;
void init() { tot = 0; memset(head, -1, sizeof(head)); }
void addedge(int x, int y, int z) { to[tot] = y; len[tot] = z; nxt[tot] = head[x]; head[x] = tot++; }
//Dijkstra + 邻接矩阵 O(V^2)
int n, mp[N][N], dist[N], pre[N]; //邻接矩阵初始化为INF, pre[i]记录src到i路径上的父结点, pre[src] = -1
bool vis[N];
void Dijkstra(int src) {
  memset(dist, 0x3f, sizeof(dist)); dist[src] = 0;
  memset(vis, 0, sizeof(vis)); memset(pre, -1, sizeof(pre));
  for (int j = 0; j < n; j++) {
    int u = -1, mn = INF;
    for (int i = 0; i < n; i++) {
      if (!vis[i] && dist[i] < mn) { mn = dist[i]; u = i; }
    }
    if (u == -1) { break; }
    vis[u] = true;
    for (int v = 0; v < n; v++) {
      if (!vis[v] && dist[u] + mp[u][v] < dist[v]) {
        dist[v] = dist[u] + mp[u][v]; pre[v] = u;
      }
    }
  }
}
//Dijkstra + priority_queue + 邻接矩阵 O(V^2)
struct Node {
  int v, w;
  Node(int _v, int _w): v(_v), w(_w) {}
  bool operator<(const Node &r)const { return w > r.w; }
};
int n, mp[N][N], dist[N], pre[N];
bool vis[N];
void Dijkstra(int src) {
  memset(dist, 0x3f, sizeof(dist)); dist[src] = 0;
  memset(vis, 0, sizeof(vis)); memset(pre, -1, sizeof(pre));
  priority_queue<Node> que; que.push(Node(src, dist[src]));
  while (!que.empty()) {
    int u = que.top().v; que.pop();
    if (vis[u]) { continue; }
    vis[u] = true;
    for (int v = 0; v < n; v++) {
      if (u != v && !vis[v] && dist[u] + mp[u][v] < dist[v]) {
        dist[v] = dist[u] + mp[u][v]; pre[v] = u; que.push(Node(v, dist[v]));
      }
    }
  }
}
//Dijkstra + priority_queue + vector存边 O((V+E)logV)
struct Node {
  int v, w;
  Node(int _v, int _w): v(_v), w(_w) {}
  bool operator<(const Node &r)const { return w > r.w; }
};
vector<Node> e[N];
int dist[N];
bool vis[N];
void Dijkstra(int src) {
  memset(dist, 0x3f, sizeof(dist)); dist[src] = 0;
  memset(vis, 0, sizeof(vis));
  priority_queue<Node> que; que.push(Node(src, dist[src]));
  while (!que.empty()) {
    int u = que.top().v; que.pop();
    if (vis[u]) { continue; }
    vis[u] = true;
    for (size_t i = 0; i < e[u].size(); i++) {
      int v = e[u][i].v, w = e[u][i].w;
      if (!vis[v] && dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w; que.push(Node(v, dist[v]));
      }
    }
  }
}
//Dijkstra + priority_queue + 邻接表 O((V+E)logV)
struct Node {
  int v, w;
  Node(int _v, int _w): v(_v), w(_w) {}
  bool operator<(const Node &r)const { return w > r.w; }
};
int dist[N];
void Dijkstra(int src) {
  memset(dist, 0x3f, sizeof(dist)); dist[src] = 0;
  priority_queue<Node> que; que.push(Node(src, dist[src]));
  while (!que.empty()) {
    int u = que.top().v, w = que.top().w; que.pop();
    if (w != dist[u]) { continue; }
    for (int i = head[u]; ~i; i = nxt[i]) {
      int v = to[i];
      if (w + len[i] < dist[v]) {
        dist[v] = w + len[i]; que.push(Node(v, dist[v]));
      }
    }
  }
}
//SPFA + queue/stack + vector存边 O(kE)
struct Edge {
  int v, w;
  Edge(int _v, int _w): v(_v), w(_w) {}
};
vector<Edge> e[N];
int dist[N], cnt[N], pre[N]; //cnt[i]为入队列次数
bool vis[N]; //在队/栈标志
bool SPFA(int src) {
  memset(dist, 0x3f, sizeof(dist)); dist[src] = 0;
  memset(cnt, 0, sizeof(cnt)); cnt[src] = 1;
  memset(vis, 0, sizeof(vis)); vis[src] = true;
  memset(pre, -1, sizeof(pre));
  queue<int> que; //stack<int> que;
  que.push(src);
  while (!que.empty()) {
    int u = que.front(); que.pop(); //int u = que.top(); que.pop();
    vis[u] = false;
    for (size_t i = 0; i < e[u].size(); i++) {
      int v = e[u][i].v, w = e[u][i].w;
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        if (!vis[v]) {
          vis[v] = true; pre[v] = u; que.push(v);
          if (++cnt[v] > n) { return false; } //有负环回路
        }
      }
    }
  }
  return true; //没有负环回路
}
//SPFA + SLF + LLL + 邻接表 O(kE)
int dist[N];
bool vis[M];
void SPFA(int src) {
  memset(dist, 0x3f, sizeof(dist)); dist[src] = 0;
  memset(vis, 0, sizeof(vis)); vis[src] = true;
  deque<int> que; que.push_back(src);
  ll sum = 0;
  while (!que.empty()) {
    int u = que.front(); que.pop_front();
    if (!que.empty() && (ll)dist[u] * que.size() > sum) { que.push_back(u); continue; }
    sum -= dist[u]; vis[u] = false;
    for (int i = head[u]; ~i; i = nxt[i]) {
      int v = to[i], d = dist[u] + len[i];
      if (d < dist[v]) {
        if (vis[v]) { sum += d - dist[v]; }
        dist[v] = d;
        if (!vis[v]) {
          if (!que.empty() && dist[que.front()] > dist[v]) { que.push_front(v); }
          else { que.push_back(v); }
          sum += dist[v]; vis[v] = true;
        }
      }
    }
  }
}
//Bellman-Ford + vector O(VE)
//可以处理负边权图, 可以判断是否存在负环回路, 当且仅当图中不包含从源点可达的负权回路时返回true
struct Edge {
  int u, v, w;
  Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
};
vector<Edge> e;
int dist[N];
bool BellmanFord(int src) {
  memset(dist, 0x3f, sizeof(dist)); dist[src] = 0;
  for (int i = 1; i < n; i++) {
    bool flag = false;
    for (size_t j = 0; j < e.size(); j++) {
      int u = e[j].u, v = e[j].v, w = e[j].w;
      if (dist[v] > dist[u] + w) { dist[v] = dist[u] + w; flag = true; }
    }
    if (!flag) { return true; } //没有负环回路
  }
  for (size_t j = 0; j < e.size(); j++) {
    int u = e[j].u, v = e[j].v, w = e[j].w;
    if (dist[v] > dist[u] + w) { return false; } //有负环回路
  }
  return true; //没有负环回路
}
//Floyd 带路径记录 O(V^3)
int n, mp[N][N], pre[N][N];
void Floyd() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { pre[i][j] = (i == j) ? -1 : i; }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (mp[i][k] + mp[k][j] < mp[i][j]) {
          mp[i][j] = mp[i][k] + mp[k][j]; pre[i][j] = pre[k][j];
        }
      }
    }
  }
}
