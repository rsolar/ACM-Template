//Nim博弈
//计算从1-n范围内的SG值
//Array存储可以走的步数，Array[0]表示可以有多少种走法
//Array[]需要从小到大排序
//HDU1847 博弈SG函数
//1.可选步数为1-m的连续整数，直接取模即可，SG(x) = x % (m + 1);
//2.可选步数为任意步，SG(x) = x;
//3.可选步数为一系列不连续的数，用GetSG(计算)
int SG[N], Hash[N];

void GetSG(int Array[], int n = N - 1) {
	memset(SG, 0, sizeof(SG));
	for (int i = 0; i <= n; ++i) {
		memset(Hash, 0, sizeof(Hash));
		for (int j = 1; j <= Array[0]; j++) {
			if (i < Array[j]) { break; }
			Hash[SG[i - Array[j]]] = 1;
		}
		for (int j = 0; j <= n; j++) {
			if (!Hash[j]) { SG[i] = j; break; }
		}
	}
}
