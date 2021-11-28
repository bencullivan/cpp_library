/**
* Extended Euclidean algorithm for finding the solution (x, y) to ax+by = gcd(a,b)
* Returns gcd(a,b)
* Time: O(log(min(a,b))
* Source: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
*/
long long extended_euclidean(long long a, long long b, long long& x, long long& y) {
	x = 1, y = 0;
	long long x1 = 0, y1 = 1;
	long long q, t;
	while (b > 0) {
		q = a / b;
		t = x - q * x1;
		x = x1;
		x1 = t;
		t = y - q * y1;
		y = y1;
		y1 = t;
		t = a - q * b;
		a = b;
		b = t;
	}
	return a;
}
/**
* Modular inverse of a, mod m
* If m is prime, this is equivalent to mpow(a,m-2)
* Only exists if a and m are coprime
* Time: O(log(min(a,m)))
*/
long long minv(long long a, long long m, bool prime = true) {
	if (prime) return mpow(a, m - 2);
	long long x, y;
	extended_euclidean(a, m, x, y);
	return (x % m + m) % m;
}
/**
* Solves the linear diophantine equation ax + by = c
* Also can be used to solve the linear congruence relation 
* ax % m = b % m, rewritten as ax+my = b
* Returns whether a solution exists
* 
* Suppose we have a solution: x0, y0
* Now, all solutions (x,y) will be of the form: x = x0 + k*b/g, y = y0 - k*a/g
* Where g is gcd(a, b) and k is an arbitrary integer.
* Chicken McNugget Theorem: for any positive coprime integers a,b the largest integer that cannot be written 
* in the form ax + by for nonnegative x,y is ab - a - b
* 
* Time: O(log(min(abs(a),abs(b)))
* Source: https://cp-algorithms.com/algebra/linear-diophantine-equation.html
*/
bool linear_diophantine(long long a, long long b, long long c, long long& x, long long& y, long long& g) {
	if (a == 0 && b == 0) {
		x = y = 0;
		return c == 0;
	}
	g = extended_euclidean(abs(a), abs(b), x, y);
	if (c % g) return false;
	x *= c / g;
	y *= c / g;
	if (a < 0) x = -x;
	if (b < 0) y = -y;
	return true;
}
/**
* Finds the number of solutions to the linear diophatine equation ax + by = c
* subject to constraints minx <= x <= maxx, miny <= y <= maxy
* Time: O(log(min(abs(a),abs(b))) 
* Source: https://cp-algorithms.com/algebra/linear-diophantine-equation.html
*/
long long along long_linear_diophantine(long long a, long long b, long long c, long long minx, long long maxx, long long miny, long long maxy) {
	if (a == 0 && b == 0) {
		if (c == 0) return (maxx - minx + 1) * (maxy - miny + 1);
		return 0;
	}
 
	auto shift_solution = [](long long& x, long long& y, long long a, long long b, long long cnt) {
		x += cnt * b;
		y -= cnt * a;
	};
 
	long long x, y, g;
	if (!linear_diophantine(a, b, c, x, y, g)) return 0;
	a /= g;
	b /= g;
 
	long long sign_a = a > 0 ? +1 : -1;
	long long sign_b = b > 0 ? +1 : -1;
 
	shift_solution(x, y, a, b, (minx - x) / b);
	if (x < minx) shift_solution(x, y, a, b, sign_b);
	if (x > maxx) return 0;
	long long lx1 = x;
 
	shift_solution(x, y, a, b, (maxx - x) / b);
	if (x > maxx) shift_solution(x, y, a, b, -sign_b);
	long long rx1 = x;
 
	shift_solution(x, y, a, b, -(miny - y) / a);
	if (y < miny) shift_solution(x, y, a, b, -sign_a);
	if (y > maxy) return 0;
	long long lx2 = x;
 
	shift_solution(x, y, a, b, -(maxy - y) / a);
	if (y > maxy) shift_solution(x, y, a, b, sign_a);
	long long rx2 = x;
 
	if (lx2 > rx2) swap(lx2, rx2);
	long long lx = max(lx1, lx2);
	long long rx = min(rx1, rx2);
 
	if (lx > rx) return 0;
	return (rx - lx) / abs(b) + 1;
}