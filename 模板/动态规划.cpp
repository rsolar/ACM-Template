//最长上升子序列 非降如注释
int n, a[N], b[N];
int BS(int len, int x) {
  int l = 0, r = len - 1, mid;
  while (l <= r) {
    mid = l + r >> 1;
    if (x > b[mid - 1] && x <= b[mid]) { return mid; } // > && <= 换为 >= && <
    else if (x >= b[mid]) { l = mid + 1; }
    else { r = mid - 1; }
  }
}

int DP() {
  int len = 1;
  b[0] = a[0];
  for (int i = 1, j; i < n; i++) {
    if (a[i] <= b[0]) { j = 0; }  // <= 换为 <
    else if (a[i] > b[len - 1]) { j = len++; } // > 换为 >=
    else { j = BS(len, a[i]); }
    b[j] = a[i];
  }
  return len;
}

//最长公共子序列
int dp[N][N];
int LCS(const char *s1, const char *s2) {
  memset(dp, 0, sizeof(dp));
  int m = strlen(s1), n = strlen(s2);
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (s1[i - 1] == s2[j - 1]) { dp[i][j] = dp[i - 1][j - 1] + 1; }
      else { dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); }
    }
  }
  return a[m][n];
}

void printLCS(const char *s1, const char *s2) {
  char s[N];
  int i = strlen(s1), j = strlen(s2), k = dp[i][j];
  s[k] = '\0';
  while (i && j) {
    if (dp[i][j] == dp[i - 1][j - 1] + 1) { s[--k] = s1[i - 1]; i--; j--; }
    else if (dp[i - 1][j] > dp[i][j - 1]) { i--; }
    else { j--; }
  }
  puts(s);
}

//最长公共递增子序列
int f[N][N], dp[N];
int gcis(int a[], int la, int b[], int lb, int ans[]) {
  //a[1...la], b[1...lb]
  int i, j, k, mx;
  memset(f, 0, sizeof(f));
  memset(dp, 0, sizeof(dp));
  for (i = 1; i <= la; i++) {
    memcpy(f[i], f[i - 1], sizeof(f[0]));
    for (k = 0, j = 1; j <= lb; j++) {
      if (b[j - 1] < a[i - 1] && dp[j] > dp[k]) { k = j; }
      if (b[j - 1] == a[i - 1] && dp[k] + 1 > dp[j]) {
        dp[j] = dp[k] + 1;
        f[i][j] = i * (lb + 1) + k;
      }
    }
  }
  for (mx = 0, i = 1; i <= lb; i++) {
    if (dp[i] > dp[mx]) { mx = i; }
  }
  for (i = la * lb + la + mx, j = dp[mx]; j;
       i = f[i / (lb + 1)][i % (lb + 1)], j--) {
    ans[j - 1] = b[i % (lb + 1) - 1];
  }
  return dp[mx];
}

//最大子段和
int maxSum(int a[], int n, int &st, int &ed) {
  int ret, sum = 0, s, i;
  for (ret = a[st = ed = s = i = 0]; i < n; i++, s = (sum > 0 ? s : i)) {
    if ((sum = (sum > 0 ? sum : 0) + a[i]) > ret) {
      ret = sum; st = s; ed = i;
    }
  }
  return ret;
}

//最大子阵和
int maxSum(int a[][N], int h, int w, int &x1, int &y1, int &x2, int &y2) {
  int asum[N][N], ret, sum, i, j, k, s;
  for (i = 0; i < h; i++) {
    for (asum[i][j = 0] = 0; j < w; j++) {
      asum[i][j + 1] = asum[i][j] + a[i][j];
    }
  }
  for (ret = a[x1 = x2 = 0][y1 = y2 = j = 0]; j < w; j++) {
    for (k = j; k < w; k++) {
      for (sum = s = i = 0; i < h; i++, s = (sum > 0 ? s : i)) {
        if ((sum = (sum > 0 ? sum : 0) + asum[i][k + 1] - asum[i][j]) > ret) {
          ret = sum; x1 = s; y1 = i; x2 = j; y2 = k;
        }
      }
    }
  }
  return ret;
}

//RMQ 一维
//Sparse Table 返回值
int n, a[N];
int dpmn[N][30], dpmx[N][30];
void initRMQ() {
  for (int i = 1; i <= n; i++) { dpmn[i][0] = dpmx[i][0] = a[i]; }
  for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 1; i + (1 << j) - 1 <= n; i++) {
      dpmn[i][j] = min(dpmn[i][j - 1], dpmn[i + (1 << (j - 1))][j - 1]);
      dpmx[i][j] = max(dpmx[i][j - 1], dpmx[i + (1 << (j - 1))][j - 1]);
    }
  }
}

