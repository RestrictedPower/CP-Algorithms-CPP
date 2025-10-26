class DSU {
    std::vector<int> parent;

public:
    DSU(int n) {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int p_i = find(i);
        int p_j = find(j);
        if (p_i == p_j) {
            return false;
        }
        parent[p_i] = p_j;
        return true;
    }
};