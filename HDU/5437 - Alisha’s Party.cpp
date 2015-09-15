#include <bits/stdc++.h>
using namespace std;

#define N 150005
#define M 205

struct Node {
	char name[M];
	int val, id;
} s[N];
int n, m, q, w;
pair<int, int> t[N];

bool operator<(Node a, Node b) {
	return a.val < b.val || (a.val == b.val && a.id > b.id);
}

priority_queue<Node> que;
vector<int> ans;

int main() {
	int C = 0, T;
	scanf("%d", &T);
	while (++C <= T) {
		ans.clear();
		scanf("%d %d %d", &n, &m, &q);
		for (int i = 0; i < n; i++) {
			scanf("%s %d", s[i].name, &s[i].val); s[i].id = i;
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &t[i].first, &t[i].second);
		}
		sort(t, t + m);
		int crt = 0, crtt = 0;
		for (int i = 0; i < q; i++) {
			scanf("%d", &w);
			while (ans.size() < w) {
				if (crtt < m) {
					for (; crt < t[crtt].first; crt++) {
						que.push(s[crt]);
					}
					while (t[crtt].second-- && !que.empty()) {
						ans.push_back(que.top().id); que.pop();
					}
					crtt++;
				} else {
					for (; crt < n; crt++) {
						que.push(s[crt]);
					}
					while (!que.empty()) {
						ans.push_back(que.top().id); que.pop();
					}
				}
			}
			if (i) { putchar(' '); }
			printf("%s", s[ans[w - 1]].name);
		}
		putchar('\n');
	}
}
