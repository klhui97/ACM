Graph
=====

Graph Traversal
---------------

DFS & BFS
+++++++++

.. code-block:: cpp

    int V;
    list<int> *adj;

    struct node {
        int v;
        int distance;

        node(int v, int distance) :v(v), distance(distance) {};
    };

    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }

    void bfs(int s) {

        bool visited[V];
        memset(visited, false, sizeof visited);

        list<node> queue;
        queue.push_back(node(s, 0));

        visited[s] = true;

        list<int>::iterator i;

        while(!queue.empty())
        {
            int v = queue.front().v;
            int d =  queue.front().distance;
            queue.pop_front();

            cout << v << " ";

            for (i = adj[v].begin(); i != adj[v].end(); ++i)
            {
                int u = *i;
                if (!visited[u]) {
                    visited[u] = true;
                    queue.push_back(node(u, d + 1));
                }
            }
        }
        cout << "\n";
    }
    void dfs(int s) 
    { 
        bool visited[V];
        memset(visited, false, sizeof visited);

        stack<node> stack; 
        stack.push(node(s, 0)); 

        visited[s] = true;

        list<int>::iterator i;

        while (!stack.empty()) 
        {
            int v = stack.top().v; 
            int d = stack.top().distance;
            stack.pop();

            cout << v << " "; 
            
            for (i = adj[v].begin(); i != adj[v].end(); ++i) {
                int u = *i;
                    
                if (!visited[u]) {
                    visited[u] = true;
                    stack.push(node(u, d + 1)); 
                }
            }
                
        } 
        cout << "\n";
    }

Example:

.. code-block:: cpp

    V = 5;
    adj = new list<int>[V];
    addEdge(1, 0); 
    addEdge(0, 2); 
    addEdge(2, 1); 
    addEdge(0, 3); 
    addEdge(1, 4); 

    cout << "Following is DFS Traversal\n"; 
    dfs(0); 
    cout << "Following is BFS Traversal\n"; 
    bfs(0);

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

    struct edge {
        int v, u, w;

        edge(int v, int u, int w) :v(v), u(u), w(w) {};

        bool operator < (const edge n2) const {
            return w > n2.w;
        }
    };

    priority_queue<edge> pq;

    void addEdge(int u, int v, int w)
    {
        pq.push(edge(u, v, w));
    }

    struct DisjointSets
    {
        int *parent, *rnk;
        int n;

        DisjointSets(int n)
        {
            this->n = n;
            parent = new int[n+1];
            rnk = new int[n+1];
            
            reset();
        }

        void reset() {
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
        DisjointSets ds(V);

        while(!pq.empty()){

            int u = pq.top().u; 
            int v = pq.top().v;
            int w = pq.top().w;
            pq.pop(); 

            int set_u = ds.find(u); 
            int set_v = ds.find(v); 

            if (set_u != set_v) 
            {
                cout << u << " - " << v << " cost: " << w << "\n"; 
                mst_wt += w; 
                ds.merge(set_u, set_v);
                cnt++;
                if (cnt == V - 1)
                    break;
            }
        } 
        pq = priority_queue <edge>(); // reset edges after completed

        cout << "Weight of MST is " << mst_wt << "\n";

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
    int src;

    typedef pair<int, int> iPair; 
    list< pair<int, int> > *adj; 

    void addEdge(int u, int v, int w) { 
        adj[u].push_back(make_pair(v, w)); 
        adj[v].push_back(make_pair(u, w)); 
    }

    int primMST()  {
        priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
        vector<int> dist(V, INF);
        vector<int> parent(V, -1);
        vector<bool> inMST(V, false);
        pq.push(make_pair(0, src)); 
        dist[src] = 0; 
    
        while (!pq.empty()) 
        {
            int u = pq.top().second; 
            pq.pop(); 
    
            inMST[u] = true;
            list< pair<int, int> >::iterator i; 
            for (i = adj[u].begin(); i != adj[u].end(); ++i) 
            {
                int v = (*i).first; 
                int weight = (*i).second; 

                if (inMST[v] == false && dist[v] > weight) 
                {
                    dist[v] = weight; 
                    pq.push(make_pair(dist[v], v)); 
                    parent[v] = u; 
                } 
            } 
        }
        
        int sum = 0;
        for (int i = 0; i < V; ++i) {
            if (i != src) {
                if (dist[i] == INF) {
                    sum = dist[i];
                    break;
                }
                printf("%d - %d    %d\n", parent[i], i, dist[i]);
                sum += dist[i];
            }
        }
            
        return sum;
    }

| Example:
| src: starting vertex
| V: vertexs are indexed as 0...V-1

.. code-block:: cpp

    src = 3;
    V = 9;
    adj = new list<iPair> [V];
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
    cout << primMST() << "\n";

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

    // analysis vertex
    void searchFlow(int vertex) {
        for (int e = h[vertex]; e != -1; e = edge[e].nxt) {
            int v = edge[e].v;
            int c = edge[e].c;

            if (c == 0) {
                cout << v << " flowed from " << vertex << " with flowed value = " << f[e] << "\n";
            }else {
                cout << vertex << " flowed to " << v << " capacity = " << c << " flowed value = " << f[e] << "\n";
                if (c - f[e] == 0)
                    cout << vertex << " completely flowed to " << v << "\n";
            }
            
        }
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