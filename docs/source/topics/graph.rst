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


