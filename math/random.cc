// Use with uniform_int_distribution, normal_distribution, or exponential_distribution
// ex: uniform_int_distribution<int>(0, x)(rng32) will generate a random int between 0 and x
mt19937 rng32(chrono::high_resolution_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::high_resolution_clock::now().time_since_epoch().count());