// kactl 2d geometry
// source: https://github.com/kth-competitive-programming/kactl/tree/main/content/geometry
/**
* Author: Ulf Lundstrom
* Date: 2009-02-26
* License: CC0
* Source: My head with inspiration from tinyKACTL
* Description: Class to handle points in the plane.
*     T can be e.g. double or long long. (Avoid int.)
* Status: Works fine, used a lot
*/
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend istream& operator>>(istream& is, P& p) {
        return is >> p.x >> p.y; }
    friend ostream& operator<<(ostream& os, P p) {
        return os << p.x << " " << p.y; }
};
/**
* Author: Simon Lindholm
* Date: 2019-04-17
* License: CC0
* Source: https://codeforces.com/blog/entry/58747
* Description: Finds the closest pair of points.
* Time: O(n \log n)
* Status: stress-tested
*/
#define P Point<long long>
pair<P, P> closest(vector<P> v) {
    assert(sz(v) > 1);
    set<P> S;
    sort(all(v), [](P a, P b) { return a.y < b.y; });
    pair<ll, pair<P, P>> ret{LLONG_MAX, {P(), P()}};
    int j = 0;
    for (P p : v) {
        P d{1 + (ll)sqrt(ret.first), 0};
        while (v[j].y <= p.y - d.x) S.erase(v[j++]);
        auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
        for (; lo != hi; ++lo)
            ret = min(ret, {(*lo - p).dist2(), {*lo, p}});
        S.insert(p);
    }
    return ret.second;
}
#undef P
/**
* Author: Ulf Lundstrom
* Date: 2009-03-21
* License: CC0
* Source: Basic math
* Description: Returns the signed distance between point p and the line containing points a and b. 
* Positive value on left side and negative on right as seen from a towards b. a==b gives nan. 
* P is supposed to be Point<T> or Point3D<T> where T is e.g. double or long long. It uses products in 
* intermediate steps so watch out for overflow if using int or long long. Using Point3D will always give a non-negative distance. 
* For Point3D, call .dist on the result of the cross product.
* Status: tested
*/
template<class P>
double lineDist(const P& a, const P& b, const P& p) {
    return (double)(b-a).cross(p-a)/(b-a).dist();
}
/**
* Author: Victor Lecomte, chilli
* Date: 2019-05-05
* License: CC0
* Source: https://vlecomte.github.io/cp-geo.pdf
* Description:
* If a unique intersection point of the lines going through s1,e1 and s2,e2 exists \{1, point\} is returned.
* If no intersection point exists \{0, (0,0)\} is returned and if infinitely many exists \{-1, (0,0)\} is returned.
* The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
* Products of three coordinates are used in intermediate steps so watch out for overflow if using int or ll.
* Usage:
*     auto res = lineInter(s1,e1,s2,e2);
*     if (res.first == 1)
*         cout << "intersection point at " << res.second << endl;
* Status: stress-tested, and tested through half-plane tests
*/
template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}
/**
* Author: Victor Lecomte, chilli
* Date: 2019-10-29
* License: CC0
* Source: https://vlecomte.github.io/cp-geo.pdf
* Description: Projects point p onto line ab. Set refl=true to get reflection
* of point p across line ab insted. The wrong point will be returned if P is
* an integer point and the desired point doesn't have integer coordinates.
* Products of three coordinates are used in intermediate steps so watch out
* for overflow.
* Status: stress-tested
*/
template<class P>
P lineProj(P a, P b, P p, bool refl=false) {
    P v = b - a;
    return p - v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}
