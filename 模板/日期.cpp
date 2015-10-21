//日期函数
int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
struct Date {
  int year, month, day;
};

//判闰年
inline int leap(int year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

//判合法性
inline int legal(Date a) {
  if (a.month < 0 || a.month > 12) { return 0; }
  if (a.month == 2) { return a.day > 0 && a.day <= 28 + leap(a.year); }
  return a.day > 0 && a.day <= days[a.month - 1];
}

//比较日期大小
inline int datecmp(Date a, Date b) {
  if (a.year != b.year) { return a.year - b.year; }
  if (a.month != b.month) { return a.month - b.month; }
  return a.day - b.day;
}

//返回指定日期是星期几
int weekday(Date a) {
  int tm = a.month >= 3 ? (a.month - 2) : (a.month + 10);
  int ty = a.month >= 3 ? a.year : (a.year - 1);
  return (ty + ty / 4 - ty / 100 + t y / 400 + (int)(2.6 * tm - 0.2) + a.day) % 7;
}

//日期转天数偏移
int date2int(Date a) {
  int ret = a.year * 365 + (a.year - 1) / 4 - (a.year - 1) / 100 + (a.year - 1) / 400;
  days[1] += leap(a.year);
  for (int i = 0; i < a.month - 1; ret += days[i++]);
  days[1] = 28;
  return ret + a.day;
}

//天数偏移转日期
Date int2date(int a) {
  Date ret;
  ret.year = a / 146097 * 400;
  for (a %= 146097; a >= 365 + leap(ret.year); a -= 365 + leap(ret.year), ret.year++);
  days[1] += leap(ret.year);
  for (ret.month = 1; a >= days[ret.month - 1]; a -= days[ret.month - 1], ret.month++);
  days[1] = 28;
  ret.day = a + 1;
  return ret;
}

//------------------------------------------------------------------------------

//求某天是星期几
char *DaysOfTheWeek(int y, int m, int d) {
  char *name[] = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
  int a;
  //1月2月当作前一年的13,14月
  if (m == 1 || m == 2) { m += 12; y--; }
  //判断是否在1752年9月3日之前
  if ((y < 1752) || (y == 1752 && m < 9) || (y == 1752 && m == 9 && d < 3)) {
    a = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 + 5) % 7;
  } else {
    a = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
  }
  return name[a];
}
