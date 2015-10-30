//Joseph 问题
int Joseph(int n, int m) {
  int ret = 0;
  for (int i = 2; i <= n; i++) {
    ret = (ret + m) % i;
  }
  return ret + 1;
}
//统计0到n之间1的个数
int CountOne(int n) {
  int i = 1, ret = 0, before, current, after;
  while (n / i) {
    before = n / (i * 10); current = n / i % 10; after = n - n / i * i;
    if (current > 1) { ret += (before + 1) * i; }
    else if (current == 0) { ret += before * i; }
    else { ret += before * i + after + 1; }
    i *= 10;
  }
  return ret;
}
//A023052 Powerful numbers(3): numbers n that are the sum of some fixed power of their digits.
int Narcissistic[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407, 1634, 4150, 4151, 8208, 9474, 54748, 92727, 93084,
                       194979, 548834, 1741725, 4210818, 9800817, 9926315, 14459929, 24678050, 24678051, 88593477
                     };
//小数转化为分数
//把小数转化为分数, 循环部分用()表示
void Work(char str[]) {
  int len = strlen(str), cnt1 = 0, cnt2 = 0;
  ll a = 0, b = 0;
  bool flag = false;
  for (int i = 2; i < len; i++) {
    if (str[i] == '(') { break; }
    a = a * 10 + str[i] - '0'; cnt1++;
  }
  for (int i = 2; i < len; i++) {
    if (str[i] == '(' || str[i] == ')') { flag = true; continue; }
    b = b * 10 + str[i] - '0'; cnt2++;
  }
  cnt2 -= cnt1;
  ll p = b - a, q = 0;
  if (!flag) { p = b; q = 1; cnt2 = 0; }
  for (int i = 0; i < cnt2; i++) { q = q * 10 + 9; }
  for (int i = 0; i < cnt1; i++) { q = q * 10; }
  ll g = gcd(p, q);
  p /= g; q /= g;
  printf("%I64d/%I64d\n", p, q);
}
//分数转化为小数
//定理: 有理数a / b(其中0 < a < b，(a, b) = 1)能表示成纯循环小数的充要条件是(b, 10) = 1
//定理: 有理数a / b, 0 < a < b, (a, b) = 1, b = (2 ^ α) * (5 ^ β) * b1, (b1, 10) = 1,
//      b1不等于1，α，β不全为零，则a / b可以表示为纯循环小数，其不循环的位数为u = max(α, β)
void Work(int n) {
  bool flag = false;
  int ans[N] = { 0 }, f[N]={ 0, 1 }, k = 1, cnt = 0;
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
