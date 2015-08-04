#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
	int a, b, c, d;
	char ans;
	while (~scanf("%d %d %d %d", &a, &b, &c, &d)) {
		double aa = b * log(1.0 * a), cc = d * log(1.0 * c);
		if (b == 0) { aa = 1.0; }
		if (d == 0) { cc = 1.0; }
		if ((a >= c && b > d) || (a > c && b >= d) || aa - cc > 1e-7) { ans = '>'; }
		else if ((a <= c && b < d) || (a < c && b <= d) || cc - aa > 1e-7) { ans = '<';	}
		else { ans = '='; }
		printf("%c\n", ans);
	}
}
