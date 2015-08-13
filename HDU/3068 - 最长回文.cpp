#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 110005

char s[N];
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

int main() {
	while (~scanf("%s", s)) {
		int len = strlen(s), ans = 0, mlen = (len << 1) + 2;
		Manacher(s, len);
		for (int i = 0; i < mlen; i++) {
			ans = max(ans, mdp[i]);
		}
		printf("%d\n", ans - 1);
	}
}
