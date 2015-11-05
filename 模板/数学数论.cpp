//快速幂
ll powMod(ll a, ll b, ll m) {
  ll r = 1; a %= m;
  while (b) {
    if (b & 1) { r = r * a % m; }
    a = a * a % m;
    b >>= 1;
  }
  return r;
}
//素数筛 Eratosthenes [0, N)
const int N = 10000000; //200ms
bool isprime[N];
void getPrime() {
  memset(isprime, -1, sizeof(isprime));
  isprime[0] = isprime[1] = false;
  for (int i = 2; i < N; i++) {
    if (isprime[i]) {
      for (ll j = (ll)i * i; j < N; j += i) { isprime[j] = false; }
    }
  }
}
//素数表 Euler [2, N] prime[0]为个数
const int N = 10000000; //160ms
int prime[N + 1];
void getPrime() {
  for (int i = 2; i <= N; i++) {
    if (!prime[i]) { prime[++prime[0]] = i; }
    for (int j = 1; j <= prime[0] && prime[j] <= N / i; j++) {
      prime[prime[j] * i] = 1;
      if (i % prime[j] == 0) { break; }
    }
  }
}
//素数筛 + 素数表 Euler [0, N)
const int N = 10000000; //100ms
bool isprime[N];
int prime[N];
void getPrime() {
  memset(isprime, -1, sizeof(isprime));
  isprime[0] = isprime[1] = false;
  for (int i = 2; i <= N; i++) {
    if (isprime[i]) {
      prime[++prime[0]] = i;
      for (int j = 1; j <= prime[0] && prime[j] <= N / i; j++) {
        isprime[prime[j] * i] = false;
        if (i % prime[j]) { break; }
      }
    }
  }
}
//分解质因数 需素数表
ll factor[100];
int getFactors(ll x) {
  int fatCnt = 0;
  for (int i = 1; prime[i] <= x / prime[i]; i++) {
    if (x % prime[i] == 0) {
      factor[fatCnt++] = prime[i];
      while (x % prime[i] == 0) { x /= prime[i]; }
    }
  }
  if (x != 1) { factor[fatCnt++] = x; }
  return fatCnt;
}
//分解质因数及求个数 需素数表
ll factor[100][2];
int getFactors(ll x) {
  int fatCnt = 0;
  for (int i = 1; prime[i] <= x / prime[i]; i++) {
    factor[fatCnt][1] = 0;
    if (x % prime[i] == 0) {
      factor[fatCnt][0] = prime[i];
      while (x % prime[i] == 0) {
        factor[fatCnt][1]++;
        x /= prime[i];
      }
      fatCnt++;
    }
  }
  if (x != 1) { factor[fatCnt][0] = x; factor[fatCnt++][1] = 1; }
  return fatCnt;
}
//Miller Rabin素数测试
const int Times = 7; //错误概率为1/4^Times
//大数乘法
ll mulMod(ll a, ll b, ll m) {
  ll r = 0; a %= m; b %= m;
  while (b) {
    if (b & 1) { r = (r + a) % m; }
    a = (a << 1) % m;
    b >>= 1;
  }
  return r;
}
//大数快速幂
ll powMod(ll a, ll b, ll m) {
  ll r = 1; a %= m;
  while (b) {
    if (b & 1) { r = mulMod(r, a, m); }
    a = mulMod(a, a, m);
    b >>= 1;
  }
  return r;
}
//Miller Rabin
bool Miller_Rabin(ll n) {
  if (n == 2) { return true; }
  if (n < 2 || (n & 1) == 0) { return false; }
  ll m = n - 1; int k = 0;
  while ((m & 1) == 0) { k++; m >>= 1; }
  for (int i = 0; i < Times; i++) {
    ll a = rand() % (n - 1) + 1, x = powMod(a, m, n), y = 0;
    for (int j = 0; j < k; j++) {
      y = mulMod(x, x, n);
      if (y == 1 && x != 1 && x != n - 1) { return false; }
      x = y;
    }
    if (y != 1) { return false; }
  }
  return true;
}
//pollard rho质因素分解
ll factor[100]; //质因素分解结果(无序)
int tol; //质因素个数
//找出一个因子
ll pollard_rho(ll x, ll c) {
  srand(time(NULL));
  ll i = 1, k = 2, x0 = rand() % (x - 1) + 1, y = x0;
  while (true) {
    i++;
    x0 = (mulMod(x0, x0, x) + c) % x;
    ll d = llabs(__gcd(y - x0, x));
    if (d != 1 && d != x) { return d; }
    if (y == x0) { return x; }
    if (i == k) {y = x0; k += k;}
  }
}
//对n进行素因子分解,存入factor,k设置为107左右即可
void findfac(ll n, int k = 107) {
  if (n == 1) { return; }
  if (Miller_Rabin(n)) { factor[tol++] = n; return; }
  ll p = n;
  int c = k;
  while (p >= n) { p = pollard_rho(p, c--); } //值变化，防止死循环k
  findfac(p, k);
  findfac(n / p, k);
}
//求单个数的欧拉函数+合数分解
int getFacEul(ll n, ll factor[][2] = factor) {
  int fatCnt = getFactors(n);
  for (int i = 0; i < fatCnt; i++) {
    n = n / factor[i][0] * (factor[i][0] - 1);
  }
  return fatCnt;
}
//求单个数的欧拉函数
ll eular(ll n) {
  ll ans = n;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      ans -= ans / i;
      while (n % i == 0) { n /= i; }
    }
  }
  if (n > 1) { ans -= ans / n; }
  return ans;
}
//欧拉函数表 [1, N)
const int N = 10000000; //~430ms
int phi[N + 5] = { 0, 1 };
void getPhi() {
  for (int i = 2; i < N; i++) {
    if (!phi[i]) {
      phi[i] = i - 1;
      for (int j = i + i; j < N; j += i) {
        if (!phi[j]) { phi[j] = j; }
        phi[j] = phi[j] / i * (i - 1);
      }
    }
  }
}
//素数表 + 欧拉函数表 线性筛 [1, N)
const int N = 10000000; //~160ms
bool check[N + 5];
int prime[N], phi[N + 5], tot; //素数的个数
void getPrimePhi() {
  tot = 0; phi[1] = 1;
  for (int i = 2; i < N; i++) {
    if (!check[i]) { prime[tot++] = i; phi[i] = i - 1; }
    for (int j = 0; j < tot; j++) {
      if (i * prime[j] >= N) { break; }
      check[i * prime[j]] = true;
      if (i % prime[j] == 0) { phi[i * prime[j]] = phi[i] * prime[j]; break; }
      else { phi[i * prime[j]] = phi[i] * (prime[j] - 1); }
    }
  }
}
//求逆元(ax = 1(mod m)的x值)
//扩展欧几里得(求ax + by = gcd(a, b)的解),求出的x为a对b的模逆元
ll extendGcd(ll a, ll b, ll &x, ll &y) {
  if (a == 0 && b == 0) { return -1; } //无最大公约数
  if (b == 0) { x = 1; y = 0; return a; }
  ll d = extendGcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}
