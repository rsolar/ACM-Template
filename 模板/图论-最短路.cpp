//http://blog.csdn.net/wjf_wzzc/article/details/22869677

//邻接表
const int N = 100005;
const int M = 200005;
const int INF = 0x3f3f3f3f;
struct graph {
  int head[N], to[M], next[M], len[M], tot;
  void init() { tot = 0; memset(head, -1, sizeof(head)); }
  void addedge(int x, int y, int z) { to[tot] = y; len[tot] = z; next[tot] = head[x]; head[x] = tot++; }
} g;
//Dijkstra + 邻接矩阵 O(V^2)
int n, mp[N][N], dist[N], pre[N]; //邻接矩阵初始化为INF, pre[i]记录src到i路径上的父结点, pre[src] = -1
bool vis[N];
void Dijkstra(int src) {
  memset(dist, 0x3f, sizeof(dist));
  memset(vis, 0, sizeof(vis));
  memset(pre, -1, sizeof(pre));
  dist[src] = 0;
  for (int j = 0; j < n; j++) {
    int k = -1, mn = INF;
    for (int i = 0; i < n; i++) {
      if (!vis[i] && dist[i] < mn) { mn = dist[i]; k = i; }
    }
    if (k == -1) { break; }
    vis[k] = true;
    for (int i = 0; i < n; i++) {
      if (!vis[i] && dist[k] + mp[k][i] < dist[i]) {
        dist[i] = dist[k] + mp[k][i]; pre[i] = k;
      }
    }
  }
}
//Dijkstra + priority_queue + vector存边 O(ElogE)
struct Node {
  int v, cost;
  Node(int _v = 0, int _cost = 0): v(_v), cost(_cost) {}
  bool operator<(const Node &r)const { return cost > r.cost; }
};
struct Edge {
  int v, dis;
  Edge(int _v = 0, int _dis = 0): v(_v), dis(_dis) {}
};
vector<Edge> e[N];
int dist[N];
bool vis[N];
void Dijkstra(int src) {
  memset(dist, 0x3f, sizeof(dist));
  memset(vis, 0, sizeof(vis));
  priority_queue<Node> que;
  dist[src] = 0;
  que.push(Node(src, dist[src]));
  while (!que.empty()) {
    int u = que.top().v; que.pop();
    if (vis[u]) { continue; }
    vis[u] = true;
    for (size_t i = 0; i < e[u].size(); i++) {
      int v = e[u][i].v, dis = e[u][i].dis;
      if (!vis[v] && dist[v] > dist[u] + dis) {
        dist[v] = dist[u] + dis;
        que.push(Node(v, dist[v]));
      }
    }
  }
}
//Dijkstra + priority_queue + 邻接表 O(VE)
struct Node {
  int v, dis;
  Node(int _v = 0, int _dis = 0): v(_v), dis(_dis) {}
  bool operator<(const Node &r)const { return dis > r.dis; }
};
int dist[N];
void Dijkstra(int src) {
  memset(dist, 0x3f, sizeof(dist));
  dist[src] = 0;
  priority_queue<Node> que;
  que.push(Node(src, dist[src]));
  while (!que.empty()) {
    int u = que.top().v, dis = que.top().dis; que.pop();
    if (dis != dist[u]) { continue; }
    for (int i = g.head[u]; ~i; i = g.next[i]) {
      int v = g.to[i];
      if (dis + g.len[i] < dist[v]) {
        dist[v] = dis + g.len[i];
        que.push(Node(v, dist[v]));
      }
    }
  }
}
//SPFA + queue/stack + vector存边 O(kE)
const int INF = 0x3f3f3f3f;
struct Edge {
  int v, dis;
  Edge(int _v = 0, int _dis = 0): v(_v), dis(_dis) {}
};
vector<Edge> e[N];
int dist[N], cnt[N]; //cnt[i]为入队列次数
bool vis[N]; //在队列/栈标志
bool SPFA(int src) {
  memset(dist, 0x3f, sizeof(dist));
  memset(cnt, 0, sizeof(cnt));
  memset(vis, 0, sizeof(vis));
  dist[src] = 0;
  cnt[src] = 1;
  vis[src] = true;
  queue<int> que; //stack<int> que;
  que.push(src);
  while (!que.empty()) {
    int u = que.front(); que.pop(); //int u = que.top(); que.pop();
    vis[u] = false;
    for (size_t i = 0; i < e[u].size(); i++) {
      int v = e[u][i].v;
      if (dist[v] > dist[u] + e[u][i].dis) {
        dist[v] = dist[u] + e[u][i].dis;
        if (!vis[v]) {
          vis[v] = true;
          que.push(v);
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
void spfa(int src) {
  memset(dist, 0x3f, sizeof(dist));
  memset(vis, 0, sizeof(vis));
  dist[src] = 0;
  deque<int> que;
  que.push_back(src);
  vis[src] = true;
  ll sum = 0;
  while (!que.empty()) {
    int u = que.front(); que.pop_front();
    if (!que.empty() && (ll)dist[u] * que.size() > sum) {
      que.push_back(u); continue;
    }
    sum -= dist[u];
    vis[u] = false;
    for (int i = g.head[u]; ~i; i = g.next[i]) {
      int v = g.to[i], d = dist[u] + g.len[i];
      if (d < dist[v]) {
        if (vis[v]) { sum += d - dist[v]; }
        dist[v] = d;
        if (!vis[v]) {
          if (!que.empty() && dist[que.front()] > dist[v]) {
            que.push_front(v);
          } else {
            que.push_back(v);
          }
          sum += dist[v];
          vis[v] = true;
        }
      }
    }
  }
}
//bellman-ford + vector O(V*E)
//可以处理负边权图
//可以判断是否存在负环回路,返回true,当且仅当图中不包含从源点可达的负权回路
const int INF = 0x3f3f3f3f;
struct Edge {
  int u, v, dis;
  Edge(int _u = 0, int _v = 0, int _dis = 0): u(_u), v(_v), dis(_dis) {}
};
vector<Edge> e;
int dist[N];
bool bellman_ford(int src) {
  memset(dist, 0x3f, sizeof(dist));
  dist[src] = 0;
  for (int i = 1; i < n; i++) {
    bool flag = false;
    for (size_t j = 0; j < e.size(); j++) {
      int u = e[j].u, v = e[j].v, dis = e[j].dis;
      if (dist[v] > dist[u] + dis) {
        dist[v] = dist[u] + dis; flag = true;
      }
    }
    if (!flag) { return true; } //没有负环回路
  }
  for (size_t j = 0; j < e.size(); j++) {
    if (dist[e[j].v] > dist[e[j].u] + e[j].dis) { return false; } //有负环回路
  }
  return true; //没有负环回路
}
//floyd 带路径记录 O(V^3)
int n, mp[N][N], dist[N][N], pre[N][N];
void floyd() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      dist[i][j] = mp[i][j]; pre[i][j] = (i == j) ? -1 : i;
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j]; pre[i][j] = pre[k][j];
        }
      }
    }
  }
}
