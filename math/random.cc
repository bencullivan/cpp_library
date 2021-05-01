/*
Use with uniform_int_distribution, normal_distribution, or exponential_distribution
ex: uniform_int_distribution<int>(0, x)(rng32) will generate a random int between 0 and x
*/
random_device rd32, rd64;
mt19937 rng32(rd32());
mt19937_64 rng64(rd64());