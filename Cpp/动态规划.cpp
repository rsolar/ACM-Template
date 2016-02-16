//最大子段和 O(n)
ll maxSum(int a[], int n, int &st, int &ed) {
  ll ret = a[0], sum = 0; st = ed = 0;
  for (int i = 0, s = 0; i < n; i++, s = sum > 0 ? s : i) {
    if ((sum = max(sum, 0LL) + a[i]) > ret) { ret = sum; st = s; ed = i; }
  }
  return ret;
}
//循环数组最大子段和 O(n)
ll maxSum_adj(int a[], int n) {
  ll ret_notadj = maxSum(a, n); //不跨界最大子段和
  if (ret_notadj < 0) { return ret_notadj; }
  ll sum = 0, mnsum = INT_MAX, mntmp = 0;
  for (int i = 0; i < n; i++) {
    if (mntmp > 0) { mntmp = a[i]; } else { mntmp += a[i]; }
    if (mntmp < mnsum) { mnsum = mntmp; }
    sum += a[i];
  }
  ll ret_adj = sum - mnsum;
  return max(ret_notadj, ret_adj);
}
//最大子阵和 O(n^3)
ll presum[N][N];
ll maxSum(int a[][N], int h, int w, int &x1, int &y1, int &x2, int &y2) {
  ll ret = a[0][0], sum; x1 = y1 = x2 = y2 = 0;
  for (int i = 0, j; i < h; i++) {
    for (presum[i][j = 0] = 0; j < w; j++) {
      presum[i][j + 1] = presum[i][j] + a[i][j];
    }
  }
  for (int j = 0, k, i, s; j < w; j++) {
    for (k = j; k < w; k++) {
      for (sum = s = i = 0; i < h; i++, s = (sum > 0 ? s : i)) {
        if ((sum = max(sum, 0LL) + presum[i][k + 1] - presum[i][j]) > ret) {
          ret = sum; x1 = s; y1 = i; x2 = j; y2 = k;
        }
      }
    }
  }
  return ret;
}
//最长上升子序列 LIS O(nlogn)
int b[N];
int LIS(int a[], int n) {
  int len = 1; b[0] = a[0];
  for (int i = 1; i < n; i++) {
    b[a[i] > b[len - 1] ? len++ : upper_bound(b, b + len, a[i]) - b] = a[i]; //非降换为lower_bound
  }
  return len;
}
//长度为k的上升子序列个数 O(knlogn)
int n, k;
ll bit[M][N];
inline int lowbit(int x) { return x & -x; }
void add(int id, int i, ll val) { while (i <= n) { bit[id][i] += val; i += lowbit(i); } }
ll sum(int id, int i) {
  ll ret = 0;
  while (i) { ret += bit[id][i]; i -= lowbit(i); }
  return ret;
}
int main() {
  scanf("%d%d", &n, &k);
  add(0, 1, 1);
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    for (int j = 1; j <= k; j++) { add(j, x, sum(j - 1, x - 1)); } //非降改为x
  }
  printf("%I64d\n", sum(k, n)); //n为元素最大值
}
//最长公共子序列 LCS O(n^2)
int dp[N][N];
int LCS(char *a, char *b) {
  int m = strlen(a), n = strlen(b);
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (a[i - 1] == b[j - 1]) { dp[i][j] = dp[i - 1][j - 1] + 1; }
      else { dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); }
    }
  }
  return dp[m][n];
}
void printLCS(char *a, char *b) {
  char s[N] = {0};
  for (int i = strlen(a), j = strlen(b), k = dp[i][j]; i && j;) {
    if (a[i - 1] == b[j - 1] && dp[i][j] == dp[i - 1][j - 1] + 1) { s[--k] = a[--i]; --j; }
    else if (dp[i - 1][j] > dp[i][j - 1]) { i--; }
    else { j--; }
  }
  puts(s);
}
//最长公共子串 LCSubstring
//DP O(n^2)
int dp[2][N];
int LCS_dp(char *s1, char *s2, int &start1, int &start2) {
  int m = strlen(s1), n = strlen(s2), longest = 0, cur = 0; start1 = start2 = -1;
  for (int i = 0; i < m; i++, cur ^= 1) {
    for (int j = 0; j < n; j++) {
      if (s1[i] == s2[j]) {
        if (i == 0 || j == 0) { dp[cur][j] = 1; }
        else { dp[cur][j] = dp[cur ^ 1][j - 1] + 1; }
        if (dp[cur][j] > longest) { longest = dp[cur][j]; start1 = i + 1 - longest; start2 = j + 1 - longest; }
      }
    }
  }
  //outputLCS(s1, longest, start1);
  return longest;
}
//后缀数组 O(nlogn)
char *suf[N];
int pstrcmp(const void *p, const void *q) {
  return strcmp(*(char **)p, *(char **)q);
}
int comlen_suf(const char *p, const char *q) {
  int len = 0;
  while (*p && *q && *p++ == *q++) {
    len++;
    if (*p == '#' || *q == '#') { return len; }
  }
  return 0;
}
int LCS_suffix(char *s1, char *s2) {
  int m = strlen(s1), n = strlen(s2), longest = 0, suf_index = 0, len_suf = m + n + 1;
  char *arr = new char[len_suf + 1];
  strcpy(arr, s1); arr[m] = '#'; strcpy(arr + m + 1, s2);
  for (int i = 0; i < len_suf; i++) { suf[i] = &arr[i]; }
  qsort(suf, len_suf, sizeof(char *), pstrcmp);
  for (int i = 0; i < len_suf - 1; i++) {
    int len = comlen_suf(suf[i], suf[i + 1]);
    if (len > longest) { longest = len; suf_index = i; }
  }
  //outputLCS(suf[suf_index], longest);
  return longest;
}
void outputLCS(char *s, int longest, int start = 0) {
  int i = start;
  while (longest--) {
    printf("%c", s[i++]);
  }
  puts("");
}
//最长公共递增子序列 GCIS O(n^2)
int f[N][N], dp[N];
int GCIS(int a[], int la, int b[], int lb, int ans[]) {
  //a[1...la], b[1...lb]
  int i, j, k, mx;
  memset(f, 0, sizeof(f));
  memset(dp, 0, sizeof(dp));
  for (i = 1; i <= la; i++) {
    memcpy(f[i], f[i - 1], sizeof(f[0]));
    for (k = 0, j = 1; j <= lb; j++) {
      if (b[j - 1] < a[i - 1] && dp[j] > dp[k]) { k = j; }
      if (b[j - 1] == a[i - 1] && dp[k] + 1 > dp[j]) {
        dp[j] = dp[k] + 1; f[i][j] = i * (lb + 1) + k;
      }
    }
  }
  for (mx = 0, i = 1; i <= lb; i++) {
    if (dp[i] > dp[mx]) { mx = i; }
  }
  for (i = la * lb + la + mx, j = dp[mx]; j; i = f[i / (lb + 1)][i % (lb + 1)], j--) {
    ans[j - 1] = b[i % (lb + 1) - 1];
  }
  return dp[mx];
}
//字符串编辑距离 (Levenshtein距离)
char S[N], T[N];
int dp[N][N];
int LenvDist(char S[], char T[]) {
  int n = strlen(S), m = strlen(T);
  for (int i = 0; i <= n; i++) { dp[i][0] = i; }
  for (int i = 0; i <= m; i++) { dp[0][i] = i; }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
      if (S[i - 1] == T[j - 1]) { dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]); }
      else { dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1); }
    }
  }
  return dp[n][m];
}
//字符串距离
//非空格字符的距离定义为它们的ASCII码的差的绝对值, 空格字符与其它任意字符之间的距离为已知的定值k
char S[N], T[N];
int dp[N][N];
int Dist(char S[], char T[], int k) {
  int n = strlen(S), m = strlen(T);
  for (int i = 0; i <= n; i++) { dp[i][0] = i * k; }
  for (int i = 1; i <= m; i++) { dp[0][i] = i * k; }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = min(dp[i - 1][j - 1] + abs(S[i - 1] - T[j - 1]), min(dp[i - 1][j], dp[i][j - 1]) + k);
    }
  }
  return dp[n][m];
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
  return max(dpmx[l][k], dpmx[r - (1 << k) + 1][k]);
}
//ST 返回下标
int n, a[N];
int dpmn[N][30], dpmx[N][30];
void initRMQ() {
  for (int i = 1; i <= n; i++) { dpmn[i][0] = dpmx[i][0] = i; }
  for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 1; i + (1 << j) - 1 <= n; i++) {
      dpmn[i][j] = a[dpmn[i][j - 1]] < a[dpmn[i + (1 << (j - 1))][j - 1]] ? dpmn[i][j - 1] : dpmn[i + (1 << (j - 1))][j - 1];
      dpmx[i][j] = a[dpmx[i][j - 1]] > a[dpmx[i + (1 << (j - 1))][j - 1]] ? dpmx[i][j - 1] : dpmx[i + (1 << (j - 1))][j - 1];
    }
  }
}
int getMin(int l, int r) {
  int k = (int)(log(r - l + 1.0) / log(2.0));
  return a[dpmn[l][k]] < a[dpmn[r - (1 << k) + 1][k]] ? dpmn[l][k] : dpmn[r - (1 << k) + 1][k];
}
int getMax(int l, int r) {
  int k = (int)(log(r - l + 1.0) / log(2.0));
  return a[dpmx[l][k]] > a[dpmx[r - (1 << k) + 1][k]] ? dpmx[l][k] : dpmx[r - (1 << k) + 1][k];
}
//RMQ 二维
int n, a[N][N];
int mm[N], dpmn[N][N][9][9], dpmx[N][N][9][9]; //mm[]为二进制位数减一，使用前初始化
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
              dpmn[i][j][ii][jj] = min(dpmn[i][j][ii - 1][jj], dpmn[i + (1 << (ii - 1))][j][ii - 1][jj]);
              dpmx[i][j][ii][jj] = max(dpmx[i][j][ii - 1][jj], dpmx[i + (1 << (ii - 1))][j][ii - 1][jj]);
            } else {
              dpmn[i][j][ii][jj] = min(dpmn[i][j][ii][jj - 1], dpmn[i][j + (1 << (jj - 1))][ii][jj - 1]);
              dpmx[i][j][ii][jj] = max(dpmx[i][j][ii][jj - 1], dpmx[i][j + (1 << (jj - 1))][ii][jj - 1]);
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
  return min(min(dpmn[x1][y1][k1][k2], dpmn[x1][y2][k1][k2]), min(dpmn[x2][y1][k1][k2], dpmn[x2][y2][k1][k2]));
}
int getMax(int x1, int y1, int x2, int y2) {
  int k1 = mm[x2 - x1 + 1], k2 = mm[y2 - y1 + 1];
  x2 = x2 - (1 << k1) + 1; y2 = y2 - (1 << k2) + 1;
  return max(max(dpmx[x1][y1][k1][k2], dpmx[x1][y2][k1][k2]), max(dpmx[x2][y1][k1][k2], dpmx[x2][y2][k1][k2]));
}
