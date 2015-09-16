//二分
template <class T> int BS(const T a[], int L, int R, int x) {
  int l = L, r = R, mid;
  while (l <= r) {
    mid = l + r >> 1;
    if (a[mid] > x) { mid = r = mid - 1;}
    else if (a[mid] < x) { l = mid + 1;}
    else { break; }
  }
  return a[mid] == x ? mid : -1;
}

template <class T> int BSup(const T a[], int L, int R) {
  int l = L, r = R, mid;
  while (l + 1 < r) {
    mid = l + r >> 1;
    if (judge(a[mid])) { l = mid; }
    else { r = mid; }
  }
  return l;
}

template <class T> int BSlow(const T a[], int L, int R) {
  int l = L, r = R, mid;
  while (l + 1 < r) {
    mid = l + r >> 1;
    if (judge(a[mid])) { r = mid; }
    else { l = mid; }
  }
  return r;
}

//三分 求函数极大值
double TS(double l, double r) {
  double mid, midmid, midv, midmidv;
  while (r - l > EPS) {
    mid = l + (r - l) / 3.0;
    midmid = r - (r - l) / 3.0;
    midv = calc(mid); midmidv = calc(midmid);
    if (midv > midmidv) { r = midmid; }
    else { l = mid; }
  }
  return l;
}

//归并排序 求逆序数
ll cnt;
template <class T> void mergeSort(const T a[], int l, int r) {
  if (l >= r) { return; }
  int mid = (l + r) >> 1;
  mergesort(a, l, mid);
  mergesort(a, mid + 1, r);
  vector<T> res;
  int i = l, j = mid + 1;
  while (i <= mid && j <= r) {
    if (a[i] > a[j]) {
      res.push_back(a[j++]);
      cnt += mid + 1 - i;
    } else {
      res.push_back(a[i++]);
    }
  }
  while (i <= mid) { res.push_back(a[i++]); }
  while (j <= r) { res.push_back(a[j++]); }
  for (int k = l; k <= r; k++) { a[k].b = res[k - l]; }
}

//快排
template <class T> void quickSort(const T a[], int l, int r) {
  if (l >= h) { return; }
  int i = l, j = r, v = a[l];
  while (i < j) {
    while (i < j && a[j] >= v) { j--; }
    a[i] = a[j];
    while (i < j && a[i] <= v) { i++; }
    a[j] = a[i];
  }
  a[i] = v;
  quickSort(a, l, i - 1);
  quickSort(a, i + 1, h);
}
