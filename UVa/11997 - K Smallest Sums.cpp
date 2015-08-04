#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

#define N 755

struct Node {
	int s, b;
	friend bool operator<(Node a, Node b) { return a.s > b.s; }
};
int k, a[N], b[N];

inline void getInt(int &x) {
	char c;
	while ((c = getchar()) < '0' || c > '9');
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
}

void Merge() {
	priority_queue<Node> que;
	for (int i = 0; i < k; i++) { que.push((Node) {a[i] + b[0], 0}); }
	for (int i = 0; i < k; i++) {
		a[i] = que.top().s;
		if (que.top().b + 1 < k) { que.push((Node) {que.top().s - b[que.top().b] + b[que.top().b + 1], que.top().b + 1}); }
		que.pop();
	}
}

int main() {
	while (~scanf("%d", &k)) {
		for (int j = 0; j < k; j++) { getInt(a[j]); }
		sort(a, a + k);
		for (int i = 1; i < k; i++) {
			for (int j = 0; j < k; j++) { getInt(b[j]); }
			sort(b, b + k);
			Merge();
		}
		for (int i = 0; i < k; i++) {
			if (i) { putchar(' '); }
			printf("%d", a[i]);
		}
		putchar('\n');
	}
}
