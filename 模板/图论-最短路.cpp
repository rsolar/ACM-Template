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

//Dijkstra + 邻接矩阵
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

//Dijkstra + priority_queue + 邻接表
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

//SPFA + SLF + LLL + 邻接表
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

//floyd 带路径记录
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
