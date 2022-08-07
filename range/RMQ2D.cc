#define LGMX 1005
int lg[LGMX+1];
bool lg_init = 0;
template<typename R, typename T, typename U> void build(T* st, U* ar, int n, int m) {
	if (!lg_init) {
		for (int i = 2; i <= LGMX; i++) lg[i] = lg[i>>1]+1;
		lg_init = 1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) st[i][0][j][0] = ar[i][j];
		for (int k = 0; (1<<k) <= m; k++)
			for (int j = 0; j+(1<<k) <= m; j++)
				st[i][0][j][k+1] = max(st[i][0][j][k], st[i][0][j+(1<<k)][k]);
	}
	for (int ik = 0; (1<<ik) <= n; ik++)
		for (int i = 0; i+(1<<ik) <= n; i++)
			for (int jk = 0; (1<<jk) <= m; jk++)
				for (int j = 0; j+(1<<jk) <= m; j++)
					st[i][ik+1][j][jk] = max(st[i][ik][j][jk], st[i+(1<<ik)][ik][j][jk]);
}
template<typename R, typename T> R get(T* st, int a, int b, int c, int d) {
	int lr = lg[c-a+1], lc = lg[d-b+1];
	return max({st[a][lr][b][lc], st[a][lr][d-(1<<lc)+1][lc], st[c-(1<<lr)+1][lr][b][lc], st[c-(1<<lr)+1][lr][d-(1<<lc)+1][lc]});
}