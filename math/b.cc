#include <bits/stdc++.h>

typedef unsigned ui;
typedef unsigned long long ull;
typedef long long ll;
using namespace std;

struct point {
	double x = 0, y = 0;
};

double slope;
bool vert;
bool flip;

bool touch(point c, point b) {
	if (b.x == c.x) {
		return vert;
	}
	if ((b.y - c.y) / (b.x - c.x) == slope) {
		cout << "TOUCH\n";
		return 1;
	}
	return 0;
}

void done(bool left) {
	if (left) cout << (flip ? "RIGHT":"LEFT") << '\n';
	else cout << (flip ? "LEFT":"RIGHT") << '\n';
}

void solve() {
	point a, b, c;
	cin >> a.x >> a.y;
	cin >> b.x >> b.y;
	cin >> c.x >> c.y;
	flip = a.x > b.x;
	if (a.x > b.x) swap(a, b);
	vert = a.x == b.x;
	if (!vert) slope = (b.y - a.y) / (b.x - a.x);
	if (c.x < b.x) if (touch(c, b)) return;
	else if (touch(b, c)) return;
	
	if (vert) slope = -1e18;

	if (a.x == c.x) {
		done(c.y > a.y);
	}
	else {
		double s;
		if (a.x < c.x) {
		}
		else {
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	int tt = 1;
	cin >> tt;
	for (int i = 1; i <= tt; i++) {
		solve();
	}
	return 0;
}