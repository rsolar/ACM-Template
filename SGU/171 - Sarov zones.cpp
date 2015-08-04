#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 16005
#define K 105

struct Stu {
	int id, level, weight;
} s[N];
struct Zone {
	int id, level, num;
} z[K];
int k, n, ans[N];

inline void getInt(int &x) {
	char c = 0; int sign = 1;
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
}

bool cmp1(Stu a, Stu b) {
	return a.weight > b.weight;
}

bool cmp2(Zone a, Zone b) {
	return a.level > b.level;
}

int main() {
	scanf("%d", &k);
	for (int i = 1; i <= k; i++) { getInt(z[i].num); z[i].id = i; n += z[i].num; }
	for (int i = 1 ; i <= k; i++) { getInt(z[i].level); }
	for (int i = 1 ; i <= n; i++) { getInt(s[i].level); s[i].id = i; }
	for (int i = 1 ; i <= n; i++) { getInt(s[i].weight); }
	sort(s + 1, s + n + 1, cmp1);
	sort(z + 1, z + k + 1, cmp2);
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			if (z[i].num > 0) {
				if (ans[s[j].id] == 0 && s[j].level > z[i].level) {
					ans[s[j].id] = z[i].id; z[i].num--;
				}
			} else {
				break;
			}
		}
	}
	for (int i = 1, j = 1; i <= k; i++) {
		while (z[i].num > 0) {
			if (ans[s[j].id] == 0) {
				ans[s[j].id] = z[i].id; z[i].num--;
			}
			j++;
		}
	}
	for (int j = 1; j <= n; j++) {
		if (j != 1) { putchar(' '); }
		printf("%d", ans[j]);
	}
	putchar('\n');
}
