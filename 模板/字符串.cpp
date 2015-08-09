//hash_fun.h
inline size_t __stl_hash_string(const char *__s) {
	unsigned long __h = 0;
	for (; *__s; ++__s) { __h = 5 * __h + *__s; }
	return size_t(__h);
}

// BKDR Hash Function
inline size_t BKDRHash(char *str) {
	size_t seed = 131; // 31 131 1313 13131 131313 etc..
	size_t hash = 0;
	while (*str) { hash = hash * seed + (*str++); }
	return (hash & 0x7FFFFFFF);
}

//------------------------------------------------------------------------------

//Manacher 最长回文子串
char mstr[N << 1];
int mdp[N << 1];
void Manacher(char s[], int len) {
	int l = 0, mx = 0, id = 0;
	mstr[l++] = '$'; mstr[l++] = '#';
	for (int i = 0; i < len; i++) { mstr[l++] = s[i]; mstr[l++] = '#'; }
	mstr[l] = 0;
	for (int i = 0; i < l; i++) {
		mdp[i] = mx > i ? min(mdp[(id << 1) - i], mx - i) : 1;
		while (mstr[i + mdp[i]] == mstr[i - mdp[i]]) { mdp[i]++; }
		if (i + mdp[i] > mx) { mx = i + mdp[i]; id = i; }
	}
}
//abaaba
//i: 0 1 2 3 4 5 6 7 8 9 10 11 12 13
//mstr[i]: $ # a # b # a # a $ b # a #
//mdp[i]: 1 1 2 1 4 1 2 7 2 1 4 1 2 1
char s[N];
int main() {
	while (~scanf("%s", s)) {
		int len = strlen(s), ans = 0;
		Manacher(s, len);
		for (int i = 0; i < (len << 1) + 2; i++) {
			ans = max(ans, mdp[i] - 1);
		}
		printf("%d\n", ans);
	}
}

//------------------------------------------------------------------------------

//strstr 在串中查找指定字符串的第一次出现
char *strstr(char *str1, const char *str2);

//KMP匹配算法 O(M+N)
//next[]的含义：x[i-next[i]...i-1]=x[0...next[i]-1]
//next[i]为满足x[i-z...i-1]=x[0...z-1]的最大z值(就是x的自身匹配)
int next[N];
void getNext(char x[], int m) {
	int i = 0, j = -1; next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = next[j]; }
		next[++i] = ++j;
	}
}
//返回x在y中出现的次数，可以重叠
//x是模式串，y是主串
int KMP_Count(char x[], int m, char y[], int n, int &longest, int &lp) {
	getNext(x, m);
	int i = 0, j = 0, ans = 0; longest = 0; lp = 0;
	while (i < n) {
		while (j != -1 && y[i] != x[j]) { j = next[j]; }
		i++; j++;
		//返回最大匹配长度及对应起始位置
		if (j > longest) { longest = j; lp = i − j; }
		if (j >= m) { j = next[j]; ans++; }
	}
	return ans;
}

//Sunday Algorithm BM算法的改进的算法
void SUNDAY(char *text, char *patt) {
	size_t temp[256], *shift = temp;
	size_t i, patt_size = strlen(patt), text_size = strlen(text);
	for (i = 0; i < 256; i++) { *(shift + i) = patt_size + 1; }
	for (i = 0; i < patt_size; i++) {
		*(shift + unsigned char(*(patt + i))) = patt_size - i;
	}
	size_t limit = text_size - patt_size + 1;
	for (i = 0; i < limit; i += shift[text[i + patt_size]]) {
		if (text[i] == *patt) {
			char *match_text = text + i + 1;
			size_t match_size = 1;
			do {// 输出所有匹配的位置
				if (match_size == patt_size) { cout << "the NO. is " << i << endl; }
			} while ((*match_text++) == patt[match_size++]);
		}
	}
}


