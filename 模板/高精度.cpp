//完全大数模板
const int MAXN = 9999;
const int MAXSIZE = 1010;
const int DLEN = 4;
class BigNum {
private:
  int a[500], len; //控制大数位数 2000位
public:
  BigNum() : len(1) {memset(a, 0, sizeof(a));} //构造函数
  BigNum(const int); //将int转化成大数
  BigNum(const char *); //将char[]转化为大数
  BigNum(const BigNum &); //拷贝构造函数
  BigNum &operator=(const BigNum &); //大数之间赋值
  friend istream &operator>>(istream &, BigNum &); //重载输入运算符
  friend ostream &operator<<(ostream &, BigNum &); //重载输出运算符
  BigNum operator+(const BigNum &)const; //大数之间的相加
  BigNum operator-(const BigNum &)const; //大数之间的相减
  BigNum operator*(const BigNum &)const; //大数之间的相乘
  BigNum operator/(const int &)const; //大数对int进行相除
  BigNum operator^(const int &)const; //大数的n次方
  int operator%(const int &)const; //大数对int取模
  bool operator>(const BigNum &T)const; //大数之间的大小比较
  bool operator>(const int &t)const; //大数和int的大小比较
  bool operator<(const BigNum &T)const;
  bool operator<(const int &t)const;
  bool operator==(const BigNum &T)const;
  bool operator==(const int &t)const;
  bool operator!=(const BigNum &T)const;
  bool operator!=(const int &t)const;
  void print(); //输出大数
};
BigNum::BigNum(const int b) : len(0) {
  memset(a, 0, sizeof(a));
  int c, d = b;
  while (d > MAXN) {
    c = d - (d / (MAXN + 1)) * (MAXN + 1);
    d = d / (MAXN + 1);
    a[len++] = c;
  }
  a[len++] = d;
}
BigNum::BigNum(const char *s) {
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
BigNum::BigNum(const BigNum &T): len(T.len) {
  memset(a, 0, sizeof(a));
  for (int i = 0; i < len; i++) { a[i] = T.a[i]; }
}
BigNum &BigNum::operator=(const BigNum &n) {
  memset(a, 0, sizeof(a));
  len = n.len;
  for (int i = 0; i < len; i++) { a[i] = n.a[i]; }
  return *this;
}
istream &operator>>(istream &in, BigNum &b) {
  char ch[MAXSIZE * 4];
  in >> ch; b = BigNum(ch);
  return in;
}
ostream &operator<<(ostream &out, BigNum &b) {
  out << setfill('0') << b.a[b.len - 1];
  for (int i = b.len - 2; i >= 0; i--) { out << setw(4) << b.a[i]; }
  return out;
}
BigNum BigNum::operator+(const BigNum &T)const {
  BigNum t(*this);
  int big = T.len > len ? T.len : len;
  for (int i = 0; i < big; i++) {
    t.a[i] += T.a[i];
    if (t.a[i] > MAXN) {
      t.a[i + 1]++;
      t.a[i] -= MAXN + 1;
    }
  }
  if (t.a[big] != 0) { t.len = big + 1; }
  else { t.len = big; }
  return t;
}
BigNum BigNum::operator-(const BigNum &T)const {
  BigNum t1, t2;
  int i, j, big; bool flag;
  if (*this > T) { t1 = *this; t2 = T; flag = false; }
  else { t1 = T; t2 = *this; flag = true; }
  big = t1.len;
  for (i = 0; i < big; i++) {
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
BigNum BigNum::operator*(const BigNum &T)const {
  BigNum ret;
  int i, j, up, temp, temp1;
  for (i = 0; i < len; i++) {
    up = 0;
    for (j = 0; j < T.len; j++) {
      temp = a[i] * T.a[j] + ret.a[i + j] + up;
      if (temp > MAXN) {
        temp1 = temp - temp / (MAXN + 1) * (MAXN + 1);
        up = temp / (MAXN + 1);
        ret.a[i + j] = temp1;
      } else {
        up = 0;
        ret.a[i + j] = temp;
      }
    }
    if (up != 0) { ret.a[i + j] = up; }
  }
  ret.len = i + j;
  while (ret.a[ret.len - 1] == 0 && ret.len > 1) { ret.len--; }
  return ret;
}
BigNum BigNum::operator/(const int &b)const {
  BigNum ret;
  for (int i = len - 1, down = 0; i >= 0; i--) {
    ret.a[i] = (a[i] + down * (MAXN + 1)) / b;
    down = a[i] + down * (MAXN + 1) - ret.a[i] * b;
  }
  ret.len = len;
  while (ret.a[ret.len - 1] == 0 && ret.len > 1) { ret.len--; }
  return ret;
}
int BigNum::operator%(const int &b)const {
  int d = 0;
  for (int i = len - 1; i >= 0; i--) { d = ((d * (MAXN + 1)) % b + a[i]) % b; }
  return d;
}
BigNum BigNum::operator^(const int &n)const {
  if (n == 0) { return 1; }
  if (n == 1) { return *this; }
  BigNum t, ret(1);
  int i, m = n;
  while (m > 1) {
    t = *this;
    for (i = 1; (i << 1) <= m; i <<= 1) { t = t * t; }
    m -= i; ret = ret * t;
    if (m == 1) { ret = ret * (*this); }
  }
  return ret;
}
bool BigNum::operator>(const BigNum &T)const {
  if (len > T.len) { return true; }
  else if (len == T.len) {
    int ln = len - 1;
    while (a[ln] == T.a[ln] && ln >= 0) { ln--; }
    if (ln >= 0 && a[ln] > T.a[ln]) { return true; }
    else { return false; }
  } else { return false; }
}
bool BigNum::operator>(const int &t)const {
  return *this > BigNum(t);
}
bool BigNum::operator<(const BigNum &T)const {
  return T > *this;
}
bool BigNum::operator<(const int &t)const {
  return BigNum(t) > *this;
}
bool BigNum::operator==(const BigNum &T)const {
  if (len != T.len) { return false; }
  int i = len - 1;
  while (a[i] == T.a[i] && i >= 0) { i--; }
  return i == -1;
}
bool BigNum::operator==(const int &t)const {
  return *this == BigNum(t);
}
bool BigNum::operator!=(const BigNum &T)const {
  return !(*this == T);
}
bool BigNum::operator!=(const int &t)const {
  return *this != BigNum(t);
}
void BigNum::print() {
  printf("%d", a[len - 1]);
  for (int i = len - 2; i >= 0; i--) { printf("%04d", a[i]); }
  putchar('\n');
}
