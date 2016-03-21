//分数类
struct Fraction {
  ll a, b; //分子, 分母
  Fraction(const ll &_a = 0, const ll &_b = 1): a(_a), b(_b) {
    ll t = __gcd(a, b); a /= t, b /= t;
    if (b < 0) { a = -a; b = -b; }
  }
  Fraction operator-()const { return Fraction(-a, b); }
  Fraction operator+(const Fraction &r)const { return Fraction(a * r.b + r.a * b, b * r.b); }
  Fraction operator-(const Fraction &r)const { return Fraction(a * r.b - r.a * b, b * r.b); }
  Fraction operator*(const Fraction &r)const { return Fraction(a * r.a, b * r.b); }
  Fraction operator/(const Fraction &r)const { return Fraction(a * r.b, b * r.a); }
  Fraction &operator+=(const Fraction &r) { return *this = *this + r; }
  Fraction &operator-=(const Fraction &r) { return *this = *this - r; }
  Fraction &operator*=(const Fraction &r) { return *this = *this * r; }
  Fraction &operator/=(const Fraction &r) { return *this = *this / r; }
  bool operator<(const Fraction &r)const { return a * r.b < r.a * b; }
  bool operator>(const Fraction &r)const { return a * r.b > r.a * b; }
  bool operator==(const Fraction &r)const { return a * r.b == r.a * b; }
  bool operator<=(const Fraction &r)const { return a * r.b <= r.a * b; }
  bool operator>=(const Fraction &r)const { return a * r.b >= r.a * b; }
  void print() { if (b == 1) { printf("%I64d", a); } else { printf("%I64d//%I64d", a, b); } }
  friend ostream &operator<<(ostream &out, const Fraction &r) {
    if (r.b == 1) { out << r.a; } else { out << r.a << '/' << r.b; } return out;
  }
};
