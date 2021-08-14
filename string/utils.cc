vector<string> split(const string& s) {
#define isspace(x) ((x) == ' ')
  int a = 0, b = 0, n = s.size();
  vector<string> r;
  while (b < n) {
    while (b < n && !isspace(s[b])) b++;
    r.push_back(s.substr(a, b - a));
    while (b < n && isspace(s[b])) b++;
    a = b;
  }
  return r;
#ifdef isspace
#undef isspace
#endif
}