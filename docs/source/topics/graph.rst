Graph
=====

Graph Traversal
^^^^^^^^^^^^^^^

Breadth First Search (BFS)
++++++++++++++++++++++++++

https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

.. code-block:: cpp

    class Graph 
    { 
        int V;
        list<int> *adj;    
    public: 
        Graph(int V);
        void addEdge(int v, int w);
        void BFS(int src);   
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
    
    void Graph::BFS(int src) 
    { 
        bool *visited = new bool[V]; 
        for(int i = 0; i < V; i++) 
            visited[i] = false; 
        list<int> queue; 
        visited[src] = true; 
        queue.push_back(src); 
    
        list<int>::iterator i; 
    
        while(!queue.empty()) 
        { 
            // Dequeue a vertex from queue and print it 
            src = queue.front(); 
            cout << src << " "; 
            queue.pop_front(); 

            for (i = adj[src].begin(); i != adj[src].end(); ++i) 
            { 
                if (!visited[*i]) 
                { 
                    visited[*i] = true; 
                    queue.push_back(*i); 
                } 
            } 
        }
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
^^^^^^^^^^^^

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

    #define INF 0x3f3f3f3f
    typedef pair<int, int> iPair; 
    class Graph 
    { 
        int V;
        list< pair<int, int> > *adj; 
    
    public: 
        Graph(int V);
        void addEdge(int u, int v, int w);
        int shortestPath(int s); 
    }; 

    Graph::Graph(int V) 
    { 
        this->V = V; 
        adj = new list<iPair> [V]; 
    } 
    
    void Graph::addEdge(int from, int to, int w) 
    { 
        adj[from].push_back(make_pair(to, w));
        printf("%d --> %d weight: %d\n", from, to, w);
        adj[to].push_back(make_pair(from, w));
        printf("%d --> %d weight: %d\n", to, from, w);
    } 

    int Graph::shortestPath(int src)
    {
        priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
        vector<int> dist(V, INF);
        pq.push(make_pair(0, src));
        dist[src] = 0;

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            list< pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = (*i).first;
                int weight = (*i).second;
                
                if (dist[v] > dist[u] + weight)
                {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        return dist[1];
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

