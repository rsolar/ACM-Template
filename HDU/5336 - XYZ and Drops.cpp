#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
using namespace std;

#define N 105
#define judge(x,y) ((x)>0&&(x)<=h&&(y)>0&&(y)<=w)

struct A {
	int x, y, sz;
	bool cracked;
} a[N];
struct B {
	int x, y, d;
};
list<B> b;
int h, w, n, t, T, mp[N][N], mov[4][2] = {{ -1, 0}, {0, 1}, {1, 0}, {0, -1}};

inline void getInt(int &x) {
	char c;
	while ((c = getchar()) < '0' || c > '9');
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
}

void oneSecond() {
	for (list<B>::iterator p = b.begin(); p != b.end();) {
		mp[(*p).x][(*p).y] -= 1;
		(*p).x += mov[(*p).d][0], (*p).y += mov[(*p).d][1];
		if (judge((*p).x, (*p).y)) {
			mp[(*p).x][(*p).y] += 1;
			p++;
		} else {
			p = b.erase(p);
		}
	}
	for (int i = 0; i < n; i++) {
		if (!a[i].cracked) {
			for (list<B>::iterator p = b.begin(); p != b.end();) {
				if (a[i].x == (*p).x && a[i].y == (*p).y) {
					a[i].sz++;
					p = b.erase(p);
				} else {
					p++;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (!a[i].cracked && a[i].sz > 4) {
			a[i].sz = t; a[i].cracked = true;
			mp[a[i].x][a[i].y] = 4;
			for (int d = 0; d < 4; d++) { b.push_back((B) {a[i].x, a[i].y, d}); }
		}
	}
}

int main() {
	int x, y;
	while (~scanf("%d %d %d %d", &h, &w, &n, &T)) {
		memset(mp, 0, sizeof(mp));
		b.clear();
		for (int i = 0; i < n; i++) {
			getInt(a[i].x); getInt(a[i].y); getInt(a[i].sz); a[i].cracked = false;
			mp[a[i].x][a[i].y] = a[i].sz;
		}
		getInt(x); getInt(y);
		for (int d = 0; d < 4; d++) { b.push_back((B) {x, y, d}); }
		mp[x][y] = 4;
		for (t = 1; t <= T; t++) { oneSecond(); }
		for (int i = 0; i < n; i++) {
			printf("%d %d\n", !a[i].cracked, a[i].sz);
		}
	}
}
