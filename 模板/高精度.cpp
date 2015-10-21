//大数模板 不支持负数
const int MAXN = 9999; //10 ^ DLEN - 1
const int MAXSIZE = 505;
const int DLEN = 4;
class BigInt {
private:
  int a[MAXSIZE], len; //大数位数为MAXSIZE * DLEN位
public:
  BigInt() : len(1) { memset(a, 0, sizeof(a)); } //构造函数
  BigInt(const int &); //int转化为大数
  BigInt(const char *); //char[]转化为大数
  BigInt(const BigInt &); //拷贝构造函数
  BigInt &operator=(const BigInt &); //大数赋值大数
  friend istream &operator>>(istream &, BigInt &); //重载输入运算符
  friend ostream &operator<<(ostream &, const BigInt &); //重载输出运算符
  BigInt operator+(const BigInt &)const; //大数 + 大数
  BigInt operator-(const BigInt &)const; //大数 - 大数
  BigInt operator*(const BigInt &)const; //大数 * 大数
  BigInt operator/(const int &)const; //大数 / int
  BigInt operator^(const int &)const; //大数的n次幂
  int operator%(const int &)const; //大数膜int
  bool operator>(const BigInt &)const; //大数间大小比较
  bool operator>=(const BigInt &)const;
  bool operator<(const BigInt &)const;
  bool operator<=(const BigInt &)const;
  bool operator==(const BigInt &)const;
  bool operator!=(const BigInt &)const;
  void print()const; //输出大数 不带换行
};
BigInt::BigInt(const int &b) : len(0) {
  memset(a, 0, sizeof(a));
  int c, d = b;
  while (d > MAXN) {
    c = d - (d / (MAXN + 1)) * (MAXN + 1);
    d = d / (MAXN + 1);
    a[len++] = c;
  }
  a[len++] = d;
}
BigInt::BigInt(const char *s) {
  memset(a, 0, sizeof(a));
  int t, k, index = 0, L = strlen(s), p = 0;
  while (s[p] == '0' && p < L - 1) { p++; }
  len = (L - p) / DLEN;
  if ((L - p) % DLEN) { len++; }
  for (int i = L - 1; i >= p; i -= DLEN) {
    t = 0; k = i - DLEN + 1;
    if (k < p) { k = p; }
    for (int j = k; j <= i; j++) { t = t * 10 + s[j] - '0'; }
    a[index++] = t;
  }
}
BigInt::BigInt(const BigInt &T): len(T.len) {
  memset(a, 0, sizeof(a));
  for (int i = 0; i < len; i++) { a[i] = T.a[i]; }
}
BigInt &BigInt::operator=(const BigInt &T) {
  memset(a, 0, sizeof(a)); len = T.len;
  for (int i = 0; i < len; i++) { a[i] = T.a[i]; }
  return *this;
}
istream &operator>>(istream &in, BigInt &b) {
  char ch[MAXSIZE * DLEN];
  in >> ch; b = BigInt(ch);
  return in;
}
ostream &operator<<(ostream &out, const BigInt &b) {
  out << setfill('0') << b.a[b.len - 1];
  for (int i = b.len - 2; i >= 0; i--) { out << setw(4) << b.a[i]; }
  return out;
}
BigInt BigInt::operator+(const BigInt &T)const {
  BigInt t(*this);
  int big = T.len > len ? T.len : len;
  for (int i = 0; i < big; i++) {
    t.a[i] += T.a[i];
    if (t.a[i] > MAXN) { t.a[i + 1]++; t.a[i] -= MAXN + 1; }
  }
  t.len = big + (t.a[big] != 0);
  return t;
}
BigInt BigInt::operator-(const BigInt &T)const {
  BigInt t1, t2;
  int i, j, big; bool flag;
  if (*this > T) { t1 = *this; t2 = T; flag = false; }
  else { t1 = T; t2 = *this; flag = true; }
  for (big = t1.len, i = 0; i < big; i++) {
    if (t1.a[i] < t2.a[i]) {
      j = i + 1;
      while (t1.a[j] == 0) { j++; }
      t1.a[j--]--;
      while (j > i) { t1.a[j--] += MAXN; }
      t1.a[i] += MAXN + 1 - t2.a[i];
    } else { t1.a[i] -= t2.a[i]; }
  }
  t1.len = big;
  while (t1.a[len - 1] == 0 && t1.len > 1) { t1.len--; big--; }
  if (flag) { t1.a[big - 1] = 0 - t1.a[big - 1]; }
  return t1;
}
BigInt BigInt::operator*(const BigInt &T)const {
  BigInt ret;
  int i, j, up, temp, temp1;
  for (i = 0; i < len; i++) {
    for (up = 0, j = 0; j < T.len; j++) {
      temp = a[i] * T.a[j] + ret.a[i + j] + up;
      if (temp > MAXN) {
        temp1 = temp - temp / (MAXN + 1) * (MAXN + 1);
        up = temp / (MAXN + 1); ret.a[i + j] = temp1;
      } else {
        up = 0; ret.a[i + j] = temp;
      }
    }
    if (up != 0) { ret.a[i + j] = up; }
  }
  ret.len = i + j;
  while (ret.a[ret.len - 1] == 0 && ret.len > 1) { ret.len--; }
  return ret;
}
BigInt BigInt::operator/(const int &b)const {
  BigInt ret;
  for (int i = len - 1, down = 0; i >= 0; i--) {
    ret.a[i] = (a[i] + down * (MAXN + 1)) / b;
    down = a[i] + down * (MAXN + 1) - ret.a[i] * b;
  }
  ret.len = len;
  while (ret.a[ret.len - 1] == 0 && ret.len > 1) { ret.len--; }
  return ret;
}
int BigInt::operator%(const int &b)const {
  int d = 0;
  for (int i = len - 1; i >= 0; i--) { d = ((d * (MAXN + 1)) % b + a[i]) % b; }
  return d;
}
BigInt BigInt::operator^(const int &n)const {
  if (n == 0) { return 1; }
  if (n == 1) { return *this; }
  BigInt t, ret(1); int i, m = n;
  while (m > 1) {
    t = *this;
    for (i = 1; (i << 1) <= m; i <<= 1) { t = t * t; }
    m -= i; ret = ret * t;
    if (m == 1) { ret = ret * (*this); }
  }
  return ret;
}
bool BigInt::operator>(const BigInt &T)const {
  if (len > T.len) { return true; }
  else if (len == T.len) {
    int ln = len - 1;
    while (a[ln] == T.a[ln] && ln >= 0) { ln--; }
    if (ln >= 0 && a[ln] > T.a[ln]) { return true; }
    else { return false; }
  } else { return false; }
}
bool operator>=(const BigInt &T)const {
  return *this > T || *this == T;
}
bool BigInt::operator<(const BigInt &T)const {
  return T > *this;
}
bool operator<=(const BigInt &T)const {
  return T > *this || T == *this;
}
bool BigInt::operator==(const BigInt &T)const {
  if (len != T.len) { return false; }
  int i = len - 1;
  while (a[i] == T.a[i] && i >= 0) { i--; }
  return i == -1;
}
bool BigInt::operator!=(const BigInt &T)const {
  return !(*this == T);
}
void BigInt::print()const {
  printf("%d", a[len - 1]);
  for (int i = len - 2; i >= 0; i--) { printf("%04d", a[i]); }
}

