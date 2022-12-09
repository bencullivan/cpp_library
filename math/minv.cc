/**
 * Extended Euclidean algorithm for finding the solution (x, y) to ax+by =
 * gcd(a,b) Returns gcd(a,b) Time: O(log(min(a,b))
 * source: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
 */
long long ext_gcd(long long a, long long b, long long &x, long long &y) {
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
 * Only exists if a and m are coprime
 * Time: O(log(min(a,m)))
 */
long long minv(long long a, long long m) {
  long long x, y;
  ext_gcd(a, m, x, y);
  return (x % m + m) % m;
}