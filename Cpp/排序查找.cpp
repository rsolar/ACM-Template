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
  double mid1, mid2;
  while (r - l > EPS) {
    mid1 = l + (r - l) / 3.0; mid2 = r - (r - l) / 3.0;
    if (calc(mid1) > calc(mid2)) { r = mid2; }
    else { l = mid1; }
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
  vector<T> res(r - l + 1);
  int i = l, j = mid + 1, k = 0;
  while (i <= mid && j <= r) {
    if (a[i] > a[j]) {
      res[k++] = a[j++];
      cnt += mid + 1 - i;
    } else {
      res[k++] = a[i++];
    }
  }
  while (i <= mid) { res[k++] = a[i++]; }
  while (j <= r) { res[k++] = a[j++]; }
  for (k = l; k <= r; k++) { a[k] = res[k - l]; }
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
