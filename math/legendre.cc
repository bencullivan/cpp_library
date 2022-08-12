/*
    Returns the largest integer i such that p^i divides n!
    p is prime
    Time: O(log(n))
*/
long long legendre(long long n, long long p) {
    long long dsum = 0;
    long long m = n;
    while (m > 0) {
        dsum += m%p;
        m /= p;
    }
    return (n-dsum)/(p-1);
}