Graph
=====

Graph Traversal
---------------

Breadth First Search (BFS)
++++++++++++++++++++++++++

https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

.. code-block:: cpp

    int V;
    list<int> *adj;

    void addEdge(int v, int w) 
    { 
        adj[v].push_back(w);
    } 

    void bfs(int s) {

        bool *visited = new bool[V]; 
        for(int i = 0; i < V; i++) 
            visited[i] = false; 

        list<int> queue; 

        visited[s] = true; 
        queue.push_back(s); 

        list<int>::iterator i; 
    
        while(!queue.empty()) 
        {
            s = queue.front(); 
            cout << s << " "; 

            queue.pop_front();
            for (i = adj[s].begin(); i != adj[s].end(); ++i) 
            { 
                if (!visited[*i]) 
                { 
                    visited[*i] = true; 
                    queue.push_back(*i); 
                } 
            } 
        }
        cout << "\n";
    }

Example:

.. code-block:: cpp

    V = 4;
    adj = new list<int>[V];
    addEdge(0, 1); 
    addEdge(0, 2); 
    addEdge(1, 2); 
    addEdge(2, 0); 
    addEdge(2, 3); 
    addEdge(3, 3); 

    bfs(2);

Topological Sorting
+++++++++++++++++++

https://www.geeksforgeeks.org/topological-sorting/

Code:

.. code-block:: cpp

    class Graph 
    { 
        int V;
        list<int> *adj;
        void topologicalSortUtil(int v, bool visited[], stack<int> &Stack); 
    public: 
        Graph(int V);
        void addEdge(int v, int w);
        void topologicalSort(); 
    }; 
    
    Graph::Graph(int V) 
    { 
        this->V = V; 
        adj = new list<int>[V]; 
    } 
    
    void Graph::addEdge(int v, int w) 
    { 
        adj[v].push_back(w);
    } 

    void Graph::topologicalSortUtil(int v, bool visited[],  
                                    stack<int> &Stack) 
    { 
        visited[v] = true; 

        list<int>::iterator i; 
        for (i = adj[v].begin(); i != adj[v].end(); ++i) 
            if (!visited[*i]) 
                topologicalSortUtil(*i, visited, Stack); 
    
        Stack.push(v); 
    } 

    void Graph::topologicalSort() 
    { 
        stack<int> Stack; 
        bool *visited = new bool[V]; 
        for (int i = 1; i < V; i++) 
            visited[i] = false; 

        for (int i = 1; i < V; i++) 
        if (visited[i] == false) 
            topologicalSortUtil(i, visited, Stack); 

        while (Stack.empty() == false) 
        { 
            cout << Stack.top(); 
            Stack.pop(); 
            if (Stack.empty() == false) {
                cout << " ";
            }
        }
        cout << endl;
    }

Example:

.. code-block:: cpp

    Graph g(4); 
    g.addEdge(0, 1); 
    g.addEdge(0, 2); 
    g.addEdge(1, 2); 
    g.addEdge(2, 0); 
    g.addEdge(2, 3); 
    g.addEdge(3, 3); 

    cout << "Following is Breadth First Traversal "
            << "(starting from vertex 2) \n"; 
    g.BFS(2);

Shorest Path
------------

Floyd- Warshall algorithm
+++++++++++++++++++++++++

* k is the intermedia point
* if i -> k + k -> j is smaller than i -> j
* i -> k + k -> j becomes the shorest path

