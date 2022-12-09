// 2D geometry

using db = double;
const db PI = acos(-1.0);

template <typename T> struct point {
  T x;
  T y;

  point() : x(0), y(0) {}

  point(T _x, T _y) : x(_x), y(_y) {}

  point scaled(T f) const { return point(x * f, y * f); }

  // distance from the origin
  db norm() const { return hypot(static_cast<db>(x), static_cast<db>(y)); }

  // squared distance from the origin
  T norm2() const { return x * x + y * y; }

  // distance between this point and p
  db dist(const point &p) const {
    return hypot(static_cast<db>(x - p.x), static_cast<db>(y - p.y));
  }

  // square of the distance between this point and p
  T dist2(const point &p) const {
    return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
  }

  // dot product between this point and p
  T dot(const point &p) const { return x * p.x + y * p.y; }

  // magnitude of (x, y, 0) X (p.x, p.y, 0)
  T cross(const point &p) { return x * p.y - y * p.x; }

  // the angle from the origin to this point (0 <= theta < 2pi)
  db angle() const { return atan2(static_cast<db>(y), static_cast<db>(x)); }

  // the angle between the vectors from the origin to these two points
  db angle(const point &p) const { return acos(dot(p) / norm() / p.norm()); }

  // the distance to the line segment with endpoints a and b
  db dist_to_seg(const point &a, const point &b) {
    if ((*this - a).angle(b - a) * 2 <= PI &&
        (*this - b).angle(a - b) * 2 <= PI) {
      return sin((*this - a).angle(b - a)) * dist(a);
    }
    return std::min(dist(a), dist(b));
  }

  // whether this point is inside the provided convex polygon
  // the polygon's vertices must be listed in clockwise or counter-clockwise
  // order
  bool inside_convex(const std::vector<point> &polygon, bool clockwise,
                     bool include_edges = 1) {
    for (size_t i = 0; i < polygon.size(); i++) {
      point a = polygon[i + 1 == polygon.size() ? 0 : i + 1] - polygon[i];
      point b = *this - polygon[i];
      T v = a.cross(b);
      if ((v > 0 && clockwise) || (v < 0 && !clockwise) ||
          (v == 0 && !include_edges))
        return 0;
    }
    return 1;
  }

  bool operator==(const point &p) const { return x == p.x && y == p.y; }

  bool operator!=(const point &p) const { return x != p.x || y != p.y; }

  point operator+() const { return point(x, y); }

  point operator-() const { return point(-x, -y); }

  point &operator+=(const point &p) {
    x += p.x;
    y += p.y;
    return *this;
  }

  point &operator-=(const point &p) {
    x -= p.x;
    y -= p.y;
    return *this;
  }

  friend point operator+(const point &l, const point &r) {
    return point(l) += r;
  }

  friend point operator-(const point &l, const point &r) {
    return point(l) -= r;
  }

  friend std::istream &operator>>(std::istream &is, point &p) {
    return is >> p.x >> p.y;
  }

  friend std::ostream &operator<<(std::ostream &os, const point &p) {
    return os << p.x << ' ' << p.y;
  }
};

// convex hull code is adapted from:
// https://cp-algorithms.com/geometry/convex-hull.html
namespace convex_hull {

template <typename T>
bool cw(point<T> s1, point<T> s2, bool include_collinear) {
  auto o = s1.cross(s2);
  return o < 0 || (include_collinear && o == 0);
}

template <typename T>
bool ccw(point<T> s1, point<T> s2, bool include_collinear) {
  auto o = s1.cross(s2);
  return o > 0 || (include_collinear && o == 0);
}

// this transforms the input vector into the convex hull
template <typename T>
void transform(std::vector<point<T>> &a, bool include_collinear = false) {
  if (a.size() <= 1)
    return;

  std::sort(a.begin(), a.end(), [](point<T> &l, point<T> &r) {
    return l.x == r.x ? l.y < r.y : l.x < r.x;
  });

  point<T> p1 = a[0], p2 = a.back();
  std::vector<point<T>> up, down;
  up.push_back(p1);
  down.push_back(p1);
  point<T> mid = p2 - p1;
  for (int i = 1; i < (int)a.size(); i++) {
    if (i == (int)a.size() - 1 || cw(a[i] - p1, mid, include_collinear)) {
      while (up.size() >= 2 &&
             !cw(up[up.size() - 1] - up[up.size() - 2],
                 a[i] - up[up.size() - 2], include_collinear)) {
        up.pop_back();
      }
      up.push_back(a[i]);
    }
    if (i == (int)a.size() - 1 || ccw(a[i] - p1, mid, include_collinear)) {
      while (down.size() >= 2 &&
             !ccw(down[down.size() - 1] - down[down.size() - 2],
                  a[i] - down[down.size() - 2], include_collinear)) {
        down.pop_back();
      }
      down.push_back(a[i]);
    }
  }

  if (include_collinear && up.size() == a.size()) {
    reverse(a.begin(), a.end());
    return;
  }
  a.clear();
  for (int i = 0; i < (int)up.size(); i++)
    a.push_back(up[i]);
  for (int i = down.size() - 2; i > 0; i--)
    a.push_back(down[i]);
}

// this returns the indices of the points that make up the convex hull
template <typename T>
std::vector<int> indices(const std::vector<point<T>> &a,
                         bool include_collinear = false) {
  if (a.size() == 0)
    return {};
  if (a.size() == 1)
    return {0};

  std::vector<int> id(a.size());
  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(), [&](int i, int j) {
    return a[i].x == a[j].x ? a[i].y < a[j].y : a[i].x < a[j].x;
  });

  point<T> p1 = a[id[0]], p2 = a[id.back()];
  std::vector<int> up, down;
  up.push_back(id[0]);
  down.push_back(id[0]);
  point<T> mid = p2 - p1;
  for (int i = 1; i < (int)a.size(); i++) {
    if (i == (int)a.size() - 1 || cw(a[id[i]] - p1, mid, include_collinear)) {
      while (up.size() >= 2 &&
             !cw(a[up[up.size() - 1]] - a[up[up.size() - 2]],
                 a[id[i]] - a[up[up.size() - 2]], include_collinear)) {
        up.pop_back();
      }
      up.push_back(id[i]);
    }
    if (i == (int)a.size() - 1 || ccw(a[id[i]] - p1, mid, include_collinear)) {
      while (down.size() >= 2 &&
             !ccw(a[down[down.size() - 1]] - a[down[down.size() - 2]],
                  a[id[i]] - a[down[down.size() - 2]], include_collinear)) {
        down.pop_back();
      }
      down.push_back(id[i]);
    }
  }

  if (include_collinear && up.size() == a.size()) {
    std::reverse(id.begin(), id.end());
    return id;
  }
  id.clear();
  for (int i = 0; i < (int)up.size(); i++)
    id.push_back(up[i]);
  for (int i = down.size() - 2; i > 0; i--)
    id.push_back(down[i]);
  return id;
}

} // namespace convex_hull

using P = point<double>;