//分数类
template<typename T> struct Fraction {
  T a, b; //分子, 分母
  Fraction(const T &_a = 0, const T &_b = 1): a(_a), b(_b) {
    T t = __gcd(a, b); a /= t, b /= t;
    if (b < 0) { a = -a; b = -b; }
  }
  Fraction operator-()const { return Fraction(-a, b); }
  Fraction operator+(const Fraction &r)const { return Fraction(a * r.b + r.a * b, b * r.b); }
  Fraction operator-(const Fraction &r)const { return Fraction(a * r.b - r.a * b, b * r.b); }
  Fraction operator*(const Fraction &r)const { return Fraction(a * r.a, b * r.b); }
  Fraction operator/(const Fraction &r)const { return Fraction(a * r.b, b * r.a); }
  Fraction &operator+=(const Fraction &r) { return *this = Fraction(a * r.b + r.a * b, b * r.b); }
  Fraction &operator-=(const Fraction &r) { return *this = Fraction(a * r.b - r.a * b, b * r.b); }
  Fraction &operator*=(const Fraction &r) { return *this = Fraction(a * r.a, b * r.b); }
  Fraction &operator/=(const Fraction &r) { return *this = Fraction(a * r.b, b * r.a); }
  bool operator<(const Fraction &r)const { return a * r.b < r.a * b; }
  bool operator>(const Fraction &r)const { return a * r.b > r.a * b; }
  bool operator==(const Fraction &r)const { return a * r.b == r.a * b; }
  bool operator<=(const Fraction &r)const { return a * r.b <= r.a * b; }
  bool operator>=(const Fraction &r)const { return a * r.b >= r.a * b; }
  void print() { if (b == 1) { printf("%d", a); } else { printf("%d//%d", a, b); } }
  friend ostream &operator<<(ostream &out, const Fraction &r) {
    if (r.b == 1) { out << r.a; } else { out << r.a << '/' << r.b; } return out;
  }
};
