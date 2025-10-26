class SCC {
public:
    SCC(int n) : n(n), adj(n), adj_t(n), vis(n, false), has_been_run(false) {
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj_t[v].push_back(u);
    }

    const std::vector<std::vector<int> > &get_SCC() {
        run();
        return scc_components;
    }

    // Mapping from a node to its SCC ID
    const std::vector<int> &node_to_scc_id_map() {
        run();
        return scc_parent;
    }

    // Mapping from an SCC ID to its nodes
    const std::vector<std::vector<int> > &scc_id_to_nodes_map() {
        run();
        return scc_components;
    }

    // Function to create the acyclic condensation graph of the SCCs
    std::vector<std::unordered_set<int> > condensation_graph() {
        run();
        std::vector<std::unordered_set<int> > compressed_adj(scc_components.size());
        for (int i = 0; i < n; i++) {
            for (int to: adj[i]) {
                if (scc_parent[i] != scc_parent[to]) {
                    compressed_adj[scc_parent[i]].insert(scc_parent[to]);
                }
            }
        }
        return compressed_adj;
    }

private:
    int n;
    std::vector<std::vector<int> > adj;
    std::vector<std::vector<int> > adj_t;
    std::vector<bool> vis;

    bool has_been_run;
    std::vector<std::vector<int> > scc_components;
    std::vector<int> scc_parent;

    void dfs1(int i, std::stack<int> &s) {
        vis[i] = true;
        for (int to: adj[i]) {
            if (!vis[to]) {
                dfs1(to, s);
            }
        }
        s.push(i);
    }

    void dfs2(int i, std::vector<int> &component, int scc_idx) {
        vis[i] = true;
        component.push_back(i);
        scc_parent[i] = scc_idx;
        for (int to: adj_t[i]) {
            if (!vis[to]) {
                dfs2(to, component, scc_idx);
            }
        }
    }

    void run() {
        if (has_been_run) {
            return;
        }
        std::stack<int> s;
        std::fill(vis.begin(), vis.end(), false);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs1(i, s);
            }
        }

        scc_parent.assign(n, -1);
        std::fill(vis.begin(), vis.end(), false);
        int scc_idx = 0;
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            if (!vis[v]) {
                std::vector<int> currentSCC;
                dfs2(v, currentSCC, scc_idx++);
                scc_components.push_back(currentSCC);
            }
        }
        has_been_run = true;
    }
};