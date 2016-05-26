﻿//快速幂
ll powMod(ll a, ll b, ll m) {
  ll r = 1;
  for (a %= m; b; b >>= 1) { if (b & 1) { r = r * a % m; } a = a * a % m; }
  return r;
}
//素数筛
//Eratosthenes O(nloglogn)
const int N = 10000000; //~80ms
bitset < N + 5 > isprime;
void getPrime() {
  isprime.set(); isprime[0] = isprime[1] = false;
  for (int i = 2; i <= N; i++) {
    if (isprime[i]) {
      for (ll j = (ll)i * i; j <= N; j += i) { isprime[j] = false; }
    }
  }
}
//Euler O(n) prime[0]为个数
const int N = 10000000; //~65ms
int prime[N + 5]; //3711111 for [2, 10^9)
void getPrime() {
  for (int i = 2; i <= N; i++) {
    if (!prime[i]) { prime[++prime[0]] = i; }
    for (int j = 1; j <= prime[0] && prime[j] * i <= N; j++) {
      prime[prime[j] * i] = 1;
      if (i % prime[j] == 0) { break; }
    }
  }
}
//Euler O(n)
const int N = 10000000; //~95ms
bitset < N + 5 > isprime;
int prime[N >> 3];
void getPrime() {
  isprime.set(); isprime[0] = isprime[1] = false;
  for (int i = 2; i <= N; i++) {
    if (isprime[i]) { prime[++prime[0]] = i; }
    for (int j = 1; j <= prime[0] && prime[j] * i <= N; j++) {
      isprime[prime[j] * i] = false;
      if (i % prime[j] == 0) { break; }
    }
  }
}
//分解质因数
ll factor[100], facCnt;
void getFactors(ll x) {
  facCnt = 0;
  for (int i = 2, xx = sqrt(x + 0.5); i <= xx; i++) {
    if (x % i == 0) {
      factor[facCnt++] = i;
      while (x % i == 0) { x /= i; }
    }
  }
  if (x != 1) { factor[facCnt++] = x; }
}
//分解质因数及个数 预处理素数表
ll factor[100][2], facCnt;
void getFactors(ll x) {
  facCnt = 0;
  for (int i = 1; prime[i] <= x / prime[i]; i++) {
    factor[facCnt][1] = 0;
    if (x % prime[i] == 0) {
      factor[facCnt][0] = prime[i];
      while (x % prime[i] == 0) { factor[facCnt][1]++; x /= prime[i]; }
      facCnt++;
    }
  }
  if (x != 1) { factor[facCnt][0] = x; factor[facCnt++][1] = 1; }
}
//Miller-Rabin素性测试 素数返回true 错误(伪素数)概率为1/4^Times
const int Times = 7;
int WIT[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}; //7 bases for n < 2^64
ll mulMod(ll a, ll b, ll m) {
  ll r = 0;
  for (a %= m, b %= m; b; b >>= 1) { if (b & 1) { r = (r + a) % m; } a = (a << 1) % m; }
  return r;
}
ll powMod(ll a, ll b, ll m) {
  ll r = 1;
  for (a %= m; b; b >>= 1) { if (b & 1) { r = mulMod(r, a, m); } a = mulMod(a, a, m); }
  return r;
}
bool Miller_Rabin(ll n) {
  if (n == 2) { return true; }
  if (n < 2 || (n & 1) == 0) { return false; }
  ll m = n - 1; int k = 0;
  while ((m & 1) == 0) { k++; m >>= 1; }
  for (int i = 0; i < Times; i++) {
    ll a = WIT[i], x = powMod(a, m, n), y = 0;
    //ll a = rand() % (n - 1) + 1;
    for (int j = 0; j < k; j++, x = y) {
      y = mulMod(x, x, n);
      if (y == 1 && x != 1 && x != n - 1) { return false; }
    }
    if (y != 1) { return false; }
  }
  return true;
}
//pollard rho质因素分解
//对n进行素因子分解, 存入factor, k设置为107左右即可
ll factor[100], facCnt; //质因素分解结果(无序)
ll pollard_rho(ll x, ll c) {
  ll i = 1, k = 2, x0 = rand() % (x - 1) + 1, y = x0;
  while (true) {
    x0 = (mulMod(x0, x0, x) + c) % x;
    ll d = llabs(__gcd(y - x0, x));
    if (d != 1 && d != x) { return d; }
    if (y == x0) { return x; }
    if (++i == k) {y = x0; k += k;}
  }
}
void findfac(ll n, int k = 107) {
  if (n == 1) { return; }
  if (Miller_Rabin(n)) { factor[facCnt++] = n; return; }
  ll p = n; int c = k;
  while (p >= n) { p = pollard_rho(p, c--); } //k值变化, 防止死循环
  findfac(p, k); findfac(n / p, k);
}
//求单个数的欧拉函数 + 合数分解
int getFacEul(ll n, ll factor[]) {
  for (int i = 0, facCnt = getFactors(n); i < facCnt; i++) {
    n = n / factor[i] * (factor[i] - 1);
  }
  return n;
}
//求单个数的欧拉函数
ll eular(ll n) {
  ll ans = n;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) { ans -= ans / i; while (n % i == 0) { n /= i; } }
  }
  return n > 1 ? ans - ans / n : ans;
}
//欧拉函数筛 O(nloglogn)
const int N = 10000000; //~320ms
int phi[N + 5] = { 0, 1 };
void getPhi() {
  for (int i = 2; i <= N; i++) {
    if (!phi[i]) {
      for (int j = i; j <= N; j += i) {
        if (!phi[j]) { phi[j] = j; } phi[j] -= phi[j] / i;
      }
    }
  }
}
//素数 + 欧拉函数筛 O(n)
const int N = 10000000; //~95ms
bitset < N + 5 > isprime;
int prime[N], phi[N + 5] = { 0, 1 };
void getPrimePhi() {
  isprime.set(); isprime[0] = isprime[1] = false;
  for (int i = 2; i < N; i++) {
    if (isprime[i]) { prime[++prime[0]] = i; phi[i] = i - 1; }
    for (int j = 1; j <= prime[0] && prime[j] * i <= N; j++) {
      isprime[prime[j] * i] = false;
      if (i % prime[j] == 0) { phi[prime[j] * i] = phi[i] * prime[j]; break; }
      else { phi[prime[j] * i] = phi[i] * (prime[j] - 1); }
    }
  }
}
//约数个数筛 O(n)
const int N = 10000000; //~125ms
bitset < N + 5 > isprime;
int prime[N], faccnt[N + 5] = { 0, 1 }, d[N + 5]; //d[i]表示i的最小质因子的幂次
void getFaccnt() {
  isprime.set(); isprime[0] = isprime[1] = false;
  for (int i = 2; i <= N; i++) {
    if (isprime[i]) { prime[++prime[0]] = i; faccnt[i] = 2; d[i] = 1; }
    for (int j = 1; j <= prime[0] && prime[j] * i <= N; j++) {
      isprime[prime[j] * i] = false;
      if (i % prime[j] == 0) {
        faccnt[prime[j] * i] = faccnt[i] / (d[i] + 1) * (d[i] + 2);
        d[prime[j] * i] = d[i] + 1; break;
      }
      faccnt[prime[j] * i] = faccnt[i] << 1; d[prime[j] * i] = 1;
    }
  }
}
//A^B的约数之和为:
//sum = [1+p1+p1^2+...+p1^(a1*B)]*...*[1+pn+pn^2+...+pn^(an*B)].
//等比数列求和 1+a+a^2+...+a^b
ll sumPow(ll a, ll b, ll m) {
  ll r = 1; a %= m;
  for (ll t = 1; b; b >>= 1) {
    if (b & 1) { r = (r * a + t) % m; }
    t = t * (a + 1) % m;
    a = a * a % m;
  }
  return r;
}
//求逆元(ax = 1(mod m)的x值)
//扩展欧几里得(求ax + by = gcd(a, b)的解), 求出的x为a对b的模逆元
ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) { x = 1; y = 0; return a; }
  ll d = exgcd(b, a % b, y, x); return y -= a / b * x, d;
}
//解不定方程ax + by = c 求得的只是其中一组解
//对于不定整数方程ax + by = c, 若c mod gcd(a, b) = 0, 则该方程存在整数解, 否则不存在整数解
//在找到ax + by = gcd(a, b)的一组解x0, y0后，可得到ax + by = c的一组解x1 = x0 * (c / gcd(a, b)), y1 = y0 * (c / gcd(a,b))
//ax + by = c的其他整数解满足：
//x = x1 + b / gcd(a, b) * t, y = y1 - a / gcd(a, b) * t(其中t为任意整数)
bool linear_equation(int a, int b, int c, int &x, int &y) {
  int d = exgcd(a, b, x, y);
  if (c % d != 0) { return false; }
  int k = c / d; x *= k; y *= k; return true;
}
//扩展欧几里得求逆元
ll modReverse(ll a, ll m) {
  ll x, y, d = exgcd(a, m, x, y);
  if (d == 1) { return (x % m + m) % m; } else { return -1; }
}
//只能求0 < a < m的情况,a和m互质
ll inv(ll a, ll m) {
  if (a == 1) { return 1; }
  return inv(m % a, m) * (m - m / a) % m;
}
//费马小定理, m为素数, a与m互质
ll inv(ll a, ll m) { return powMod(a, m - 2, m); }
//线性求逆元
void getInv(int m) {
  for (ll i = 2; i < m; i++) { inv[i] = (m - m / i) * inv[m % i] % m; }
}
//组合数预处理 / 杨辉三角
//C[i][i] = C[i][0] = 1
//C[i][j] = C[i - 1][j] + C[i - 1][j - 1], 0 < j < i
const int maxc = 105;
ll C[maxc][maxc];
void calC() {
  for (int i = 0; i < maxc; i++) { C[i][i] = C[i][0] = 1; }
  for (int i = 2; i < maxc; i++) {
    for (int j = 1; j < i; j++) { C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % M; }
  }
}
//求组合数C(n, m) 不取模
ll Com(ll n, ll m) {
  if (m > n) { return 0; }
  if (m > n - m) { m = n - m; }
  ll ret = 1;
  for (ll i = 0, j = 1; i < m; i++) {
    for (ret *= n - i; j <= m && ret % j == 0; j++) { ret /= j; }
  }
  return ret;
}
//求组合数取模
//p <= 10^5 预处理阶乘逆元
ll fac[M] = {1, 1}, invfac[M] = {1, 1};
void initFac(ll p) {
  for (int i = 2; i < p; i++) {
    fac[i] = fac[i - 1] * i % p; invfac[i] = (-invfac[p % i] * (p / i) % p + p) % p;
  }
  for (int i = 2; i < p; i++) { invfac[i] = invfac[i] * invfac[i - 1] % p; }
}
ll Com(ll n, ll m, ll p) {
  return n < m ? 0 : fac[n] * invfac[n - m] % p * invfac[m] % p;
}
//p <= 10^9 在线求逆元
ll Com(ll n, ll m, ll p) {
  if (m > n) { return 0; }
  if (m > n - m) { m = n - m; }
  ll ret = 1;
  for (ll i = 1; i <= m; i++) {
    ll a = (n + i - m) % p, b = i % p;
    ret = ret * a % p * powMod(b, p - 2, p) % p;
  }
  return ret;
}
//Lucas定理
ll Lucas(ll n, ll m, ll p) {
  if (n < m) { return 0; }
  if (m == 0 && n == 0) { return 1; }
  return Com(n % p, m % p, p) * Lucas(n / p, m / p, p) % p;
}
//第一类Stirling数 s(p, k)
//将p个物体排成k个非空循环排列的方法数
//s(p, k)的递推公式：s(p, k) = (p - 1) * s(p - 1, k) + s(p - 1, k - 1), 1 <= k <= p - 1
//边界条件：s(p, 0) = 0, p >= 1, s(p, p) = 1, p >= 0
const int maxs = 105;
ll S[maxs][maxs];
void calStir1() {
  S[0][0] = S[1][1] = 1;
  for (int i = 2; i < maxs; i++) {
    for (int j = 1; j <= i; j++) { S[i][j] = ((i - 1) * S[i - 1][j] + S[i - 1][j - 1]) % M; }
  }
}
//第二类Stirling数 S(p, k)
//将p个物体划分成k个非空的不可辨别的(可以理解为盒子没有编号)集合的方法数
//k! * S(p, k)是把p个人分进k间有差别(如被标有房号)的房间(无空房)的方法数
//S(p, k)的递推公式是：S(p, k) = k * S(p - 1, k) + S(p - 1, k - 1), 1 <= k <= p - 1
//边界条件：S(p, 0) = 0, p >= 1, S(p, p) = 1, p >= 0
const int maxs = 105;
ll S[maxs][maxs];
void calStir2() {
  S[0][0] = S[1][1] = 1;
  for (int i = 2; i < maxs; i++) {
    for (int j = 1; j <= i; j++) { S[i][j] = (j * S[i - 1][j] + S[i - 1][j - 1]) % M; }
  }
}
//Bell数
//B(n)表示基数为n的集合的划分方法的数目
//B(0) = 1, B(n + 1) = sum(C(n, k) * B(k)), 0 <= k <= n
//每个贝尔数都是第二类Stirling数的和, 即B(n) = sum(S(n, k)), 1 <= k <= n
//Bell三角形
//a[0][0] = 1
//对于n >= 1, a[n][0] = a[n - 1][n - 1]
//对于m, n >= 1, a[n][m] = a[n][m - 1] + a[n - 1][m - 1]
//每行首项是贝尔数，每行之和是第二类Stirling数
//两个重要的同余性质:
//B(p + n) = B(n) + B(n + 1) (mod p)
//B(p^m + n) = m * B(n) + B(n + 1) (mod p)
//p是不大于100的素数, 这样, 我们可以通过上面的性质来计算Bell数模小于100的素数值
//Bell数模素数p的周期为: N(p) = (p^p - 1) / (p - 1)
const int maxb = 105;
ll T[maxb], B[maxb];
void calBell() {
  B[0] = B[1] = T[0] = 1;
  for (int i = 2; i < maxb; i++) {
    T[i - 1] = B[i - 1];
    for (int j = i - 2; j >= 0; j--) { T[j] = (T[j] + T[j + 1]) % M; }
    B[i] = T[0];
  }
}
//中国剩余定理 求模线性方程组x=a[i](mod m[i]) m[i]可以不互质
bool merge(ll a1, ll m1, ll a2, ll m2, ll &a3, ll &m3) {
  ll d = __gcd(m1, m2), c = a2 - a1;
  if (c % d != 0) { return false; }
  c = (c % m2 + m2) % m2 / d; m1 /= d; m2 /= d;
  c = c * inv(m1, m2) % m2 * m1 * d + a1;
  m3 = m1 * m2 * d; a3 = (c % m3 + m3) % m3;
  return true;
}
ll CRT(ll a[], ll m[], int k) {
  ll a1 = a[0], m1 = m[0];
  for (int i = 1; i < k; i++) {
    ll a2 = a[i], m2 = m[i], m3, a3;
    if (!merge(a1, m1, a2, m2, a3, m3)) { return -1; }
    a1 = a3; m1 = m3;
  }
  return (a1 % m1 + m1) % m1;
}
//模线性方程组 需扩展欧几里得
//求解方程ax ≡ b (mod m) 相当于求解方程ax + my = b (x, y为整数)
int m[10], a[10]; //模数为m, 余数为a, X % m = a
bool solve(int &m0, int &a0, int m, int a) {
  ll y, x;
  int g = exgcd(m0, m, x, y);
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
bool MLES(int &m0, int &a0, int n) {  //解为X = a0 + m0 * k
  bool flag = true;
  m0 = 1; a0 = 0;
  for (int i = 0; i < n; i++) {
    if (!solve(m0, a0, m[i], a[i])) { flag = false; break; }
  }
  return flag;
}
//预处理卡特兰数
int a[105][105], b[105]; //大数, 长度
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
//求原根
ll n, factor[100];
int cnt, prime[N + 5];
//素数表
void getPrime() {
  for (int i = 2; i <= N; i++) {
    if (!prime[i]) { prime[++prime[0]] = i; }
    for (int j = 1; j <= prime[0] && prime[j] * i <= N; j++) {
      prime[prime[j] * i] = 1;
      if (i % prime[j] == 0) { break; }
    }
  }
}
//快速幂取模
ll powMod(ll a, ll b, ll m) {
  ll r = 1;
  for (a %= m; b; b >>= 1) { if (b & 1) { r = r * a % m; } a = a * a % m; }
  return r;
}
//分解质因数
void getFactors(ll x) {
  cnt = 0;
  for (int i = 1; (ll)prime[i] * prime[i] <= x; i++) {
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
//莫比乌斯函数筛 O(n)
const int N = 10000000; //95ms
bitset < N + 5 > isprime;
int prime[N], miu[N + 5] = { 0, 1 };
void getMiu() {
  isprime.set(); isprime[0] = isprime[1] = false;
  for (int i = 2; i <= N; i++) {
    if (isprime[i]) { prime[++prime[0]] = i; miu[i] = -1; }
    for (int j = 1; j <= prime[0] && prime[j] * i <= N; j++) {
      isprime[prime[j] * i] = false;
      if (i % prime[j] == 0) { miu[prime[j] * i] = 0; break; }
      miu[prime[j] * i] = -miu[i];
    }
  }
}
//离散对数 大步小步算法 Baby-Step Giant-Step
//a^x = b (mod n) n是素数和不是素数都可以 求解上式最小非负整数解或通解(p是质数)
#define MOD 76543
int hs[MOD], head[MOD], next[MOD], id[MOD], top;
void ins(int x, int y) {
  int k = x % MOD;
  hs[top] = x, id[top] = y, next[top] = head[k], head[k] = top++;
}
int fnd(int x) {
  int k = x % MOD;
  for (int i = head[k]; i != -1; i = next[i])
    if (hs[i] == x) {
      return id[i];
    }
  return -1;
}
int BSGS(int a, int b, int n) {
  memset(head, -1, sizeof(head));
  top = 1;
  if (b == 1) { return 0; }
  int m = sqrt(n * 1.0), j;
  ll x = 1, p = 1;
  for (int i = 0; i < m; ++i, p = p * a % n) { ins(p * b % n, i); }
  for (ll i = m; ; i += m) {
    if ((j = fnd(x = x * p % n)) != -1) { return i - j; }
    if (i > n) { break; }
  }
  return -1;
}
//ver.STL map
//BSGS(a, b, p): 求ax≡b(modp)的最小非负整数解, 若无解则返回 -1
//rev(a, p): 扩展欧几里得求逆元
//fastPow(base, pow, mod): 快速幂
//fastMul(a, b, mod): 快速乘(这里用快速乘是为了避免爆long long int, 实际有时可以不用)
map<ll, ll> Hash; //BSGS的hash表
ll BSGS(ll a, ll b, ll p) { //a^x=b(mod p), 已知a,b,p,求x
  a %= p, b %= p; //注意开始的特判是非常重要的
  if (!a && !b) { return 1; } //a和b都是p的倍数的话, 就相当于0^x=0(mod p)了, 那么最小非负整数解就是1
  if (!a) { return -1; } //如果a是p的倍数但是b不是, 就相当于0^x=t(mod p),t>0, 无解
  Hash.clear(); //记得一开始要把map清零
  ll m = ceil(sqrt(p)); //注意这里的sqrt(p)要向上取整, 不然就不能枚举到0~p-1里的每个幂了
  ll tmp = 1 % p; //tmp=a^j
  for (ll j = 0; j < m; j++) { //预处理出a^j mod p的值
    Hash[tmp] = j; tmp = fastMul(tmp, a, p);
  }
  tmp = rev(fastPow(a, m, p), p); //tmp=a^(-m)
  for (ll i = 0; i < m; i++) {
    if (Hash.count(b)) { return i * m + Hash[b]; }
    b = fastMul(b, tmp, p);
  }
  return -1;
}
//自适应simpson积分
double simpson(double a, double b) {
  double c = a + (b - a) / 2;
  return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}
double asr(double a, double b, double eps, double A) {
  double c = a + (b - a) / 2;
  double L = simpson(a, c), R = simpson(c, b);
  if (fabs(L + R - A) <= 15 * eps) { return L + R + (L + R - A) / 15.0; }
  return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}
double asr(double a, double b, double eps) {
  return asr(a, b, eps, simpson(a, b));
}
//高斯消元 (浮点数)
const double eps = 1e-9;
const int N = 205;
double a[N][N], x[N]; //方程的左边的矩阵和等式右边的值, 求解之后x存的就是结果
int equ, var; //方程数和未知数个数
//返回0表示无解, 1表示有解
int Gauss() {
  int i, j, k, col, max_r;
  for (k = 0, col = 0; k < equ && col < var; k++, col++) {
    max_r = k;
    for (i = k + 1; i < equ; i++) {
      if (fabs(a[i][col]) > fabs(a[max_r][col])) { max_r = i; }
    }
    if (fabs(a[max_r][col]) < eps) { return 0; }
    if (k != max_r) {
      for (j = col; j < var; j++) { swap(a[k][j], a[max_r][j]); }
      swap(x[k], x[max_r]);
    }
    x[k] /= a[k][col];
    for (j = col + 1; j < var; j++) { a[k][j] /= a[k][col]; }
    a[k][col] = 1;
    for (i = 0; i < equ; i++) {
      if (i != k) {
        x[i] -= x[k] * a[i][k];
        for (j = col + 1; j < var; j++) { a[i][j] -= a[k][j] * a[i][col]; }
        a[i][col] = 0;
      }
    }
  }
  return 1;
}
//FFT