.. code-block:: cpp
    
    for(k = 1; k < N; k++) {
        for(i = 1; i < N; i++) {
            for(j = 1; j < N; j++) {
                if(graph[i][j] == 0 || graph[i][j] > graph[i][k] + graph[k][j]) {
                    if(graph[i][k] && graph[k][j])
                        graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }

Dijkstra’s algorithm
++++++++++++++++++++

Code:

.. code-block:: cpp

    typedef pair<int, int> iPair;
    struct node {
        int v;
        int distance;

        node(int v, int distance) :v(v), distance(distance) {};

        bool operator < (const node n2) const {
            return distance > n2.distance;
        }
    };
    class Graph
    {
        int V;
        list< pair<int, int> > *adj;

    public:
        Graph(int V);
        void addEdge(int u, int v, int w);
        void shortestPath(int s);
    };

    Graph::Graph(int V)
    {
        this->V = V;
        adj = new list<iPair> [V];
    }

    void Graph::addEdge(int u, int v, int w)
    {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    void Graph::shortestPath(int src)
    {
        priority_queue<node> pq;
        // Create a vector for distances and initialize all
        // distances as infinite (INF)
        int dist[V + 1];
        memset(dist, INF, sizeof dist);

        pq.push(node(src, 0));
        dist[src] = 0;

        while (!pq.empty())
        {
            // The first vertex in pair is the minimum distance
            // vertex, extract it from priority queue.
            // vertex label is stored in second of pair (it
            // has to be done this way to keep the vertices
            // sorted distance (distance must be first item
            // in pair)
            int u = pq.top().v;
            pq.pop();

            // 'i' is used to get all adjacent vertices of a vertex
            list< pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                int v = (*i).first;
                int weight = (*i).second;

                //  If there is shorted path to v through u.
                if (dist[v] > dist[u] + weight)
                {
                    // Updating distance of v
                    dist[v] = dist[u] + weight;
                    pq.push(node(v, dist[v]));
                }
            }
        }

        // Print shortest distances stored in dist[]
        printf("Vertex   Distance from Source\n");
        for (int i = 0; i < V; ++i)
            printf("%d \t\t %d\n", i, dist[i]);
    }

Example:

.. code-block:: cpp

    int V = 9; 
    Graph g(V); 

    //  making above shown graph 
    g.addEdge(0, 1, 4); 
    g.addEdge(0, 7, 8); 
    g.addEdge(1, 2, 8); 
    g.addEdge(1, 7, 11); 
    g.addEdge(2, 3, 7); 
    g.addEdge(2, 8, 2); 
    g.addEdge(2, 5, 4); 
    g.addEdge(3, 4, 9); 
    g.addEdge(3, 5, 14); 
    g.addEdge(4, 5, 10); 
    g.addEdge(5, 6, 2); 
    g.addEdge(6, 7, 1); 
    g.addEdge(6, 8, 6); 
    g.addEdge(7, 8, 7); 

    g.shortestPath(0);

ans:

.. code-block:: cpp

    Vertex   Distance from Source
    0                0
    1                4
    2                12
    3                19
    4                21
    5                11
    6                9
    7                8
    8                14

Minimum Spanning Tree
---------------------

Kruskal’s algorithm
+++++++++++++++++++

Time complexity: E log E

Code:

.. code-block:: cpp

    typedef  pair<int, int> iPair;
    int V, E; 
    vector< pair<int, iPair> > edges; 

    void addEdge(int u, int v, int w) 
    { 
        edges.push_back(make_pair(w, make_pair(u, v))); 
    }
    
    struct DisjointSets 
    { 
        int *parent, *rnk; 
        int n; 
    
        // Constructor. 
        DisjointSets(int n) 
        { 
            // Allocate memory 
            this->n = n; 
            parent = new int[n+1]; 
            rnk = new int[n+1]; 

            for (int i = 0; i <= n; i++) 
            { 
                rnk[i] = 0; 
                parent[i] = i; 
            } 
        } 

        int find(int u) 
        {
            if (u != parent[u]) 
                parent[u] = find(parent[u]); 
            return parent[u]; 
        } 

        void merge(int x, int y) 
        { 
            x = find(x), y = find(y); 
            if (rnk[x] > rnk[y]) 
                parent[y] = x; 
            else
                parent[x] = y; 
    
            if (rnk[x] == rnk[y]) 
                rnk[y]++; 
        } 
    }; 

    int kruskalMST() 
    { 
        int mst_wt = 0;
        int cnt = 0;
        sort(edges.begin(), edges.end()); 
        DisjointSets ds(V);

        vector< pair<int, iPair> >::iterator it;
        for (it=edges.begin(); it!=edges.end(); it++) 
        { 
            int u = it->second.first; 
            int v = it->second.second; 
    
            int set_u = ds.find(u); 
            int set_v = ds.find(v); 

            if (set_u != set_v) 
            {
                cout << u << " - " << v << " cost: " << it->first << "\n"; 
                mst_wt += it->first; 
                ds.merge(set_u, set_v);
                cnt++;
                if (cnt == V - 1)
                    break;
            }
        } 
        cout << "Weight of MST is " << mst_wt << "\n";
        // Clear after finished
        edges.clear();
        if (cnt == V - 1)
            return mst_wt;
        else
            return -1; // Cannot find mst
    }

Example:

.. code-block:: cpp

    V = 9;
    E = 14;
    addEdge(0, 1, 4); 
    addEdge(0, 7, 8); 
    addEdge(1, 2, 8); 
    addEdge(1, 7, 11); 
    addEdge(2, 3, 7); 
    addEdge(2, 8, 2); 
    addEdge(2, 5, 4); 
    addEdge(3, 4, 9); 
    addEdge(3, 5, 14); 
    addEdge(4, 5, 10); 
    addEdge(5, 6, 2); 
    addEdge(6, 7, 1);
    addEdge(6, 8, 6); 
    addEdge(7, 8, 7);
    cout << "Edges of MST are \n"; 
    int mst_wt = kruskalMST();
    cout << "\nMST: " << mst_wt << "\n";


Prim’s Algorithm
++++++++++++++++

Time complexity: O(VlogV + ElogV) = O(ElogV)

Code:

.. code-block:: cpp

    int V;

    int minKey(int key[], bool mstSet[])  {
        int min = INT_MAX, min_index; 
        
        for (int v = 0; v < V; v++) 
            if (mstSet[v] == false && key[v] < min) 
                min = key[v], min_index = v; 
        
        return min_index; 
    }

    int primMST(int graph[maxn][maxn])  {
        int parent[V];
        int key[V];
        bool mstSet[V];

        for (int i = 0; i < V; i++) 
            key[i] = INT_MAX, mstSet[i] = false; 

        key[0] = 0;      
        parent[0] = -1;

        for (int count = 0; count < V-1; count++) 
        {
            int u = minKey(key, mstSet);
            mstSet[u] = true; 
            for (int v = 0; v < V; v++)  
                if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
                parent[v] = u, key[v] = graph[u][v]; 
        }

        int w = 0;
        printf("Edge \tWeight\n"); 
        for (int i = 1; i < V; i++) {
            if (graph[i][parent[i]] == INT_MAX)
                return -1; // not a mst
            w += graph[i][parent[i]];
            printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
        }
        return w;
    }

Example:

.. code-block:: cpp

    int cost[maxn][maxn] = { 
        { INT_MAX, 2, INT_MAX, 6, INT_MAX }, 
        { 2, INT_MAX, 3, 8, 5 }, 
        { INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX }, 
        { 6, 8, INT_MAX, INT_MAX, 9 }, 
        { INT_MAX, 5, 7, 9, INT_MAX }, 
    }; 

    cout << primMST(cost) << "\n"; // -1 is returned (undefine case)

    int cost2[maxn][maxn] = { 
        { INT_MAX, 2, INT_MAX, 6, INT_MAX }, 
        { 2, INT_MAX, 3, 8, 5 }, 
        { INT_MAX, 3, INT_MAX, INT_MAX, 7 }, 
        { 6, 8, INT_MAX, INT_MAX, 9 }, 
        { INT_MAX, 5, 7, 9, INT_MAX }, 
    }; 

    cout << primMST(cost2) << "\n"; // 16 is returned

Maxflow
-------

Edmonds-Karp Algorithm
++++++++++++++++++++++

Time complexity: O(VE^2)
Code:

.. code-block:: cpp

    typedef pair<int, int> pii;
    typedef vector<int> vi;
    typedef vector<pii> vpii;
    #define maxn 105
    
    int res[maxn][maxn], maxflow, f, ss, tt;
    vector<vi> adj;
    vi p;

    int n;

    void augment(int v, int minEdge) {
        if (v == ss) {
            f = minEdge;
            return;
        } else if (p[v] != -1) {
            augment(p[v], min(minEdge, res[p[v]][v]));
            res[p[v]][v] -= f;
            res[v][p[v]] += f;
        }
    }

    void EdmondKarps() {
        maxflow = 0;
        while (1) {
            f = 0;
            bitset<maxn> visited;
            visited.set(ss);
            queue<int> q;
            q.push(ss);
            p.assign(maxn, -1);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                if (u == tt)
                    break;
                for (int i = 0; i < (int) adj[u].size(); i++) {
                    int v = adj[u][i];
                    if (res[u][v] > 0 && !visited.test(v)) {
                        visited.set(v);
                        q.push(v);
                        p[v] = u;
                    }
                }
            }
            augment(tt, INF);
            if (f == 0)
                break;
            maxflow += f;
        }
    }

    void addEdge(int v, int u, int w) {
        res[v][u] += w;
        adj[v].push_back(u);
    }

    void init(int n) {
        memset(res, 0, sizeof res);
        adj.assign(n, vi());
    }

Example:

.. code-block:: cpp

    n = 5;
    ss = 1;
    tt = 4;
    init(n);
    addEdge(1, 2, 20);
    addEdge(1, 3, 10);
    addEdge(2, 3, 5);
    addEdge(2, 4, 10);
    addEdge(3, 4, 20);

    EdmondKarps();
    cout << maxflow << endl;

Dinic's algorithm
+++++++++++++++++

Time complexity: O(EV^2)
Code:

.. code-block:: cpp

    #define INTT long long
    struct Edge {
        int v;     // edge (u->v)
        INTT c;  // edge cacity (w)
        int nxt;  // the next edge connected by node u.
    };
    int edges;
    Edge edge[maxw];
    int d[maxn];
    int f[maxw], h[maxw];

    void addEdge(int u, int v, INTT c) {
        edge[edges].nxt = h[u];
        edge[edges].v = v;
        edge[edges].c = c;
        h[u] = edges;
        edges++;
        edge[edges].nxt = h[v];
        edge[edges].v = u;
        edge[edges].c = 0;
        h[v] = edges;
        edges++;
    }
    void init() {
        edges = 0;
        memset(h, -1, sizeof(h));
        memset(f, 0, sizeof(f));
    }

    bool bfs(int S, int T) {
        int u, v;
        memset(d, -1, sizeof(d));
        queue<int> Q;
        while (!Q.empty())
            Q.pop();
        Q.push(S);
        d[S] = 0;
        while (!Q.empty()) {
            u = Q.front();
            Q.pop();
            for (int e = h[u]; e != -1; e = edge[e].nxt) {
                v = edge[e].v;

                if ((d[v] == -1) && edge[e].c > f[e]) {
                    d[v] = d[u] + 1;
                    Q.push(v);
                }
            }
        }
        return d[T] >= 0;
    }

    INTT dinic(int u, int T, INTT sum) {
        if (u == T) 
            return sum;
        int v, tp = sum;
        for (int e = h[u]; e != -1 && sum; e = edge[e].nxt) {
            v = edge[e].v;
            if (d[v] == d[u] + 1 && edge[e].c>f[e]) {
                ll toflow = dinic(v, T, min(sum, edge[e].c - f[e]));
                f[e] += toflow;
                f[e ^ 1] -= toflow;
                sum -= toflow;
            }
        }
        return tp - sum;
    }

    INTT maxFlow(int s, int t) {
        INTT ans = 0;
        while (bfs(s, t))
            ans += dinic(s, t, INF);
        return ans;
    }

    // dfs, find vertexs that haven't flowout
    int cnt;
    int visited[maxn];
    void dfs(int u) {
        cnt++;
        visited[u] = 1;
        int v;
        for (int e = h[u]; e != -1; e = edge[e].nxt) {
            v = edge[e].v;
            if (edge[e].c - f[e]>0 && !visited[v]) {
                dfs(v);
            }
        }
    }

Example:

.. code-block:: cpp

    init();
    int s = 0, t = 5;
    addEdge(0, 1, 16 ); 
    addEdge(0, 2, 13 ); 
    addEdge(1, 2, 10 ); 
    addEdge(1, 3, 12 ); 
    addEdge(2, 1, 4 ); 
    addEdge(2, 4, 14); 
    addEdge(3, 2, 9 ); 
    addEdge(3, 5, 20 ); 
    addEdge(4, 3, 7 ); 
    addEdge(4, 5, 4); 
    cout << maxFlow(s, 5) << endl;