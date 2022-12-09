/**
 * Euler's totient function
 * Calculates the number of integers in the range [1,a] that are coprime to a.
 * Properties:
 *      - If a is prime and b > 0, phi(a^b) = a^b - a^(b-1)
 *      - If a and b are coprime, phi(a*b) = phi(a)*phi(b)
 *      - If a and m are coprime, a^phi(m) % m = 1
 * Time: O(sqrt(N))
 * Source: https://cp-algorithms.com/algebra/phi-function.html
 */
long long phi(long long a) {
  long long r = a;
  for (long long i = 2; i * i <= a; i++) {
    if (a % i == 0) {
      while (a % i == 0) {
        a /= i;
      }
      r -= r / i;
    }
  }
  if (a > 1) {
    r -= r / a;
  }
  return r;
}
/**
 * Calculates phi(i) for all i in the range [1,n]
 * Time: O(n*log(log(n)))
 * Source: https://cp-algorithms.com/algebra/phi-function.html
 */
vector<int> all_phi(int n) {
  vector<int> ph(n + 1);
  for (int i = 0; i <= n; i++) {
    ph[i] = i;
  }
  for (int i = 2; i <= n; i++) {
    if (ph[i] == i) {
      for (int j = i; j <= n; j += i) {
        ph[j] -= ph[j] / i;
      }
    }
  }
  return ph;
}