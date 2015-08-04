#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long ll;

int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		printf("%d\n", (int)pow(10.0 , (n * log10(n) - (ll)(n * log10(n)))));
	}
}
