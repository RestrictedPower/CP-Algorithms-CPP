template<typename T_weight = int>
class Dijkstra {
    using edge = std::pair<int, T_weight>;
    using state = std::pair<T_weight, int>;
    using priority_q = priority_queue<state, std::vector<state>, std::greater<state> >;

public:
    const T_weight INF = std::numeric_limits<T_weight>::max();

    Dijkstra(int n) : n(n), adj(n), has_been_run(false) {
    }

    void add_edge(int u, int v, T_weight weight) {
        adj[u].emplace_back(v, weight);
    }

    void run(int src) {
        run_multi_source({src});
    }

    void run_multi_source(const vector<int> &sources) {
        dist.assign(n, INF);
        parent.assign(n, -1);

        priority_q pq;
        for (const int &source: sources) {
            relax(pq, source, -1, 0);
        }

        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();
            if (d > dist[node]) {
                continue;
            }
            for (auto &[to, weight]: adj[node]) {
                relax(pq, to, node, d + weight);
            }
        }
        has_been_run = true;
    }

    const vector<T_weight> &shortest_distances() {
        assert_computed();
        return dist;
    }

    bool path_exists(int d) {
        assert_computed();
        return dist[d] != INF;
    }

    std::vector<int> shortest_path(int d) {
        assert_computed();
        std::vector<int> path;
        for (int current = d; current != -1; current = parent[current]) {
            path.push_back(current);
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    int n;
    std::vector<std::vector<edge> > adj;

    bool has_been_run;
    std::vector<T_weight> dist;
    std::vector<int> parent;

    void relax(priority_q &pq, int node, int from, T_weight distance) {
        if (distance < dist[node]) {
            dist[node] = distance;
            parent[node] = from;
            pq.emplace(distance, node);
        }
    }

    void assert_computed() const {
        if (!has_been_run) {
            throw std::runtime_error("Dijkstra::run() must be called.");
        }
    }
};
