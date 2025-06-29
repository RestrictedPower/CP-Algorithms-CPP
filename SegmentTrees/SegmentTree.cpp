
template<typename T>
class SegmentTree {
public:
    SegmentTree(const std::vector<T> &arr, std::function<T(T, T)> op, T identity)
        : op(op), identity(identity) {
        n = arr.size();
        tree.resize(4 * n);
        build_from_array(arr, 1, 0, n - 1);
    }

    SegmentTree(int size, T defaultValue, std::function<T(T, T)> op, T identity)
        : op(op), identity(identity), n(size) {
        tree.resize(4 * n);
        build_with_default(defaultValue, 1, 0, n - 1);
    }

    T query(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }

    void update(int index, T value) {
        update(1, 0, n - 1, index, value);
    }

    static constexpr auto MIN = [](T a, T b) { return std::min(a, b); };
    static constexpr auto MAX = [](T a, T b) { return std::max(a, b); };
    static constexpr auto SUM = [](T a, T b) { return a + b; };

private:
    std::vector<T> tree;
    int n;
    std::function<T(T, T)> op;
    T identity;

    void build_from_array(const std::vector<T> &arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = start + (end - start) / 2;
            build_from_array(arr, 2 * node, start, mid);
            build_from_array(arr, 2 * node + 1, mid + 1, end);
            tree[node] = op(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void build_with_default(T val, int node, int start, int end) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = start + (end - start) / 2;
            build_with_default(val, 2 * node, start, mid);
            build_with_default(val, 2 * node + 1, mid + 1, end);
            tree[node] = op(tree[2 * node], tree[2 * node + 1]);
        }
    }

    T query(int node, int start, int end, int left, int right) {
        if (right < start || end < left || left > right) {
            return identity;
        }
        if (left <= start && end <= right) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        T p1 = query(2 * node, start, mid, left, right);
        T p2 = query(2 * node + 1, mid + 1, end, left, right);
        return op(p1, p2);
    }

    void update(int node, int start, int end, int index, T value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = start + (end - start) / 2;
            if (start <= index && index <= mid) {
                update(2 * node, start, mid, index, value);
            } else {
                update(2 * node + 1, mid + 1, end, index, value);
            }
            tree[node] = op(tree[2 * node], tree[2 * node + 1]);
        }
    }
};