int getMin(int l, int r) {
  int k = (int)(log(r - l + 1.0) / log(2.0));
  return min(dpmn[l][k], dpmn[r - (1 << k) + 1][k]);
}

int getMax(int l, int r) {
  int k = (int)(log(r - l + 1.0) / log(2.0));
  return max(dpmn[l][k], dpmn[r - (1 << k) + 1][k]);
}

//ST 返回下标
int n, a[N];
int dpmn[N][30], dpmx[N][30];
void initRMQ() {
  for (int i = 1; i <= n; i++) { dpmn[i][0] = dpmx[i][0] = i; }
  for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 1; i + (1 << j) - 1 <= n; i++) {
      dpmn[i][j] = a[dpmn[i][j - 1]] < a[dpmn[i + (1 << (j - 1))][j - 1]] ? dpmn[i][j
                   - 1] : dpmn[i + (1 << (j - 1))][j - 1];
      dpmx[i][j] = a[dpmx[i][j - 1]] > a[dpmx[i + (1 << (j - 1))][j - 1]] ? dpmx[i][j
                   - 1] : dpmx[i + (1 << (j - 1))][j - 1];
    }
  }
}

int getMin(int l, int r) {
  int k = (int)(log(r - l + 1.0) / log(2.0));
  return a[dpmn[l][k]] < a[dpmn[r - (1 << k) + 1][k]] ? dpmn[l][k] : dpmn[r -
         (1 << k) + 1][k];
}

int getMax(int l, int r) {
  int k = (int)(log(r - l + 1.0) / log(2.0));
  return a[dpmx[l][k]] > a[dpmx[r - (1 << k) + 1][k]] ? dpmx[l][k] : dpmx[r -
         (1 << k) + 1][k];
}

//RMQ 二维
int n, a[N][N];
int mm[N], dpmn[N][N][9][9],
    dpmx[N][N][9][9]; //mm[]为二进制位数减一，使用前初始化
void initmm() {
  mm[0] = -1;
  for (int i = 1; i < N; i++) {
    mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
  }
}

void initRMQ() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      dpmn[i][j][0][0] = dpmx[i][j][0][0] = a[i][j];
    }
  }
  for (int ii = 0; ii <= mm[n]; ii++) {
    for (int jj = 0; jj <= mm[m]; jj++) {
      if (ii + jj) {
        for (int i = 1; i + (1 << ii) - 1 <= n; i++) {
          for (int j = 1; j + (1 << jj) - 1 <= m; j++) {
            if (ii) {
              dpmn[i][j][ii][jj] = min(dpmn[i][j][ii - 1][jj],
                                       dpmn[i + (1 << (ii - 1))][j][ii - 1][jj]);
              dpmx[i][j][ii][jj] = max(dpmx[i][j][ii - 1][jj],
                                       dpmx[i + (1 << (ii - 1))][j][ii - 1][jj]);
            } else {
              dpmn[i][j][ii][jj] = min(dpmn[i][j][ii][jj - 1],
                                       dpmn[i][j + (1 << (jj - 1))][ii][jj - 1]);
              dpmx[i][j][ii][jj] = max(dpmx[i][j][ii][jj - 1],
                                       dpmx[i][j + (1 << (jj - 1))][ii][jj - 1]);
            }
          }
        }
      }
    }
  }
}

int getMin(int x1, int y1, int x2, int y2) {
  int k1 = mm[x2 - x1 + 1], k2 = mm[y2 - y1 + 1];
  x2 = x2 - (1 << k1) + 1; y2 = y2 - (1 << k2) + 1;
  return min(min(dpmn[x1][y1][k1][k2], dpmn[x1][y2][k1][k2]),
             min(dpmn[x2][y1][k1][k2], dpmn[x2][y2][k1][k2]));
}

int getMax(int x1, int y1, int x2, int y2) {
  int k1 = mm[x2 - x1 + 1], k2 = mm[y2 - y1 + 1];
  x2 = x2 - (1 << k1) + 1; y2 = y2 - (1 << k2) + 1;
  return max(max(dpmx[x1][y1][k1][k2], dpmx[x1][y2][k1][k2]),
             max(dpmx[x2][y1][k1][k2], dpmx[x2][y2][k1][k2]));
}