//扩展欧几里得求逆元
ll modReverse(ll a, ll m) {
  ll x, y;
  ll d = extendGcd(a, m, x, y);
  if (d == 1) { return (x % m + m) % m; }
  else { return -1; }
}
//只能求0 < a < m的情况,a和m互质
ll inv(ll a, ll m) {
  if (a == 1) { return 1; }
  return inv(m % a, m) * (m - m / a) % m;
}
//费马小定理, m为素数, a与m互质
ll inv(ll a, ll m) {
  return powMod(a, m - 2, m);
}
//预处理卡特兰数
int a[105][105]; //大数
int b[105]; //长度
void Catalan() {
  int i, j, len, carry, temp;
  a[1][0] = b[1] = len = 1;
  for (i = 2; i <= 100; i++) {
    for (j = 0; j < len; j++) { //乘法
      a[i][j] = a[i - 1][j] * (4 * (i - 1) + 2);
    }
    carry = 0;
    for (j = 0; j < len; j++) { //处理相乘结果
      temp = a[i][j] + carry;
      a[i][j] = temp % 10;
      carry = temp / 10;
    }
    while (carry) { //进位处理
      a[i][len++] = carry % 10;
      carry /= 10;
    }
    carry = 0;
    for (j = len - 1; j >= 0; j--) { //除法
      temp = carry * 10 + a[i][j];
      a[i][j] = temp / (i + 1);
      carry = temp % (i + 1);
    }
    while (!a[i][len - 1]) { len--; } //高位零处理
    b[i] = len;
  }
}
//输出大数
void printCatalan(int n) {
  for (int i = b[n] - 1; i >= 0; i--) { printf("%d", a[n][i]); }
}
//组合数
ll Com(ll n, ll m) {
  if (m > n) { return 0; }
  if (n - m > m) { m = n - m; }
  if (m == 0) { return 1; }
  ll ret = 1;
  for (ll i = 0, j = 1; i < m; i++) {
    ret *= n - i;
    for (; j <= m && ret % j == 0; j++) { ret /= j; }
  }
  return ret;
}
//组合数取模 Lucas定理 p <= 10^5 需要预处理阶乘 + 快速幂
ll fac[N] = { 0 };
void getFac(ll p) {
  for (ll i = 1; i <= p; i++) { fac[i] = (fac[i - 1] * i) % p; }
}
ll Lucas(ll n, ll m, ll p) {
  if (m > n) { return 0; }
  if (m > n - m) { m = n - m; }
  if (m == 0) { return 1; }
  ll res = 1;
  while (n && m) {
    ll a = n % p, b = m % p;
    if (a < b) { return 0; }
    res = res * fac[a] * powMod(fac[b] * fac[a - b] % p, p - 2, p) % p;
    n /= p; m /= p;
  }
  return res;
}
//组合数取模 Lucas定理 p <= 10^9 需要快速幂
ll Com(ll n, ll m) {
  if (m > n) { return 0; }
  if (n - m > m) { m = n - m; }
  if (m == 0) { return 1; }
  ll ret = 1;
  for (ll i = 1; i <= m; i++) {
    ll a = (n + i - m) % p, b = i % p;
    ret = ret * (a * powMod(b, p - 2, p) % p) % p;
  }
  return ret;
}
ll Lucas(ll n, ll m, ll p) {
  if (m == 0) { return 1; }
  return C(n % p, m % p) * Lucas(n / p, m / p, p) % p;
}
//中国剩余定理
ll CRT(ll a[], ll m[], int k) {
  ll mm = 1, ans = 0;
  for (int i = 0; i < k; i++) { mm *= m[i]; }
  for (int i = 0; i < k; i++) {
    ll t = mm / m[i];
    ans = (ans + t * inv(t, m[i]) * a[i]) % mm;
  }
  if (ans < 0) { ans += mm; }
  return ans;
}
//求原根
ll n, factor[100];
int cnt, prime[N + 1];
//素数表
void getPrime() {
  for (int i = 2; i <= N; i++) {
    if (!prime[i]) { prime[++prime[0]] = i; }
    for (int j = 1; j <= prime[0] && prime[j] <= N / i; j++) {
      prime[prime[j] * i] = 1;
      if (i % prime[j] == 0) { break; }
    }
  }
}
//快速幂取模
ll powMod(ll a, ll b, ll m) {
  ll r = 1; a %= m;
  while (b) {
    if (b & 1) { r = r * a % m; }
    a = a * a % m;
    b >>= 1;
  }
  return r;
}
//分解质因数
void getFactors(ll x) {
  cnt = 0;
  for (int i = 1; prime[i] <= x / prime[i]; i++) {
    if (x % prime[i] == 0) {
      factor[cnt++] = prime[i];
      while (x % prime[i] == 0) { x /= prime[i]; }
    }
  }
  if (x != 1) { factor[cnt++] = x; }
}
//求原根
int main() {
  getPrime();
  while (~scanf("%I64d", &n)) {
    getFactors(n - 1);
    for (ll g = 2; g < n; g++) {
      bool flag = true;
      for (int i = 0; i < cnt; i++) {
        ll t = (n - 1) / factor[i];
        if (powMod(g, t, n) == 1) { flag = false; break; }
      }
      if (flag) {
        ll root = g;
        printf("%I64d\n", root);
        break; //加上break是求最小的原根
      }
    }
  }
}
//G(1-n)最小公倍数 O(n)
ll lcm(int n) {
  ll ret = 1;
  for (ll i = 1; i <= n; i++) { ret = ret / __gcd(ret, i) * i % M; }
  return ret;
}
//模线性方程组 需扩展欧几里得
int m[10], a[10]; //模数为m, 余数为a, X % m = a
bool solve(int &m0, int &a0, int m, int a) {
  ll y, x;
  int g = extendGcd(m0, m, x, y);
  if (abs(a - a0) % g) { return false; }
  x *= (a - a0) / g;
  x %= m / g;
  a0 = (x * m0 + a0);
  m0 *= m / g;
  a0 %= m0;
  if (a0 < 0) { a0 += m0; }
  return true;
}
//无解返回false, 有解返回true
//解的形式最后为a0 + m0 * t (0 <= a0 < m0)
bool MLES(int &m0 , int &a0, int n) { //解为X = a0 + m0 * k
  bool flag = true;
  m0 = 1; a0 = 0;
  for (int i = 0; i < n; i++) {
    if (!solve(m0, a0, m[i], a[i])) { flag = false; break; }
  }
  return flag;
}
