#include <bits/stdc++.h>
using namespace std;

#define N 35

int h, w, mp[N][N], dp[N][N][1805];

int main() {
  int C = 0, T;
  scanf("%d", &T);
  while (++C <= T) {
    scanf("%d %d", &h, &w);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        scanf("%d", &mp[i][j]);
      }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][mp[0][0]] = mp[0][0] * mp[0][0];
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        for (int k = 0; k <= 1800; k++) {
          if (k >= mp[i][j]) {
            if (i) { dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k - mp[i][j]] + mp[i][j] * mp[i][j]); }
            if (j) { dp[i][j][k] = min(dp[i][j][k], dp[i][j - 1][k - mp[i][j]] + mp[i][j] * mp[i][j]); }
          }
        }
      }
    }
    int ans = INT_MAX;
    for (int k = 0, t = h + w - 1; k <= 1800; k++) {
      if (dp[h - 1][w - 1][k] != 0x3f3f3f3f) {
        ans = min(ans, t * dp[h - 1][w - 1][k] - k * k);
      }
    }
    printf("Case #%d: %d\n", C, ans);
  }
}
