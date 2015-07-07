#include <iostream>
#include <cstdio>
using namespace std;

#define N 101

struct Step {
	int a, b, step, op;
	char ans[200];
} que[N *N], t;
int a, b, c;
bool vis[N][N];
char *ans[] = {"FILL(1)", "FILL(2)", "DROP(1)", "DROP(2)", "POUR(1,2)", "POUR(2,1)"};

bool bfs() {
	int front = 0, back = 0;
	Step p = {0};
	vis[0][0] = 1;
	que[back++] = p;
	while (front < back) {
		p = que[front++];
		for (int i = 0; i < 6; i++) {
			t = p;
			switch (i) {
				case 0:
					t.a = a; t.op = 0; break;
				case 1:
					t.b = b; t.op = 1; break;
				case 2:
					t.a = 0; t.op = 2; break;
				case 3:
					t.b = 0; t.op = 3; break;
				case 4:
					if (t.a + t.b <= b) {
						t.b += t.a;
						t.a = 0;
					} else {
						t.a -= b - t.b;
						t.b = b;
					}
					t.op = 4; break;
				case 5:
					if (t.a + t.b <= a) {
						t.a += t.b;
						t.b = 0;
					} else {
						t.b -= a - t.a;
						t.a = a;
					}
					t.op = 5; break;
			}
			if (!vis[t.a][t.b]) {
				t.step = p.step + 1;
				t.ans[p.step] = t.op;
				vis[t.a][t.b] = true;
				if (t.a == c || t.b == c) {
					return true;
				}
				que[back++] = t;
			}
		}
	}
	return false;
}

int main() {
	scanf("%d%d%d", &a, &b, &c);
	if (bfs()) {
		printf("%d\n", t.step);
		for (int i = 0; i < t.step; i++) {
			puts(ans[t.ans[i]]);
		}
	} else {
		puts("impossible");
	}
}
