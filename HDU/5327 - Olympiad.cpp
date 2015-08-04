#include <iostream>
#include <cstdio>
using namespace std;

#define N 100005

int a[N] = {1};

bool judge(int n) {
	bool vis[10] = {false};
	while (n != 0) {
		if (vis[n % 10]) { return false; }
		vis[n % 10] = true; n /= 10;
	}
	return true;
}

int main() {
	for (int i = 1; i < N; i++) {
		if (judge(i)) { a[i] = a[i - 1] + 1; }
		else { a[i] = a[i - 1]; }
	}
	int T, n, m;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		printf("%d\n", a[m] - a[n - 1]);
	}
}
