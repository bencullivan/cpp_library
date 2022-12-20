// maximize a single variable unimodal function
// uses strategy from kactl hillClimbing: https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/HillClimbing.h
std::pair<double, double> maximize_unimodal(double start, double (*f)(double)) {
	std::pair<double, double> best = std::make_pair(f(start),start);
	double tolerance = 1e-18;
	for (double jmp = L*2; jmp >= tolerance; jmp /= 2) {
		{
			double d = best.second + jmp;
			std::pair<double, double> cur = std::make_pair(f(d), d);
			best = std::max(best, cur);
		}
		{
			double d = best.second - jmp;
			std::pair<double, double> cur = std::make_pair(f(d), d);
			best = std::max(best, cur);
		}
	}
	return best;
}