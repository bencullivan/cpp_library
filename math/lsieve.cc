/*
    The sieve of Eratosthenes.
    Generates every prime number less than or equal to N.
    Time: O(N)
    Source: https://www.geeksforgeeks.org/sieve-of-eratosthenes/
*/
vector<long long> primes;
void sieve(long long N) {
    vector<bool> is_prime(N + 1, true);
    vector<long long> smallest_prime_factor(N + 1);
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i <= N; i++) {
        if (is_prime[i]) {
            smallest_prime_factor[i] = i;
            primes.push_back(i);
        }
        for (long long j = 0; j < (long long) primes.size() && primes[j] <= smallest_prime_factor[i] && i * primes[j] <= N; j++) {
            is_prime[i * primes[j]] = false;
            smallest_prime_factor[i * primes[j]] = primes[j];
        }
    }
}