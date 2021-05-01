vector<ll> primes;
vector<ll> spf;
vector<bool> is_prime;

/*
    The sieve of Eratosthenes.
    Generates every prime number less than or equal to N.
    Almost twice as fast as spf_sieve.
    Time: O(N*log(log(N)))
    Source: https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
*/
void sieve(ll N) {
    primes.clear();
    is_prime = vector<bool>(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

/*
    Generates all prime numbers in the range [L, R] (inclusive)
    Time: O((R-L+1)*log(log(R)) + sqrt(R)*log(log(sqrt(R))))
    Source: https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
*/
void range(ll L, ll R) {
    ll root = sqrt(R);
    sieve(root);
    is_prime = vector<bool>(R - L + 1, true);
    for (ll i:primes) {
        for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i) {
            is_prime[j - L] = false;
        }
    }
    if (L == 1) is_prime[0] = false;
    primes.clear();
    for (ll i = 0; i < R - L + 1; i++) {
        if (is_prime[i]) {
            primes.push_back(i + L);
        }
    }
}

/*
    Generates every prime number less than or equal to N.
    Generates the smallest prime factor of every number from 2 to N.
    Time: O(N)
    Source: https://cp-algorithms.com/algebra/prime-sieve-linear.html
*/
void spf_sieve(ll N) {
    primes.clear();
    spf = vector<ll>(N + 1);
    for (ll i = 2; i <= N; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (ll j = 0; j < (ll) primes.size() && primes[j] <= spf[i] && i * primes[j] <= N; j++) {
            spf[i * primes[j]] = primes[j];
        }
    }
}

/*
    Finds the prime factorization of x without precomputation.
    Time: O(sqrt(x))
*/
vector<pair<ll, ll>> get_pf(ll x) {
    vector<pair<ll, ll>> prime_factors;
    for (ll i = 2; i * i <= x; i += 1 + (i & 1)) {
        int ct = 0;
        while (x % i == 0) {
            ct++;
            x /= i;
        }
        if (ct) prime_factors.emplace_back(i, ct);
    }
    if (x > 1) prime_factors.emplace_back(x, 1);
    return prime_factors;
}

/*
    Finds the prime factorization of x using precomputed spfs.
    Must be used with spf_sieve.
    Time: O(log(x))
*/
vector<pair<ll, ll>> get_pf_fast(ll x) {
    ll cur = spf[x];
    int ct = 0;
    vector<pair<ll, ll>> prime_factors;
    while (x > 1) {
        if (cur != spf[x]) {
            prime_factors.emplace_back(cur, ct);
            cur = spf[x];
            ct = 0;
        }
        ct++;
        x /= spf[x];
    }
    if (ct) prime_factors.emplace_back(cur, ct);
    return prime_factors;
}