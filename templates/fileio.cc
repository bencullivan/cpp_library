void fileio(string name = "")
{
  freopen((name == "" ? "input.txt" : name + ".in").c_str(), "r", stdin);
  freopen((name == "" ? "output.txt" : name + ".out").c_str(), "w", stdout);
}
