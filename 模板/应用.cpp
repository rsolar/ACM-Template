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
