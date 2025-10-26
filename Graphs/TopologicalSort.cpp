class TopologicalSort {
public:
    explicit TopologicalSort(int node_count)
        : n(node_count), adj(n), has_been_run(false) {
    }

    void add_edge(int u, int v) {
        if (has_been_run) {
            throw std::runtime_error("Cannot add edges after computation has been run.");
        }
        adj[u].push_back(v);
    }

    const std::vector<int> &get_topological_order() {
        ensure_run();
        if (!is_dag()) {
            throw std::runtime_error("Graph has a cycle; topological sort is not possible.");
        }
        return sorted_order;
    }

    bool is_dag() {
        ensure_run();
        return sorted_order.size() == n;
    }

private:
    int n;
    std::vector<std::vector<int> > adj;

    bool has_been_run;
    std::vector<int> sorted_order;

    void ensure_run() {
        if (!has_been_run) {
            run_computation();
        }
    }

    void run_computation() {
        std::vector<int> in_degree(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int neighbor: adj[i]) {
                in_degree[neighbor]++;
            }
        }

        std::queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        sorted_order.reserve(n);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            sorted_order.push_back(u);

            for (int v: adj[u]) {
                if (--in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }
        has_been_run = true;
    }
};