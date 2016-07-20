//Joseph问题 O(n)
int Joseph(int n, int m, int s) {
  int ret = s - 1;
  for (int i = 2; i <= n; i++) { ret = (ret + m) % i; }
  return ret + 1;
}
//O(logn) 0 <= k < n
int Joseph(int n, int m, int k) {
  if (m == 1) { return n - 1; }
  for (k = k * m + m - 1; k >= n; k = k - n + (k - n) / (m - 1));
  return k;
}
//康托展开 fac[]为阶乘 0 <= ans
ll Cantor(char *s) {
  ll ans = 0;
  for (int i = 0, len = strlen(s); i < len; i++) {
    int cnt = 0;
    for (int j = i + 1; j < len; j++) { if (s[j] < s[i]) { cnt++; } }
    ans += cnt * fac[len - i - 1];
  }
  return ans;
}
//康托展开逆运算 1 <= k <= n!
vector<int> revCantor(ll n, ll k) {
  vector<int> v, ret; k--;
  for (int i = 1; i <= n; i++) { v.push_back(i); }
  for (int i = n; i >= 1; i--) {
    ll t = k / fac[i - 1]; k %= fac[i - 1];
    sort(v.begin(), v.end());
    ret.push_back(v[t]); v.erase(v.begin() + t);
  }
  return ret;
}
//lydsy 1057: [ZJOI2007]棋盘制作
//求最大子矩形及正方形
//单调栈
int n, m, h[N];
bool a[N][N];
int main() {
  while (~scanf("%d%d", &n, &m)) {
    for (int i = 1, t; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        scanf("%d", &t); a[i][j] = (t & 1) ^ ((i + j) & 1);
      }
    }
    int rec = 0, sqr = 0;
    memset(h, 0, sizeof(h));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) { h[j] = a[i][j] ? h[j] + 1 : 0; }
      stack<int> st; st.push(0);
      for (int j = 1; j <= m + 1; j++) {
        while (h[j] < h[st.top()]) {
          int t = h[st.top()]; st.pop();
          int w = j - st.top() - 1;
          sqr = max(sqr, min(t, w) * min(t, w)); rec = max(rec, t * w);
        }
        st.push(j);
      }
    }
    memset(h, 0, sizeof(h));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) { h[j] = !a[i][j] ? h[j] + 1 : 0; }
      stack<int> st; st.push(0);
      for (int j = 1; j <= m + 1; j++) {
        while (h[j] < h[st.top()]) {
          int t = h[st.top()]; st.pop();
          int w = j - st.top() - 1;
          sqr = max(sqr, min(t, w) * min(t, w)); rec = max(rec, t * w);
        }
        st.push(j);
      }
    }
    printf("%d\n%d\n", sqr, rec);
  }
}
//dp 悬线法
int n, m, l[N], r[N], h[N];
bool a[N][N];
int main() {
  while (~scanf("%d%d", &n, &m)) {
    memset(h, 0, sizeof(h));
    for (int i = 1, t; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        scanf("%d", &t); a[i][j] = t;
      }
    }
    int sqr = 1, rec = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        l[j] = r[j] = j; h[j] = a[i][j] != a[i - 1][j] ? h[j] + 1 : 1;
      }
      for (int j = 2; j <= m; j++) {
        while (l[j] - 1 >= 1 && a[i][l[j] - 1] != a[i][l[j]] && h[l[j] - 1] >= h[j]) {
          l[j] = l[l[j] - 1];
        }
      }
      for (int j = m - 1; j >= 1; j--) {
        while (r[j] + 1 <= m && a[i][r[j] + 1] != a[i][r[j]] && h[r[j] + 1] >= h[j]) {
          r[j] = r[r[j] + 1];
        }
      }
      for (int j = 1; j <= m; j++) {
        int w = r[j] - l[j] + 1;
        sqr = max(sqr, min(h[j], w) * min(h[j], w));
        rec = max(rec, h[j] * w);
      }
    }
    printf("%d\n%d\n", sqr, rec);
  }
}
//二叉树前序 + 中序求后序遍历
void getPost(char *pre, char *in, int len) {
  if (len == 0) { return; }
  int root = 0;
  for (; root < len && in[root] != *pre; root++);
  getPost(pre + 1, in, root);
  getPost(pre + root + 1, in + root + 1, len - root - 1);
  putchar(*pre);
}
//求1到n之间1的个数
ll countOne(ll n) {
  ll ret = 0;
  for (ll m = 1; m <= n; m *= 10) {
    ll a = n / m, b = n % m;
    ret += (a + 8) / 10 * m + (a % 10 == 1) * (b + 1);
  }
  return ret;
}
//求1到n所有数字的数位和的和 数位DP
char t[N];
ll dp[N][N][N];
ll countDigit(char *s) {
  ll ret = 0;
  for (int i = 1, n = strlen(s); i <= n; i++) { t[i] = s[i - 1] - '0'; }
  for (int i = 0; i <= t[1]; i++) { dp[1][i][i == t[1]] = 1; }
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= 900; j++) {
      if (dp[i][j][0]) {
        for (int k = 0; k <= 9; k++) { dp[i + 1][j + k][0] += dp[i][j][0]; dp[i + 1][j + k][0] %= M; }
      }
      if (dp[i][j][1]) {
        for (int k = 0; k <= t[i + 1]; k++) { dp[i + 1][j + k][k == t[i + 1]] += dp[i][j][1]; dp[i + 1][j + k][k == t[i + 1]] %= M; }
      }
    }
  }
  for (int j = 1; j <= 900; j++) { ret += dp[n][j][0] * dp[n][j][1] % M; ret %= M; }
  return ret;
}
//树hash
int hs[N], P[N]; //一些质数
void dfs(int u, int p) {
  vector<int> t; t.push_back(1);
  for (int i = 0; i < (int)e[u].size(); i++) {
    int v = e[u][i];
    if (v == p) { continue; }
    dfs(v, u); t.push_back(hs[v]);
  }
  sort(t.begin(), t.end()); hs[u] = 0;
  for (int i = 0; i < (int)t.size(); i++) { hs[u] += t[i] * P[i]; }
}
for (int j = 1; j <= n; j++) {
  dfs(j, 0); //cout << j << ' ' << hs[j] << endl;
}
sort(hs[i] + 1, hs[i] + n + 1);
//小数转化为分数
//把小数转化为分数, 循环部分用()表示
void work(char str[]) {
  int len = strlen(str), cnt1 = 0, cnt2 = 0;
  ll a = 0, b = 0; bool flag = false;
  for (int i = 2; i < len; i++) {
    if (str[i] == '(') { break; }
    a = a * 10 + str[i] - '0'; cnt1++;
  }
  for (int i = 2; i < len; i++) {
    if (str[i] == '(' || str[i] == ')') { flag = true; continue; }
    b = b * 10 + str[i] - '0'; cnt2++;
  }
  ll p = b - a, q = 0; cnt2 -= cnt1;
  if (!flag) { p = b; q = 1; cnt2 = 0; }
  for (int i = 0; i < cnt2; i++) { q = q * 10 + 9; }
  for (int i = 0; i < cnt1; i++) { q = q * 10; }
  ll g = gcd(p, q);
  printf("%I64d/%I64d\n", p / g, q / g);
}
//分数转化为小数
//定理: 有理数a / b(其中0 < a < b，(a, b) = 1)能表示成纯循环小数的充要条件是(b, 10) = 1
//定理: 有理数a / b, 0 < a < b, (a, b) = 1, b = (2 ^ α) * (5 ^ β) * b1, (b1, 10) = 1,
//      b1不等于1，α，β不全为零，则a / b可以表示为纯循环小数，其不循环的位数为u = max(α, β)
void work(int n) {
  bool flag = false;
  int ans[N] = { 0 }, f[N] = { 0, 1 }, k = 1, cnt = 0;
  if (n < 0) { n = -n; flag = 1; }
  while (k && n != 1) {
    k *= 10; ans[cnt++] = k / n; k %= n;
    if (f[k]) { break; }
    f[k] = 1;
  }
  if (flag) { printf("-"); }
  if (n == 1) { puts("1"); }
  else {
    printf("0.");
    for (int i = 0; i < cnt; i++) { printf("%d", ans[i]); }
    puts("");
  }
}
//水仙花数 A023052 Powerful numbers(3): numbers n that are the sum of some fixed power of their digits.
int Nar[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407, 1634, 4150, 4151, 8208, 9474, 54748, 92727, 93084,
              194979, 548834, 1741725, 4210818, 9800817, 9926315, 14459929, 24678050, 24678051, 88593477
            };
//完数 A000396 Perfect numbers n: n is equal to the sum of the proper divisors of n.
string str[] = {
  "6",
  "28",
  "496",
  "8128",
  "33550336",
  "8589869056",
  "137438691328",
  "2305843008139952128",
  "2658455991569831744654692615953842176",
  "191561942608236107294793378084303638130997321548169216",
  "13164036458569648337239753460458722910223472318386943117783728128",
  "14474011154664524427946373126085988481573677491474835889066354349131199152128",
  "23562723457267347065789548996709904988477547858392600710143027597506337283178622239730365539602600561360255566462503270175052892578043215543382498428777152427010394496918664028644534128033831439790236838624033171435922356643219703101720713163527487298747400647801939587165936401087419375649057918549492160555646976"
};
