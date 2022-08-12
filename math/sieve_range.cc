vector<long long> primes;
vector<bool> is_prime;
/*
    The sieve of Eratosthenes.
    Generates every prime number less than or equal to N.
    Source: https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
*/
void sieve(long long N) {
    primes.clear();
    is_prime.assign(N+1, true);
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = i*i; j <= N; j += i) is_prime[j] = false;
        }
    }
}
/*
    Generates all prime numbers in the range [L, R] (inclusive)
    Time: O((R-L+1)*log(log(R)) + sqrt(R)*log(log(sqrt(R))))
    Source: https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
*/
void range(long long L, long long R) {
    long long root = sqrt(R);
    sieve(root);
    is_prime = vector<bool>(R - L + 1, true);
    for (long long i:primes) {
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i) {
            is_prime[j - L] = false;
        }
    }
    if (L == 1) is_prime[0] = false;
    primes.clear();
    for (long long i = 0; i < R - L + 1; i++) {
        if (is_prime[i]) primes.push_back(i + L);
    }
}