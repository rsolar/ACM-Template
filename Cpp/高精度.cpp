//大数类ver.1 不支持负数
const int MAXN = 9999; //10 ^ DLEN - 1
const int MAXSIZE = 505;
const int DLEN = 4;
struct BigInt {
  int a[MAXSIZE], len; //MAXSIZE * DLEN位
  BigInt() : len(1) { memset(a, 0, sizeof(a)); } //构造函数
  BigInt(int b): len(0) { //int转化为大数
    memset(a, 0, sizeof(a));
    for (; b > MAXN; b /= MAXN + 1) { a[len++] = b - (b / (MAXN + 1)) * (MAXN + 1); }
    a[len++] = b;
  }
  BigInt(const char *s) { //char[]转化为大数
    memset(a, 0, sizeof(a));
    while (*(s + 1) && *s == '0') { s++; }
    int L = strlen(s); len = L / DLEN + (L % DLEN != 0);
    for (int i = L - 1, index = 0, t, j; i >= 0; a[index++] = t, i -= DLEN) {
      for (t = 0, j = max(i - DLEN + 1, 0); j <= i; j++) { t = t * 10 + s[j] - '0'; }
    }
  }
  BigInt(const BigInt &T): len(T.len) { memcpy(a, T.a, sizeof(a)); } //拷贝构造函数
  BigInt &operator=(const BigInt &T) { len = T.len; memcpy(a, T.a, sizeof(a)); return *this; } //大数赋值大数
  BigInt operator+(const BigInt &T)const { //大数 + 大数
    BigInt t(*this); t.len = max(len, T.len);
    for (int i = 0; i < t.len; i++) {
      t.a[i] += T.a[i];
      if (t.a[i] > MAXN) { t.a[i + 1]++; t.a[i] -= MAXN + 1; }
    }
    t.len += (t.a[t.len] != 0);
    return t;
  }
  BigInt operator-(const BigInt &T)const { //|大数 - 大数|
    BigInt t1, t2; bool flag;
    if (*this > T) { t1 = *this; t2 = T; flag = false; }
    else { t1 = T; t2 = *this; flag = true; }
    for (int i = 0, j; i < t1.len; i++) {
      if (t1.a[i] < t2.a[i]) {
        for (j = i + 1; t1.a[j] == 0; j++); t1.a[j--]--;
        while (j > i) { t1.a[j--] += MAXN; }
        t1.a[i] += MAXN + 1 - t2.a[i];
      } else { t1.a[i] -= t2.a[i]; }
    }
    while (t1.a[len - 1] == 0 && t1.len > 1) { t1.len--; }
    if (flag) { t1.a[t1.len - 1] = -t1.a[t1.len - 1]; }
    return t1;
  }
  BigInt operator*(const BigInt &T)const { //大数 * 大数
    BigInt t; int i, j, up, tmp;
    for (i = 0; i < len; i++) {
      for (up = j = 0; j < T.len; j++) {
        tmp = a[i] * T.a[j] + t.a[i + j] + up;
        if (tmp > MAXN) {
          t.a[i + j] = tmp - tmp / (MAXN + 1) * (MAXN + 1);
          up = tmp / (MAXN + 1);
        } else { t.a[i + j] = tmp; up = 0; }
      }
      if (up != 0) { t.a[i + j] = up; }
    }
    for (t.len = i + j; t.a[t.len - 1] == 0 && t.len > 1; t.len--);
    return t;
  }
  BigInt operator/(const int b)const { //大数 / int
    BigInt t;
    for (int i = len - 1, down = 0; i >= 0; i--) {
      t.a[i] = (a[i] + down * (MAXN + 1)) / b;
      down = a[i] + down * (MAXN + 1) - t.a[i] * b;
    }
    for (t.len = len; t.a[t.len - 1] == 0 && t.len > 1; t.len--);
    return t;
  }
  BigInt operator^(int b)const { //大数快速幂
    if (b == 0) { return 1; }
    if (b == 1) { return *this; }
    BigInt t = *this, ret(1);
    for (; b > 1; b >>= 1) { if (b & 1) { ret = ret * t; } t = t * t; }
    return ret * t;
  }
  int operator%(const int b)const { //大数膜int
    int d = 0;
    for (int i = len - 1; i >= 0; i--) { d = ((d * (MAXN + 1)) % b + a[i]) % b; }
    return d;
  }
  bool operator>(const BigInt &T)const { //大数间大小比较
    if (len > T.len) { return true; }
    else if (len == T.len) {
      int i = len - 1;
      while (a[i] == T.a[i] && i >= 0) { i--; }
      return i >= 0 && a[i] > T.a[i];
    } else { return false; }
  }
  bool operator>=(const BigInt &T)const { return *this > T || *this == T; }
  bool operator<(const BigInt &T)const { return T > *this; }
  bool operator<=(const BigInt &T)const { return T > *this || T == *this; }
  bool operator==(const BigInt &T)const { return len == T.len && equal(a, a + len, T.a); }
  bool operator!=(const BigInt &T)const { return !(*this == T); }
  void print()const { //输出大数 不带换行
    printf("%d", a[len - 1]);
    for (int i = len - 2; i >= 0; i--) { printf("%04d", a[i]); }
  }
  friend istream &operator>>(istream &in, BigInt &b) { //重载输入运算符
    char ch[MAXSIZE * DLEN]; in >> ch; b = BigInt(ch);
    return in;
  }
  friend ostream &operator<<(ostream &out, const BigInt &b) { //重载输出运算符
    out << setfill('0') << b.a[b.len - 1];
    for (int i = b.len - 2; i >= 0; i--) { out << setw(4) << b.a[i]; }
    return out;
  }
};

