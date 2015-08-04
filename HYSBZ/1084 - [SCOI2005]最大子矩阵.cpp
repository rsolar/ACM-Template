#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 105

int h, w, k, a[N][3], sum[N][3], dp1[N][11], dp2[N][N][11];
//sum[i][j]表示第j列前缀和
//dp1[i][k]表示第一列到第i行,选出k个子矩阵
//dp2[i][j][k]表示第一列到第i行,第二列到第j行,选出k个子矩阵

inline void getInt(int &x) {
	char c = 0; int sign = 1;
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
}

int main() {
	while (~scanf("%d %d %d", &h, &w, &k)) {
		for (int i = 1; i <= h; i++) {
			for (int j = 1; j <= w; j++) {
				getInt(a[i][j]);
				sum[i][j] = sum[i - 1][j] + a[i][j];
			}
		}
		//1<=w<=2
		if (w == 1) {
			for (int i = 1; i <= h; i++) {
				for (int l = 1; l <= k; l++) {
					dp1[i][l] = dp1[i - 1][l];
					//不选a[i][1]时
					for (int ii = 0; ii < i; ii++) {
						dp1[i][l] = max(dp1[i][l], dp1[ii][l - 1] + sum[i][1] - sum[ii][1]);
						//尝试分为1...ii和(ii+1)...i两块
					}
				}
			}
			printf("%d\n", dp1[h][k]);
		} else {
			for (int i = 1; i <= h; i++) {
				for (int j = 1; j <= h; j++) {
					for (int l = 1; l <= k; l++) {
						dp2[i][j][l] = max(dp2[i - 1][j][l], dp2[i][j - 1][l]);
						//前i行 不选a[i][j]时
						for (int ii = 0; ii < i; ii++) {
							dp2[i][j][l] = max(dp2[i][j][l], dp2[ii][j][l - 1] + sum[i][1] - sum[ii][1]);
							//第一列分为1...ii和(ii+1)...i两块
						}
						for (int jj = 0; jj < j; jj++) {
							dp2[i][j][l] = max(dp2[i][j][l], dp2[i][jj][l - 1] + sum[j][2] - sum[jj][2]);
							//第二列分为1...jj和(jj+1)...j两块
						}
						if (i == j) {
							for (int ii = 0; ii < i; ii++) {
								dp2[i][i][l] = max(dp2[i][i][l], dp2[ii][ii][l - 1] + sum[i][1] - sum[ii][1] + sum[j][2] - sum[ii][2]);
								//i==j时可选宽为2的子矩阵
							}
						}
					}
				}
			}
			printf("%d\n", dp2[h][h][k]);
		}
	}
}
