//http://blog.csdn.net/wjf_wzzc/article/details/22869677

//邻接表
#define N 100005
#define M 200005
#define INF 0x3f3f3f3f
struct graph {
	int head[N], to[M], next[M], len[M], tot;
	void init() { tot = 0; memset(head, -1, sizeof(head)); }
	void addedge(int x, int y, int z) { to[tot] = y; len[tot] = z; next[tot] = head[x]; head[x] = tot++; }
} g;

//Dijkstra + 邻接矩阵 O(V^2)
int n, mp[N][N], pre[N], dist[N]; //pre[i]记录src到i路径上的父结点，pre[src] = -1
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

//Dijkstra + priority_queue + 邻接表 O(VE)
int dist[M];
void dijkstra(int src) {
	memset(dist, 0x3f, sizeof(dist));
	dist[src] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	pq.push(make_pair(dist[src], src));
	while (!pq.empty()) {
		int x = pq.top().second, d = pq.top().first; pq.pop();
		if (d != dist[x]) { continue; }
		for (int i = g.head[x]; ~i; i = g.next[i]) {
			int y = g.to[i];
			if (d + g.len[i] < dist[y]) {
				dist[y] = d + g.len[i];
				pq.push(make_pair(dist[y], y));
			}
		}
	}
}

//SPFA + SLF + LLL + 邻接表 O(kE)
int dist[M];
bool inque[M];
void spfa(int src) {
	memset(dist, 0x3f, sizeof(dist));
	memset(inque, 0, sizeof(inque));
	dist[src] = 0;
	deque<int> q;
	q.push_back(src);
	inque[src] = true;
	ll sum = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop_front();
		if (!q.empty() && (ll)dist[x]*q.size() > sum) {
			q.push_back(x); continue;
		}
		sum -= dist[x];
		inque[x] = false;
		for (int i = g.head[x]; ~i; i = g.next[i]) {
			int y = g.to[i];
			int d = dist[x] + g.len[i];
			if (d < dist[y]) {
				if (inque[y]) { sum += d - dist[y]; }
				dist[y] = d;
				if (!inque[y]) {
					if (!q.empty() && dist[q.front()] > dist[y]) {
						q.push_front(y);
					} else {
						q.push_back(y);
					}
					sum += dist[y];
					inque[y] = true;
				}
			}
		}
	}
}

//bellman-ford + vector O(V*E)
//可以处理负边权图
//可以判断是否存在负环回路,返回true,当且仅当图中不包含从源点可达的负权回路
#define INF 0x3f3f3f3f
int dist[N];
struct Edge {
	int u, v, cost;
	Edge(int _u = 0, int _v = 0, int _cost = 0): u(_u), v(_v), cost(_cost) {}
};
vector<Edge> E;
bool bellman_ford(int start, int n) { //点的编号从1开始
	for (int i = 1; i <= n; i++) { dist[i] = INF; }
	dist[start] = 0;
	for (int i = 1; i < n; i++) {
		bool flag = false;
		for (size_t j = 0; j < E.size(); j++) {
			int u = E[j].u, v = E[j].v, cost = E[j].cost;
			if (dist[v] > dist[u] + cost) {
				dist[v] = dist[u] + cost;
				flag = true;
			}
		}
		if (!flag) { return true; } //没有负环回路
	}
	for (size_t j = 0; j < E.size(); j++) {
		if (dist[E[j].v] > dist[E[j].u] + E[j].cost) { return false; } //有负环回路
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
