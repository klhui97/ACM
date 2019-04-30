Example 
=======

Geog
----

Convex Quadrangles
++++++++++++++++++

| Given n points in a plane
| How many convex quadrangles you can construct?

.. code-block:: cpp

    #define PI M_PI
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

    int dblcmp(double x) {
        return (x < -eps ? -1 : x > eps);
    }

    ll C(int a, int b)
    {
        ll aa = a, bb = b, ans = 1;
        for (int i = 0; i < b; i++)ans *= (aa - i);
        for (int i = 2; i <= b; i++)ans /= i;
        return ans;
    }

    double ans[2000];
    point_t p[700];

    void mainFunction()
    {
        int t;
        cin >> t;
        while (t--)
        {
            int n;
            cin >> n;
            for (int i = 0; i < n; i++) {
                cin >> p[i].x >> p[i].y;
            }
            long long re=0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j == i)
                        continue;
                    double tmp = atan2(p[j].y - p[i].y, p[j].x - p[i].x);
                    if (dblcmp(tmp) <= 0)
                        tmp += 2 * PI;
                    j < i ? ans[j] = tmp : ans[j - 1] = tmp;
                }
                sort(ans, ans + n - 1);
                int k = 1;
                long long re2 = 0;
                for (int j = 0; j < n - 1; j++)
                    ans[j + n - 1] = ans[j] + 2 * PI;
                for (int j = 0; j < n - 1; j++) {
                    while (fabs(ans[k] - ans[j]) - PI < 0) {
                        k++;
                    }
                    if (k - j - 1 >= 2)
                        re2 += C(k - j - 1, 2);
                }
                re += C(n - 1, 3) - re2;
            }
            printf("%lld\n", C(n, 4) - re);
        }
    }

Maximum Flow
------------

546E - Soldier and Traveling
++++++++++++++++++++++++++++

| In the country there are n cities and m bidirectional roads between them. Each city has an army. Army of the i-th city consists of ai soldiers. Now soldiers roam. After roaming each soldier has to either stay in his city or to go to the one of neighboring cities by at moving along at most one road.
| Check if is it possible that after roaming there will be exactly bi soldiers in the i-th city.

| **Input**
| First line of input consists of two integers n and m (1 ≤ n ≤ 100, 0 ≤ m ≤ 200).
| Next line contains n integers a1, a2, ..., an (0 ≤ ai ≤ 100).
| Next line contains n integers b1, b2, ..., bn (0 ≤ bi ≤ 100).
| Then m lines follow, each of them consists of two integers p and q (1 ≤ p, q ≤ n, p ≠ q) denoting that there is an undirected road between cities p and q.
| It is guaranteed that there is at most one road between each pair of cities.

| **Output**
| If the conditions can not be met output single word "NO".
|  Otherwise output word "YES" and then n lines, each of them consisting of n integers. Number in the i-th line in the j-th column should denote how many soldiers should road from city i to city j (if i ≠ j) or how many soldiers should stay in city i (if i = j).
| If there are several possible answers you may output any of them.

| The solution is used dinic algorithm

Sample input

.. code-block::

    4 4
    1 2 6 3
    3 5 3 1
    1 2
    2 3
    3 4
    4 2

Sample output

.. code-block::

    YES
    1 0 0 0
    2 0 0 0
    0 2 3 1
    0 3 0 0

.. code-block:: cpp

    int ans[maxn][maxn];
    void compute(int u, int n) {
        
        for (int e = h[u]; e != -1; e = edge[e].nxt) {
            int v = edge[e].v;
            if (f[e] < 0 && v <= n && v > 0) {
                ans[v][u - n] = -1 * f[e];
            }
        }
    }

    void mainFunction()
    {
        int n, m;
        int v, u;
        while(cin >> n >> m){
            init();
            int sum = 0;
            int summ = 0;
            int s = 0, t = 250;
            for (int i = 1; i <= n; i++) {
                cin >> v;
                summ += v;
                addEdge(s, i, v);
                addEdge(i, i + n, INF);
            }
            for (int i = 1; i <= n; i++) {
                cin >> v;
                sum += v;
                addEdge(i + n, t, v);
            }
            for (int i = 1; i <= m; i++) {
                cin >> v >> u;
                addEdge(v, u + n, INF);
                addEdge(u, v + n, INF);
            }
            if (summ != sum) {
                cout << "NO\n";
                continue;
            }
            int flow = maxFlow(s, t);
            if (flow != sum) {
                cout << "NO\n";
            }else {
                cout << "YES\n";
                memset(ans, 0, sizeof ans);
                for (int i = 1; i <= n; i++) {
                    compute(n + i, n);
                }
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j < n; j++) {
                        cout << ans[i][j] << " ";
                    }
                    cout << ans[i][n] << "\n";
                }
            }
        }
    }