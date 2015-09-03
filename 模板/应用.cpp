//Joseph Œ Ã‚
int Joseph(int n, int m) {
	int ret = 0;
	for (int i = 2; i <= n; i++) {
		ret = (ret + m) % i;
	}
	return ret + 1;
}
