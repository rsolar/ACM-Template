#include <iostream>
#include <cstdio>
using namespace std;

#define N 10005

int n, m;
double a[N];

bool judge(double x) {
	int cnt = 0;
	for (int i = 0; i < n; i++) { cnt += a[i] / x; }
	return cnt >= m;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%lf", &a[i]);
	}
	double mid, l = 0, r = 100000.1;
	while (r - l > 1e-3) {
		mid = (l + r) * 0.5;
		if (judge(mid)) { l = mid; }
		else { r = mid; }
	}
	printf("%.2f\n", (int)(r * 100) / 100.0);
}