//大数类ver.2 支持负数
const int MAXBIT = 2005; //位数
class BigInt {
private:
  int bit[MAXBIT];
  bool nega; //负数标志
public:
  BigInt(): nega(false) { memset(bit, 0, sizeof(bit)); }
  BigInt(int n) {
    memset(bit, 0, sizeof(bit));
    if (n >= 0) { nega = false; } else { nega = true; n = -n; }
    for (int pos = 0; n; bit[pos++] = n % 10, n /= 10);
  }
  BigInt(const char *s) {
    memset(bit, 0, sizeof(bit));
    int len = strlen(s), beg = 0; bool valid = true; //符合数字格式
    if (len >= 2) {
      if (s[0] != '+' && s[0] != '-' && !isdigit(s[0])) { valid = false; }
      else { for (int i = 1; i < len; i++) { if (!isdigit(s[i])) { valid = false; break; } } }
    } else if (len == 1) { valid = isdigit(s[0]); }
    if (len == 0 || !valid) { *this = BigInt(); return; }
    if (s[0] == '+') { nega = false; beg++; }
    else if (s[0] == '-') {
      for (int i = 1; i < len; i++) { if (s[i] != '0') { nega = true; break; } } beg++;
    } else { nega = false; }
    for (int i = beg; i < len; i++) { bit[len - 1 - i] = s[i] - '0'; }
  }
  BigInt(const BigInt &n): nega(n.nega) { memcpy(bit, n.bit, sizeof(n.bit)); }
  BigInt &operator=(const BigInt &n) { nega = n.nega; memcpy(bit, n.bit, sizeof(bit)); return *this; }
  BigInt operator+(const BigInt &n)const {
    if (nega ^ !n.nega) { return this->absoluteAdd(n); }
    else if (absoluteEqual(n)) { return BigInt(); }
    else { return absoluteEqualGreater(n) ? this->absoluteMinus(n) : n.absoluteMinus(*this); }
  }
  BigInt operator-(const BigInt &n)const { return *this + n.opposite(); }
  BigInt operator*(const BigInt &n)const {
    if (isZero() || n.isZero()) { return BigInt(); }
    BigInt ret; ret.nega = nega ^ n.nega;
    for (int i = 0; i < MAXBIT; i++) {
      for (int j = 0; j < MAXBIT - i; j++) { ret.bit[i + j] += bit[i] * n.bit[j]; }
    }
    for (int i = 0; i < MAXBIT - 1; i++) { ret.bit[i + 1] += ret.bit[i] / 10; ret.bit[i] %= 10; }
    return ret;
  }
  BigInt operator/(const int &n)const {
    if (isZero() || n == 0) { return BigInt(); } //除以0直接返回0
    BigInt ret; int div = 0; ret.nega = (!nega && n < 0) || (nega && n > 0);
    for (int i = MAXBIT - 1; i >= 0; i--) { div = div * 10 + bit[i]; ret.bit[i] = div / n; div %= n; }
    return ret;
  }
  int operator%(const int &n)const {
    int mod = 0;
    for (int i = MAXBIT - 1; i >= 0; i--) { mod = (mod * 10 + bit[i]) % n; }
    return mod;
  }
  BigInt operator-()const {
    BigInt ret(*this);
    if (!this->isZero()) { ret.nega = !ret.nega; }
    return ret;
  }
  bool operator>(const BigInt &n)const {
    if (!nega && n.nega) { return true; }
    else if (nega && !n.nega) { return false; }
    else if (!nega && !n.nega) { return absoluteGreater(n); }
    else { return n.absoluteGreater(*this); }
  }
  bool operator>=(const BigInt &n)const {
    if (!nega && n.nega) { return true; }
    else if (nega && !n.nega) { return false; }
    else if (!nega && !n.nega) { return absoluteEqualGreater(n); }
    else { return n.absoluteEqualGreater(*this); }
  }
  bool operator<(const BigInt &n)const { return n > *this; }
  bool operator<=(const BigInt &n)const { return n >= *this; }
  bool operator==(const BigInt &n)const { return nega == n.nega && equal(bit, bit + MAXBIT, n.bit); }
  bool operator!=(const BigInt &n)const { return !(*this == n); }
  void print()const { //输出大数 不带换行
    if (nega) { putchar('-'); }
    int i = MAXBIT - 1;
    for (; i > 0 && !bit[i]; i--);
    for (; i >= 0; i--) { putchar(bit[i] + '0'); }
  }
  char *toString()const { //返回数值字符串
    char *content = new char[MAXBIT + 2];
    int pos = 0, i = MAXBIT - 1;
    for (; i > 0 && !bit[i]; i--);
    if (nega) { content[pos++] = '-'; }
    for (; i >= 0; i--) { content[pos++] = bit[i] + '0'; }
    return content;
  }
  bool isZero()const { //是否为0
    for (int i = 0; i < MAXBIT; i++) { if (bit[i] != 0) { return false; } }
    return true;
  }
  bool isPositive()const { return !nega && !isZero(); }
  bool isNegative()const { return nega; }
  bool notNegative()const { return !nega; }
private:
  BigInt opposite()const { //取相反数
    BigInt n(*this);
    if (!n.isZero()) { n.nega = !n.nega; }
    return n;
  }
  BigInt absoluteAdd(const BigInt &n)const { //加上绝对值
    BigInt ret(*this);
    for (int i = 0, next = 0; i < MAXBIT; i++) {
      ret.bit[i] = (bit[i] + n.bit[i] + next) % 10;
      next = (bit[i] + n.bit[i] + next) / 10;
    }
    return ret;
  }
  BigInt absoluteMinus(const BigInt &n)const { //减去绝对值小于自身的数的绝对值
    BigInt ret(*this);
    for (int i = MAXBIT - 1; i >= 0; i--) {
      if (ret.bit[i] >= n.bit[i]) { ret.bit[i] -= n.bit[i]; }
      else { //借位
        int borrow = i + 1;
        while (ret.bit[borrow] == 0) { borrow++; } ret.bit[borrow]--;
        for (int j = i + 1; j < borrow; j++) { ret.bit[j] = 9; }
        ret.bit[i] += 10 - n.bit[i];
      }
    }
    return ret;
  }
  bool absoluteEqual(const BigInt &n)const { return equal(bit, bit + MAXBIT, n.bit); } //绝对值等于
  bool absoluteGreater(const BigInt &n)const { //绝对值大于
    for (int i = MAXBIT - 1; i >= 0; i--) {
      if (bit[i] > n.bit[i]) { return true; }
      else if (bit[i] < n.bit[i]) { return false; }
    }
    return false;
  }
  bool absoluteEqualGreater(const BigInt &n)const { //绝对值大于等于
    for (int i = MAXBIT - 1; i >= 0; i--) {
      if (bit[i] > n.bit[i]) { return true; }
      else if (bit[i] < n.bit[i]) { return false; }
    }
    return true;
  }
};