//另一大数模板 支持负数
const int MAXBIT = 2005; //位数
class BigInt {
private:
  int bit[MAXBIT];
  bool negative; //负数标志
public:
  BigInt();
  BigInt(const int &);
  BigInt(const char *);
  BigInt(const BigInt &);
  /*重载赋值运算符*/
  BigInt &operator=(const BigInt &);
  /*重载算数运算符*/
  BigInt operator+(const BigInt &)const;
  BigInt operator-(const BigInt &)const;
  BigInt operator*(const BigInt &)const;
  BigInt operator/(const int &)const;
  int operator%(const int &)const;
  BigInt operator-()const;
  /*重载比较运算符*/
  bool operator>(const BigInt &)const;
  bool operator>=(const BigInt &)const;
  bool operator<(const BigInt &)const;
  bool operator<=(const BigInt &)const;
  bool operator==(const BigInt &)const;
  bool operator!=(const BigInt &)const;
  /*基本操作*/
  void print()const; //输出数值
  char *toString()const; //返回数值字符串
  bool isZero()const; //是否为0
  bool isPositive()const; //是否为正数
  bool isNegative()const; //是否为负数
  bool nonNegative()const; //是否为非负数
private:
  BigInt opposite()const;//取相反数
  BigInt absoluteAdd(const BigInt &)const; //加上绝对值
  BigInt absoluteMinus(const BigInt &)const; //减去绝对值小于自身的数的绝对值
  bool absoluteEqual(const BigInt &)const; //绝对值等于
  bool absoluteGreater(const BigInt &)const; //绝对值大于
  bool absoluteEqualGreater(const BigInt &)const; //绝对值大于等于
};
BigInt::BigInt(): negative(false) {
  memset(bit, 0, sizeof(bit));
}
BigInt::BigInt(const int &n) {
  memset(bit, 0, sizeof(bit));
  int nn = n, pos = 0;
  if (nn >= 0) { negative = false; }
  else { negative = true; nn = -nn; }
  while (nn) { bit[pos++] = nn % 10; nn /= 10; }
}
BigInt::BigInt(const char *s) {
  int len = strlen(s), beg = 0, end = len - 1; bool valid = true; //符合数字格式
  if (len >= 2) {
    if (s[0] != '+' && s[0] != '-' && !isdigit(s[0])) { valid = false; }
    for (int i = 1; i < len; i++) { if (!isdigit(s[i])) { valid = false; } }
  } else if (len == 1) { if (!isdigit(s[0])) { valid = false; } }
  if (len == 0 || !valid) { memset(bit, 0, sizeof(bit)); negative = false; return; }
  if (s[0] == '+') { negative = false; ++beg; }
  else if (s[0] == '-') {
    bool zeroFlag = true;
    for (int i = 1; i < len; i++) { if (s[i] != '0') { zeroFlag = false; break; } }
    if (zeroFlag) { negative = false; }
    else { negative = true; }
    beg++;
  } else { negative = false; }
  memset(bit, 0, sizeof(bit));
  for (int i = beg; i <= end; i++) { bit[len - 1 - i] = s[i] - '0'; }
}
BigInt::BigInt(const BigInt &n): negative(n.negative) {
  memcpy(bit, n.bit, sizeof(bit));
}
BigInt &BigInt::operator=(const BigInt &n) {
  memcpy(bit, n.bit, sizeof(bit)); negative = n.negative;
  return *this;
}
BigInt BigInt::operator+(const BigInt &n)const {
  if ((!negative && !n.negative) || (negative && n.negative)) {
    return this->absoluteAdd(n);
  } else {
    if (absoluteEqual(n)) { return BigInt(); }
    else if (absoluteEqualGreater(n)) { return this->absoluteMinus(n); }
    else { return n.absoluteMinus(*this); }
  }
}
BigInt BigInt::operator-(const BigInt &n)const {
  return *this + n.opposite();
}
BigInt BigInt::operator*(const BigInt &n)const {
  if (isZero() || n.isZero()) { return BigInt(); }
  BigInt bi = BigInt();
  if ((!negative && !n.negative) || (negative && n.negative)) { bi.negative = false; }
  else { bi.negative = true; }
  for (int i = 0; i < MAXBIT; ++i) {
    for (int j = 0; j < MAXBIT - i; ++j) {
      bi.bit[i + j] += bit[i] * n.bit[j];
    }
  }
  for (int i = 0; i < MAXBIT - 1; ++i) { //进位
    bi.bit[i + 1] += bi.bit[i] / 10; bi.bit[i] %= 10;
  }
  return bi;
}
BigInt BigInt::operator/(const int &n)const {
  if (isZero() || n == 0) { return BigInt(); } //除以0直接返回0
  BigInt bi = BigInt(); int div = 0; //累计除数
  if ((!negative && n > 0) || (negative && n < 0)) { bi.negative = false; }
  else { bi.negative = true; }
  for (int i = MAXBIT - 1; i >= 0; --i) {
    div = div * 10 + bit[i]; bi.bit[i] = div / n; div %= n;
  }
  return bi;
}
int BigInt::operator%(const int &n)const {
  int mod = 0; //累计余数
  for (int i = MAXBIT - 1; i >= 0; --i) {
    //mod = ((mod * (MAXBIT + 1/*??*/)) + bit[i]) % n;
    mod = ((mod * 10) + bit[i]) % n;
  }
  return mod;
}
BigInt BigInt::operator-()const {
  BigInt bi(*this);
  if (!this->isZero()) { bi.negative = !bi.negative; }
  return bi;
}
bool BigInt::operator>(const BigInt &n)const {
  if (!negative && n.negative) { return true; }
  else if (negative && !n.negative) { return false; }
  else if (!negative && !n.negative) { return absoluteGreater(n); }
  else { return n.absoluteGreater(*this); }
}
bool BigInt::operator>=(const BigInt &n)const {
  if (!negative && n.negative) { return true; }
  else if (negative && !n.negative) { return false; }
  else if (!negative && !n.negative) { return absoluteEqualGreater(n); }
  else { return n.absoluteEqualGreater(*this); }
}
bool BigInt::operator<(const BigInt &n)const {
  return n > *this;
}
bool BigInt::operator<=(const BigInt &n)const {
  return n >= *this;
}
bool BigInt::operator==(const BigInt &n)const {
  if (negative != n.negative) { return false; }
  for (int i = 0; i < MAXBIT; ++i) {
    if (bit[i] != n.bit[i]) { return false; }
  }
  return true;
}
bool BigInt::operator!=(const BigInt &n)const {
  if (negative != n.negative) { return true; }
  for (int i = 0; i < MAXBIT; ++i) {
    if (bit[i] != n.bit[i]) { return true; }
  }
  return false;
}
void BigInt::print()const {
  if (negative) { printf("-"); }
  int pos = MAXBIT - 1;
  for (; pos > 0; --pos) { if (bit[pos]) { break; } }
  for (int i = pos; i >= 0; --i) { printf("%d", bit[i]); }
}
char *BigInt::toString()const {
  char *content = new char[MAXBIT + 2];
  int posi = 0, pos = MAXBIT - 1;
  if (negative) { content[posi++] = '-'; }
  for (; pos > 0; --pos) { if (bit[pos]) { break; } }
  //printf("pos = %d\n", pos);
  for (int i = pos; i >= 0; --i) {
    content[posi++] = bit[i] + '0';
    //printf("bit[%d] = %d\n", i, bit[i]);
  }
  content[posi] = '\0';
  return content;
}
bool BigInt::isZero()const {
  bool zeroFlag = true;
  for (int i = 0; i < MAXBIT; ++i) {
    if (bit[i] != 0) { zeroFlag = false; break; }
  }
  return zeroFlag;
}
bool BigInt::isPositive()const {
  return !negative && !isZero();
}
bool BigInt::isNegative()const {
  return negative;
}
bool BigInt::nonNegative()const {
  return !negative;
}
BigInt BigInt::opposite()const {
  BigInt n(*this);
  if (!n.isZero()) { n.negative = !n.negative; }
  return n;
}
BigInt BigInt::absoluteAdd(const BigInt &n)const {
  BigInt bi(*this);
  int next = 0; //进位
  for (int i = 0; i < MAXBIT; ++i) {
    bi.bit[i] = (bit[i] + n.bit[i] + next) % 10;
    next = (bit[i] + n.bit[i] + next) / 10;
  }
  return bi;
}
BigInt BigInt::absoluteMinus(const BigInt &n)const {
  BigInt bi(*this);
  for (int i = MAXBIT - 1; i >= 0; --i) {
    if (bi.bit[i] >= n.bit[i]) { bi.bit[i] -= n.bit[i]; }
    else { //借位
      int borrow = i + 1; //借位位
      while (bi.bit[borrow] == 0) { ++borrow; }
      --bi.bit[borrow];
      for (int j = i + 1; j < borrow; ++j) { bi.bit[j] = 9; }
      bi.bit[i] = bi.bit[i] + 10 - n.bit[i];
    }
  }
  return bi;
}
bool BigInt::absoluteEqual(const BigInt &n)const {
  for (int i = 0; i < MAXBIT; ++i) {
    if (bit[i] != n.bit[i]) { return false; }
  }
  return true;
}
bool BigInt::absoluteGreater(const BigInt &n)const {
  for (int i = MAXBIT - 1; i >= 0; --i) {
    if (bit[i] > n.bit[i]) { return true; }
    else if (bit[i] < n.bit[i]) { return false; }
  }
  return false;
}
bool BigInt::absoluteEqualGreater(const BigInt &n)const {
  for (int i = MAXBIT - 1; i >= 0; --i) {
    if (bit[i] > n.bit[i]) { return true; }
    else if (bit[i] < n.bit[i]) { return false; }
  }
  return true;
}
