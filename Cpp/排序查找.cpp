//二分查找有序数组是否存在一个元素
template <typename T> int BS(const T a[], int l, int r, T key) {
  int mid;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (a[mid] == key) { return mid; }
    if (a[mid] > key) { r = mid - 1;}
    else { l = mid + 1;}
  }
  return -1;
}
//lower_bound
template <typename T> int BSlower_bound(const T a[], int l, int r, T key) { //[l, r]
  int mid;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (a[mid] < key) { l = mid + 1; }
    else { r = mid - 1; }
  }
  return l;
}
//upper_bound
template <typename T> int BSupper_bound(const T a[], int l, int r, T key) { //[l, r]
  int mid;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (a[mid] <= key) { l = mid + 1; }
    else { r = mid - 1; }
  }
  return l;
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
template <typename T> void mergeSort(T a[], int l, int r) {
  if (l >= r) { return; }
  int mid = (l + r) >> 1;
  mergeSort(a, l, mid);
  mergeSort(a, mid + 1, r);
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
  for (int k = l; k <= r; k++) { a[k] = res[k - l]; }
}
//快排
template <typename T> void quickSort(T a[], int l, int r) {
  if (l >= r) { return; }
  int i = l, j = r, v = a[l];
  while (i < j) {
    while (i < j && a[j] >= v) { j--; }
    a[i] = a[j];
    while (i < j && a[i] <= v) { i++; }
    a[j] = a[i];
  }
  a[i] = v;
  quickSort(a, l, i - 1);
  quickSort(a, i + 1, r);
}