//高精度开方
bool bigger(char *s1, char *s2) {
  int beg = 0;
  while (s1[beg] == '0') { beg++; } strcpy(s1, s1 + beg);
  if (strlen(s1) == 0) { s1[0] = '0'; s1[1] = 0; }
  beg = 0;
  while (s2[beg] == '0') { beg++; } strcpy(s2, s2 + beg);
  if (strlen(s2) == 0) { s2[0] = '0'; s2[1] = 0; }
  int len1 = strlen(s1), len2 = strlen(s2);
  if (len1 > len2) { return true; }
  else if (len1 < len2) { return false; }
  else {
    for (int i = 0; i < len1; i++) {
      if (s1[i] > s2[i]) { return true; }
      else if (s1[i] < s2[i]) { return false; }
    }
  }
  return false;
}
void mul(const char *s, const int t, char *ret) {
  int left = 0, pos = 0;
  for (int i = strlen(s) - 1, k; i >= 0; i--) {
    k = t * (s[i] - '0') + left; ret[pos++] = k % 10 + '0'; left = k / 10;
  }
  while (left > 0) { ret[pos++] = left % 10 + '0'; left /= 10; }
  ret[pos] = 0;
  for (int i = 0, len = strlen(ret); i < len >> 1; i++) { swap(ret[i], ret[len - i - 1]); }
}
void sub(char *a, const char *b) {
  int left = 0, len1 = strlen(a) - 1, len2 = strlen(b) - 1, beg = 0, tmp;
  while (len2 >= 0) {
    tmp = a[len1] - b[len2] + left;
    if (tmp < 0) { tmp += 10; left = -1; }
    else { left = 0; }
    a[len1] = tmp + '0'; len1--; len2--;
  }
  while (len1 >= 0) {
    tmp = a[len1] - '0' + left;
    if (tmp < 0) { tmp += 10; left = -1; }
    else { left = 0; }
    a[len1] = tmp + '0'; len1--;
  }
  while (a[beg] == '0') { beg++; }
  strcpy(a, a + beg);
  if (strlen(a) == 0) { a[0] = '0'; a[1] = 0; }
}
void sqrt(const char *s, char *ret) {
  char tmp[MAXBIT], left[MAXBIT], p[MAXBIT];
  int i, j, len1 = strlen(s), len2, pos = 0; ret[0] = '0'; ret[1] = 0;
  if (len1 % 2 == 0) { left[0] = s[0]; left[1] = s[1]; left[2] = 0; j = 2; }
  else { left[0] = s[0]; left[1] = 0; j = 1; }
  while (j <= len1) {
    mul(ret, 20, tmp); len2 = strlen(tmp);
    for (i = 9; i >= 0; i--) {
      tmp[len2 - 1] = i + '0'; mul(tmp, i, p);
      if (!bigger(p, left)) { break; }
    }
    ret[pos++] = i + '0'; ret[pos] = 0;
    sub(left, p); len2 = strlen(left);
    left[len2] = s[j]; left[len2 + 1] = s[j + 1]; left[len2 + 2] = 0; j += 2;
  }
}
