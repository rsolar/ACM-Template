#include <iostream>
#include <cstdio>
using namespace std;

char *ans[] = { "-1"
                , "-1" //1
                , "-1" //2
                , "-1" //3
                , "1 * 2\n5 + 3\n6 + 4" //4
                , "1 * 2\n6 * 3\n7 - 4\n8 / 5" //5
                , "1 + 2\n3 + 4\n5 / 6\n7 + 8\n9 * 10" //6
                , "1 + 2\n3 + 8\n9 / 4\n10 + 5\n11 + 6\n12 + 7" //7
                , "1 - 2\n3 - 4\n5 * 9\n10 + 11\n12 + 6\n13 + 7\n14 + 8" //8
                , "1 / 2\n3 / 4\n5 / 6\n10 + 11\n12 + 13\n7 + 8\n9 + 15\n16 - 14" //9
                , "1 / 2\n3 / 4\n5 / 6\n7 / 8\n11 + 12\n13 + 14\n15 + 16\n17 + 9\n18 + 10" //10
                , "1 / 2\n3 / 4\n5 - 6\n7 - 8\n9 * 14\n15 + 12\n13 + 16\n17 + 18\n19 + 10\n20 + 11" //11
                , "1 - 2\n3 - 4\n5 - 6\n7 - 8\n9 - 10\n13 + 14\n15 + 16\n17 + 18\n19 + 20\n21 + 11\n12 + 22" //12
              };

int main() {
	int n;
	while (~scanf("%d", &n)) {
		if (n < 13) {
			puts(ans[n]);
		} else {
			puts("1 + 2"); //2n
			puts("3 + 4"); //2n
			puts("5 + 6"); //2n
			puts(n % 2 ? "7 + 8" : "7 / 8"); //2n or 1
			printf("%d + 9\n", n + 1); //3n
			printf("%d / 10\n", n + 5); //3
			printf("%d / 11\n", n + 2); //2
			printf("%d / 12\n", n + 3); //2
			if (n % 2) {
				printf("%d / 13\n", n + 4); //2
				//9 steps
			} else {
				printf("13 / 14\n"); //1
				printf("%d + %d\n", n + 4, n + 9); //2
				//10 steps
			}
			int used = n % 2 ? 13 : 14, step = n % 2 ? 9 : 10;
			for (int i = used + 1; i < n; i += 2) {
				printf("%d / %d\n", i, i + 1); //1
				step++;
				printf("%d * %d\n", n + step - 1, n + step); //2
				step++;
			}
			printf("%d * %d\n", n + 6, n + 7); //6
			printf("%d * %d\n", n + 8, n + n - 3);  //12
			printf("%d * %d\n", n + n - 4, n + n - 2); //24
		}
	}
}