/**
* Author: Simon Lindholm
* Date: 2015-09-01
* License: CC0
* Description: Computes the pair of points at which two circles intersect. Returns false in case of no intersection.
* Status: stress-tested
*/
#define P Point<double>
bool circleInter(P a, P b, double r1, double r2, pair<P, P>& out) {
    if (a == b) { assert(r1 != r2); return false; }
    P vec = b - a;
    double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
                p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
    if (sum*sum < d2 || dif*dif > d2) return false;
    P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
    out = make_pair(mid + per, mid - per);
    return true;
}
#undef P
/**
* Author: Victor Lecomte, chilli
* Date: 2019-10-29
* License: CC0
* Source: https://vlecomte.github.io/cp-geo.pdf
* Description: Finds the intersection between a circle and a line.
* Returns a vector of either 0, 1, or 2 intersection points.
* P is intended to be Point<double>.
* Status: unit tested
*/
#define P Point<double>
vector<P> circleLine(P c, double r, P a, P b) {
    P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
    double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
    if (h2 < 0) return {};
    if (h2 == 0) return {p};
    P h = ab.unit() * sqrt(h2);
    return {p - h, p + h};
}
#undef P
/**
* Author: chilli, Takanori MAEHARA
* Date: 2019-10-31
* License: CC0
* Source: https://github.com/spaghetti-source/algorithm/blob/master/geometry/_geom.cc#L744
* Description: Returns the area of the intersection of a circle with a
* ccw polygon.
* Time: O(n)
* Status: Tested on GNYR 2019 Gerrymandering, stress-tested
*/
#define P Point<double>
#define arg(p, q) atan2(p.cross(q), p.dot(q))
double circlePoly(P c, double r, vector<P> ps) {
    auto tri = [&](P p, P q) {
        auto r2 = r * r / 2;
        P d = q - p;
        auto a = d.dot(p)/d.dist2(), b = (p.dist2()-r*r)/d.dist2();
        auto det = a * a - b;
        if (det <= 0) return arg(p, q) * r2;
        auto s = max(0., -a-sqrt(det)), t = min(1., -a+sqrt(det));
        if (t < 0 || 1 <= s) return arg(p, q) * r2;
        P u = p + d * s, v = p + d * t;
        return arg(p,u) * r2 + u.cross(v)/2 + arg(v,q) * r2;
    };
    auto sum = 0.0;
    rep(i,0,sz(ps))
        sum += tri(ps[i] - c, ps[(i + 1) % sz(ps)] - c);
    return sum;
}
#undef arg
#undef P
/**
* Author: Ulf Lundstrom
* Date: 2009-04-11
* License: CC0
* Source: http://en.wikipedia.org/wiki/Circumcircle
* Description: The circumcirle of a triangle is the circle intersecting all three vertices. 
* ccRadius returns the radius of the circle going through points A, B and C and ccCenter returns the center of the same circle.
* Status: tested
*/
#define P Point<double>
double ccRadius(const P& A, const P& B, const P& C) {
    return (B-A).dist()*(C-B).dist()*(A-C).dist()/
            abs((B-A).cross(C-A))/2;
}
P ccCenter(const P& A, const P& B, const P& C) {
    P b = C-A, c = B-A;
    return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}
#undef P
/**
* Author: Andrew He, chilli
* Date: 2019-05-07
* License: CC0
* Source: folklore
* Description: Computes the minimum circle that encloses a set of points.
* Time: expected O(n)
* Status: stress-tested
*/
#define P Point<double>
pair<P, double> mec(vector<P> ps) {
    shuffle(all(ps), mt19937(chrono::high_resolution_clock::now().time_since_epoch().count()));
    P o = ps[0];
    double r = 0, EPS = 1 + 1e-8;
    rep(i,0,sz(ps)) if ((o - ps[i]).dist() > r * EPS) {
        o = ps[i], r = 0;
        rep(j,0,i) if ((o - ps[j]).dist() > r * EPS) {
            o = (ps[i] + ps[j]) / 2;
            r = (o - ps[i]).dist();
            rep(k,0,j) if ((o - ps[k]).dist() > r * EPS) {
                o = ccCenter(ps[i], ps[j], ps[k]);
                r = (o - ps[i]).dist();
            }
        }
    }
    return {o, r};
}
#undef P
/**
* Author: Ulf Lundstrom
* Date: 2009-03-21
* License: CC0
* Source:
* Description:
* Returns the shortest distance between point p and the line segment from point s to e.
* Usage: 
*     Point<double> a, b(2,2), p(1,1);
*     bool onSegment = segDist(a,b,p) < 1e-10;
* Status: tested
*/
#define P Point<double>
double segDist(P& s, P& e, P& p) {
    if (s==e) return (p-s).dist();
    auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
    return ((p-s)*d-(e-s)*t).dist()/d;
}
#undef P
/**
* Author: Victor Lecomte, chilli
* Date: 2019-04-26
* License: CC0
* Source: https://vlecomte.github.io/cp-geo.pdf
* Description: Returns true iff p lies on the line segment from s to e.
* Use (segDist(s,e,p)<=epsilon) instead when using Point<double>.
* Status:
*/
template<class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
/**
* Author: Victor Lecomte, chilli
* Date: 2019-04-27
* License: CC0
* Source: https://vlecomte.github.io/cp-geo.pdf
* Description:
If a unique intersection point between the line segments going from s1 to e1 and from s2 to e2 exists then it is returned.
If no intersection point exists an empty vector is returned. If infinitely many exist a vector with 2 elements 
is returned, containing the endpoints of the common line segment.
The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
* Usage:
* vector<P> inter = segInter(s1,e1,s2,e2);
* if (sz(inter)==1)
*   cout << "segments intersect at " << inter[0] << endl;
* Status: stress-tested, tested on kattis:intersection
*/
template<class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
            oc = a.cross(b, c), od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}
