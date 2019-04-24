Computational Geometry
======================

Basic
-----

.. code-block:: cpp

    #define eps 1e-6

    struct point_t {
        double x, y;
        point_t() { }
        point_t(double tx, double ty) : x(tx), y(ty) { }
        point_t operator-(const point_t &r) const { return point_t(x - r.x, y - r.y); }
        point_t operator+(const point_t &r) const { return point_t(x + r.x, y + r.y); }
        point_t operator*(double r) const { return point_t(x * r, y * r); }
        point_t operator/(double r) const { return point_t(x / r, y / r); }
        point_t rot90() const { return point_t(-y, x); }
        double l() const { return sqrt(x * x + y * y); }
    };

    double dot(point_t p1, point_t p2) {
        return p1.x * p2.x + p1.y * p2.y;
    }

    int dblcmp(double x) {
        return (x < -eps ? -1 : x > eps);
    }

    double cross(point_t p1, point_t p2) {
        return p1.x * p2.y - p2.x * p1.y;
    }

    bool onSeg(point_t p, point_t a, point_t b) {
        return dblcmp(cross(a - p, b - p)) == 0 && dblcmp(dot(a - p, b - p)) <= 0;
    }

    double dist(point_t p1, point_t p2) {
        return (p2 - p1).l();
    }

    // 1 normal intersected, -1 denormal intersected, 0 not intersected
    int testSS(point_t a, point_t b, point_t c, point_t d) {
        if (dblcmp(max(a.x, b.x) - min(c.x, d.x)) < 0) return 0;
        if (dblcmp(max(c.x, d.x) - min(a.x, b.x)) < 0) return 0;
        if (dblcmp(max(a.y, b.y) - min(c.y, d.y)) < 0) return 0;
        if (dblcmp(max(c.y, d.y) - min(a.y, b.y)) < 0) return 0;
        int d1 = dblcmp(cross(c - a, b - a));
        int d2 = dblcmp(cross(d - a, b - a));
        int d3 = dblcmp(cross(a - c, d - c));
        int d4 = dblcmp(cross(b - c, d - c));
        if ((d1 * d2 < 0) && (d3 * d4 < 0)) return 1;
        if ((d1 * d2 <= 0 && d3 * d4 == 0) || (d1 * d2 == 0 && d3 * d4 <= 0)) return -1;
        return 0;
    }

    // Important note: points must follow clockwise / anti-cloclwise order
    bool insidePoly(point_t *p, int n, point_t t) {
        p[0] = p[n];
        for (int i = 0; i < n; ++i) if (onSeg(t, p[i], p[i + 1])) return true;
        point_t r = point_t(2353456.663, 5326546.243); // random point
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (testSS(t, r, p[i], p[i + 1]) != 0) ++cnt;
        }
        return cnt & 1;
    }

    // Important note: points must follow clockwise / anti-cloclwise order
    double areaPoly(point_t *p, int n) {
        double sum = 0;
        p[n + 1] = p[1];
        for (int i = 1; i <= n; i++) {
            sum += cross(p[i], p[i + 1]);
        }
            return abs(sum / 2.0);
    }

Convex Hull
-----------

Graham scan
+++++++++++

n points, points are saved from points[1] to points[n]
return: top
p[1] ... p[top] = Convex Hull

.. code-block:: cpp

    bool cmp(const point_t p1, const point_t p2) {
        return dblcmp(p1.y - p2.y) == 0 ? p1.x < p2.x : p1.y < p2.y;
    }

    int graham(point_t *p) {
        int top = 2; static point_t sk[maxn];
        sort(p + 1, p + 1 + n, cmp);
        sk[1] = p[1], sk[2] = p[2];
        for (int i = 3; i <= n; ++i) {
            while (top >= 2 && dblcmp(cross(p[i] - sk[top - 1], sk[top] - sk[top - 1])) >= 0) --top;
            sk[++top] = p[i];
        }
        int ttop = top;
        for (int i = n - 1; i >= 1; --i) {
            while (top > ttop && dblcmp(cross(p[i] - sk[top - 1], sk[top] - sk[top - 1])) >= 0) --top;
            sk[++top] = p[i];
        }
        for (int i = 1; i < top; ++i) p[i] = sk[i];
            return --top;
    }
