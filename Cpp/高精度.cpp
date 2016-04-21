//高精度整数
const int BASE = 1000000000;
const int BASEDIGITS = 9;
struct bint {
  vector<int> s; char sign;
  bint(): s(), sign(1) {}
  bint(const ll &v): s(), sign(v < 0 ? -1 : 1) {
    for (ll t = v < 0 ? -v : v; t; t /= BASE) { s.push_back(t % BASE); }
  }
  bint(const string &v): s(), sign(1) {
    int beg = 0;
    for (; beg < (int)v.size() && (v[beg] == '-' || v[beg] == '+'); beg++) {
      if (v[beg] == '-') { sign = -1; }
    }
    for (int i = (int)v.size() - 1, x, j; i >= beg; i -= BASEDIGITS) {
      for (x = 0, j = max(beg, i - BASEDIGITS + 1); j <= i; x = x * 10 + v[j++] - '0');
      s.push_back(x);
    }
    trim();
  }
  bint &operator=(const bint &v) { sign = v.sign; s = v.s; return *this; }
  bint &operator+=(const bint &v) {
    if (sign == v.sign) {
      for (int i = 0, is = 0, len = max(s.size(), v.s.size()); i < len || is; i++) {
        if (i == (int)s.size()) { s.push_back(0); }
        s[i] += is + (i < (int)v.s.size() ? v.s[i] : 0);
        if ((is = s[i] >= BASE)) { s[i] -= BASE; }
      }
      return *this;
    } else { return *this -= -v; }
  }
  bint &operator-=(const bint &v) {
    if (sign == v.sign) {
      if (cmp(v, 0) != -1) {
        for (int i = 0, is = 0; i < (int)v.s.size() || is; i++) {
          s[i] -= is + (i < (int)v.s.size() ? v.s[i] : 0);
          if ((is = s[i] < 0)) { s[i] += BASE; }
        }
        trim(); return *this;
      } else { return *this = -(bint(v) -= *this); }
    } else { return *this += -v; }
  }
  bint &operator*=(const bint &v) {
    vector<ll> num(s.size() + v.s.size());
    for (int i = 0; i < (int)s.size(); i++) {
      for (int j = 0; j < (int)v.s.size(); j++) {
        num[i + j] += (ll)s[i] * v.s[j];
        if (num[i + j] >= BASE) { num[i + j + 1] += num[i + j] / BASE; num[i + j] %= BASE; }
      }
    }
    sign *= v.sign; s.resize(num.size());
    for (int i = 0; i < (int)num.size(); i++) { s[i] = num[i]; }
    trim(); return *this;
  }
  bint &operator/=(const bint &v) { return *this = divmod(*this, v).first; }
  bint &operator%=(const bint &v) { return *this = divmod(*this, v).second; }
  bint operator-()const { bint ret(*this); ret.sign = -sign; return ret; }
  bint operator+(const bint &v)const { return bint(*this) += v; }
  bint operator-(const bint &v)const { return bint(*this) -= v; }
  bint operator*(const bint &v)const { return bint(*this) *= v; }
  bint operator/(const bint &v)const { return divmod(*this, v).first; }
  bint operator%(const bint &v)const { return divmod(*this, v).second; }
  bint operator^(const ll &v)const {
    bint ret(1), t(*this);
    for (ll b = v; b; b >>= 1) { if (b & 1) { ret *= t; } t *= t; }
    return ret;
  }
  //乘除法辅助函数
  friend pair<bint, bint> divmod(const bint &a, const bint &b) {
    int norm = BASE / (b.s.back() + 1);
    bint x = a.abs().mul(norm), y = b.abs().mul(norm), q, r; q.s.resize(x.s.size());
    for (int i = (int)x.s.size() - 1; i >= 0; i--) {
      r = r.mul(BASE); r += x.s[i];
      int s1 = r.s.size() <= y.s.size() ? 0 : r.s[y.s.size()];
      int s2 = r.s.size() + 1 <= y.s.size() ? 0 : r.s[y.s.size() - 1];
      int d = ((ll)BASE * s1 + s2) / y.s.back();
      r -= y.mul(d);
      while (r.cmp(0, 1) == -1) { r += y; --d; }
      q.s[i] = d;
    }
    q.sign = a.sign * b.sign; q.trim(); r.sign = a.sign; r.trim();
    return make_pair(q, r.div(norm));
  }
  bint mul(int v)const {
    bint ret(*this);
    if (v < 0) { ret.sign = -ret.sign; v = -v; }
    for (int i = 0, is = 0; i < (int)ret.s.size() || is; i++) {
      if (i == (int)s.size()) { ret.s.push_back(0); }
      ll a = ret.s[i] * (ll)v + is; is = a / BASE; ret.s[i] = a % BASE;
    }
    ret.trim(); return ret;
  }
  bint div(int v)const {
    bint ret(*this);
    if (v < 0) { ret.sign = -ret.sign; v = -v; }
    for (int i = (int)ret.s.size() - 1, rem = 0; i >= 0; i--) {
      ll a = ret.s[i] + rem * (ll)BASE; ret.s[i] = a / v; rem = a % v;
    }
    ret.trim(); return ret;
  }
  int mod(int v)const {
    if (v < 0) { v = -v; }
    int m = 0;
    for (int i = (int)s.size() - 1; i >= 0; i--) { m = (s[i] + m * (ll)BASE) % v; }
    return m * sign;
  }
  bool operator<(const bint &v)const { return cmp(v) < 0; }
  bool operator>(const bint &v)const { return cmp(v) > 0; }
  bool operator<=(const bint &v)const { return cmp(v) <= 0; }
  bool operator>=(const bint &v)const { return cmp(v) >= 0; }
  bool operator==(const bint &v)const { return cmp(v) == 0; }
  bool operator!=(const bint &v)const { return cmp(v) != 0; }
  int cmp(const bint &v, bool is = 1)const {
    if (is) { if (sign > v.sign) { return 1; } if (sign < v.sign) { return -1; } }
    int d = sign > 0 || !is ? 1 : -1;
    if (s.size() > v.s.size()) { return d; }
    if (s.size() < v.s.size()) { return -d; }
    for (int i = (int)s.size() - 1; i >= 0; i--) {
      if (s[i] > v.s[i]) { return d; } if (s[i] < v.s[i]) { return -d; }
    }
    return 0;
  }
  bint abs()const { bint ret(*this); ret.sign *= ret.sign; return ret; }
  void trim() {
    while (!s.empty() && !s.back()) { s.pop_back(); }
    if (s.empty()) { sign = 1; }
  }
  void print()const {
    if (sign == -1) { putchar('-'); }
    printf("%d", s.empty() ? 0 : s.back());
    for (int i = (int)s.size() - 2; i >= 0; i--) { printf("%09d", s[i]); }
  }
  friend istream &operator>>(istream &in, bint &v) { string s; in >> s; v = s; return in; }
  friend ostream &operator<<(ostream &out, const bint &v) {
    if (v.sign == -1) { out << '-'; }
    out << setfill('0') << (v.s.empty() ? 0 : v.s.back());
    for (int i = (int)v.s.size() - 2; i >= 0; i--) { out << setw(BASEDIGITS) << v.s[i]; }
    return out << setfill(' ');
  }
  string toString()const {
    if (s.empty()) { return "0"; }
    string ret, x;
    if (sign == -1) { ret += '-'; }
    for (int o = s[s.size() - 1]; o; o /= 10) { x += o % 10 + '0'; }
    for (int i = (int)x.size() - 1; i >= 0; i--) { ret += x[i]; }
    for (int i = (int)s.size() - 2; i >= 0; i--) {
      x.clear();
      for (int j = 0, p = s[i]; j < BASEDIGITS; j++, p /= 10) { x += p % 10 + '0'; }
      for (int j = BASEDIGITS - 1; j >= 0; j--) { ret += x[j]; }
    }
    return ret;
  }
  operator bool()const { return s.size() && !(s.size() == 1 && !s[0]); }
};
//高精度开方
const int MAXBIT = 10005;
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