/**
* Author: Ulf Lundstrom
* Date: 2009-03-21
* License: CC0
* Source:
* Description: Returns where $p$ is as seen from $s$ towards $e$. 1/0/-1 $\Leftrightarrow$ left/on line/right.
* If the optional argument $eps$ is given 0 is returned if $p$ is within distance $eps$ from the line. 
* P is supposed to be Point<T> where T is e.g. double or long long. 
* It uses products in intermediate steps so watch out for overflow if using int or long long.
* Usage:
*     bool left = sideOf(p1,p2,q)==1;
* Status: tested
*/
template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }
template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
    auto a = (e-s).cross(p-s);
    double l = (e-s).dist()*eps;
    return (a > l) - (a < -l);
}
/**
* Author: black_horse2014, chilli
* Date: 2019-10-29
* License: Unknown
* Source: https://codeforces.com/gym/101673/submission/50481926
* Description: Calculates the area of the union of $n$ polygons (not necessarily
* convex). The points within each polygon must be given in CCW order.
* (Epsilon checks may optionally be added to sideOf/sgn, but shouldn't be needed.)
* Time: $O(N^2)$, where $N$ is the total number of points
* Status: stress-tested, Submitted on ECNA 2017 Problem A
*/
#define P Point<double>
double polyUnion(vector<vector<P>>& poly) {
    static auto ratio = [](P a, P b) -> double { return sgn(b.x) ? a.x/b.x : a.y/b.y; };
    double ret = 0;
    rep(i,0,sz(poly)) rep(v,0,sz(poly[i])) {
        P A = poly[i][v], B = poly[i][(v + 1) % sz(poly[i])];
        vector<pair<double, int>> segs = {{0, 0}, {1, 0}};
        rep(j,0,sz(poly)) if (i != j) {
            rep(u,0,sz(poly[j])) {
                P C = poly[j][u], D = poly[j][(u + 1) % sz(poly[j])];
                int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
                if (sc != sd) {
                    double sa = C.cross(D, A), sb = C.cross(D, B);
                    if (min(sc, sd) < 0)
                        segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
                } else if (!sc && !sd && j<i && sgn((B-A).dot(D-C))>0){
                    segs.emplace_back(ratio(C - A, B - A), 1);
                    segs.emplace_back(ratio(D - A, B - A), -1);
                }
            }
        }
        sort(all(segs));
        for (auto& s : segs) s.first = min(max(s.first, 0.0), 1.0);
        double sum = 0;
        int cnt = segs[0].second;
        rep(j,1,sz(segs)) {
            if (!cnt) sum += segs[j].first - segs[j - 1].first;
            cnt += segs[j].second;
        }
        ret += A.cross(B) * sum;
    }
    return ret / 2;
}
#undef P
/**
* Author: Ulf Lundstrom
* Date: 2009-03-21
* License: CC0
* Source:
* Description: Returns a vector with the vertices of a polygon with everything to the left of the line going from s to e cut away.
* Usage:
*     vector<P> p = ...;
*     p = polygonCut(p, P(0,0), P(1,0));
* Status: tested but not extensively
*/
#define P Point<double>
vector<P> polygonCut(const vector<P>& poly, P s, P e) {
    vector<P> res;
    rep(i,0,sz(poly)) {
        P cur = poly[i], prev = i ? poly[i-1] : poly.back();
        bool side = s.cross(e, cur) < 0;
        if (side != (s.cross(e, prev) < 0))
            res.push_back(lineInter(s, e, cur, prev).second);
        if (side)
            res.push_back(cur);
    }
    return res;
}
#undef P
/**
* Author: Ulf Lundstrom
* Date: 2009-04-08
* License: CC0
* Source:
* Description: Returns the center of mass for a polygon.
* Time: O(n)
* Status: Tested
*/
#define P Point<double>
P polygonCenter(const vector<P>& v) {
    P res(0, 0); double A = 0;
    for (int i = 0, j = sz(v) - 1; i < sz(v); j = i++) {
        res = res + (v[i] + v[j]) * v[j].cross(v[i]);
        A += v[j].cross(v[i]);
    }
    return res / A / 3;
}
#undef P
/**
* Author: Ulf Lundstrom
* Date: 2009-03-21
* License: CC0
* Source: tinyKACTL
* Description: Returns twice the signed area of a polygon.
*  Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
* Status: Stress-tested and tested on kattis:polygonarea
*/
template<class T>
T polygonArea2(vector<Point<T>>& v) {
    T a = v.back().cross(v[0]);
    rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
    return a;
}
/**
* Author: Victor Lecomte, chilli
* Date: 2019-04-26
* License: CC0
* Source: https://vlecomte.github.io/cp-geo.pdf
* Description: Returns true if p lies within the polygon. If strict is true,
* it returns false for points on the boundary. The algorithm uses
* products in intermediate steps so watch out for overflow.
* Time: O(n)
* Usage:
* vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
* bool in = inPolygon(v, P{3, 3}, false);
* Status: stress-tested and tested on kattis:pointinpolygon
*/
template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
    int cnt = 0, n = sz(p);
    rep(i,0,n) {
        P q = p[(i + 1) % n];
        if (onSegment(p[i], q, a)) return !strict;
        //or: if (segDist(p[i], q, a) <= eps) return !strict;
        cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
}
/**
* Author: Stjepan Glavina, chilli
* Date: 2019-05-05
* License: Unlicense
* Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
* Description:
Returns a vector of the points of the convex hull in counter-clockwise order.
Points on the edge of the hull between two other points are not considered part of the hull.
* Time: O(n \log n)
* Status: stress-tested, tested with kattis:convexhull
*/
#define P Point<long long>
vector<P> convexHull(vector<P> pts) {
    if (sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<P> h(sz(pts)+1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(all(pts)))
        for (P p : pts) {
            while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
#undef P
/**
* Author: chilli
* Date: 2019-05-17
* License: CC0
* Source: https://github.com/ngthanhtrung23/ACM_Notebook_new
* Description: Determine whether a point t lies inside a convex hull (CCW
* order, with no collinear points). Returns true if point lies within
* the hull. If strict is true, points on the boundary aren't included.
* Usage:
* Status: stress-tested
* Time: O(\log N)
*/
#define P Point<long long>
bool inHull(const vector<P>& l, P p, bool strict = true) {
    int a = 1, b = sz(l) - 1, r = !strict;
    if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
    if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
    if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
        return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
    }
    return sgn(l[a].cross(l[b], p)) < r;
}
#undef P
/**
* Author: Oleksandr Bacherikov, chilli
* Date: 2019-05-05
* License: Boost Software License
* Source: https://codeforces.com/blog/entry/48868
* Description: Returns the two points with max distance on a convex hull (ccw,
* no duplicate/collinear points).
* Status: stress-tested, tested on kattis:roberthood
*/
#define P Point<long long>
array<P, 2> hullDiameter(vector<P> S) {
    int n = sz(S), j = n < 2 ? 0 : 1;
    pair<ll, array<P, 2>> res({0, {S[0], S[0]}});
    rep(i,0,j)
        for (;; j = (j + 1) % n) {
            res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
            if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
                break;
        }
    return res.second;
}
#undef P
/**
* Author: Oleksandr Bacherikov, chilli
* Date: 2019-05-07
* License: Boost Software License
* Source: https://github.com/AlCash07/ACTL/blob/master/include/actl/geometry/algorithm/intersect/line_convex_polygon.hpp
* Description: Line-convex polygon intersection. The polygon must be ccw and have no collinear points.
* lineHull(line, poly) returns a pair describing the intersection of a line with the polygon:
*    (-1, -1) if no collision,
*    (i, -1) if touching the corner $i$,
*    (i, i) if along side $(i, i+1)$,
*    (i, j) if crossing sides $(i, i+1)$ and $(j, j+1)$.
*  In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$.
*  The points are returned in the same order as the line hits the polygon.
* extrVertex returns the point of a hull with the max projection onto a line.
* Time: O(\log n)
* Status: stress-tested
*/
#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template <class P> int extrVertex(vector<P>& poly, P dir) {
    int n = sz(poly), lo = 0, hi = n;
    if (extr(0)) return 0;
    while (lo + 1 < hi) {
        int m = (lo + hi) / 2;
        if (extr(m)) return m;
        int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
        (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
    }
    return lo;
}
#define cmpL(i) sgn(a.cross(poly[i], b))
template <class P>
array<int, 2> lineHull(P a, P b, vector<P>& poly) {
    int endA = extrVertex(poly, (a - b).perp());
    int endB = extrVertex(poly, (b - a).perp());
    if (cmpL(endA) < 0 || cmpL(endB) > 0)
        return {-1, -1};
    array<int, 2> res;
    rep(i,0,2) {
        int lo = endB, hi = endA, n = sz(poly);
        while ((lo + 1) % n != hi) {
            int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
            (cmpL(m) == cmpL(endB) ? lo : hi) = m;
        }
        res[i] = (lo + !cmpL(hi)) % n;
        swap(endA, endB);
    }
    if (res[0] == res[1]) return {res[0], -1};
    if (!cmpL(res[0]) && !cmpL(res[1]))
        switch ((res[0] - res[1] + sz(poly) + 1) % sz(poly)) {
            case 0: return {res[0], res[0]};
            case 2: return {res[1], res[1]};
        }
    return res;
}
#undef cmpL
#undef extr
#undef cmp