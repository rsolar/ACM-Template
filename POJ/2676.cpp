#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 10

char mp[N][N];
bool flag, row[N][N], col[N][N], nin[N][N];

void dfs(int n) {
	if (n == -1) {
		flag = true;
		return;
	}
	int x = n / 9, y = n % 9;
	if (mp[x][y] != '0') {
		dfs(n - 1);
	} else {
		for (int i = 1; i <= 9; i++) {
			if (!row[x][i] && !col[y][i] && !nin[x / 3 * 3 + y / 3][i]) {
				mp[x][y] = i + '0'; row[x][i] = true; col[y][i] = true; nin[x / 3 * 3 + y / 3][i] = true;
				dfs(n - 1);
				if (flag) {
					return;
				}
				mp[x][y] = '0'; row[x][i] = false; col[y][i] = false; nin[x / 3 * 3 + y / 3][i] = false;
			}
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	getchar();
	while (T--) {
		memset(row, 0, sizeof(row));
		memset(col, 0, sizeof(col));
		memset(nin, 0, sizeof(nin));
		for (int i = 0; i < 9; i++) {
			gets(mp[i]);
			for (int j = 0; j < 9; j++)
				if (mp[i][j] != '0') {
					row[i][mp[i][j] - '0'] = true; col[j][mp[i][j] - '0'] = true; nin[i / 3 * 3 + j / 3][mp[i][j] - '0'] = true;
				}
		}
		flag = false;
		dfs(81);
		for (int i = 0; i < 9; i++) {
			puts(mp[i]);
		}
	}
}
