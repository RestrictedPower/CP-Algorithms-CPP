template<typename T = ll, typename LazyT = T>
class SegmentTree {
public:
    // Type aliases for clarity
    using MergeOperation = std::function<T(T, T)>;
    using ApplyLazyToValueOperation = std::function<T(T, LazyT, int)>; // node_val, lazy_val, range_size
    using CombineLazyOperation = std::function<LazyT(LazyT, LazyT)>; // old_lazy, new_lazy

    // Constructor
    SegmentTree(int n, T identity,
                MergeOperation merge_op,
                ApplyLazyToValueOperation update_op,
                CombineLazyOperation combine_lazy)
        : n(n), identity(identity),
          merge_values(merge_op), apply_lazy_to_value(update_op), combine_lazy(combine_lazy) {
        tree.assign(4 * n, Node(identity));
    }

    // Constructor with initial array
    SegmentTree(const std::vector<T> &arr,
                T identity,
                MergeOperation merge_op,
                ApplyLazyToValueOperation update_op,
                CombineLazyOperation combine_lazy)
        : n(arr.size()), identity(identity),
          merge_values(merge_op), apply_lazy_to_value(update_op), combine_lazy(combine_lazy) {
        tree.assign(4 * n, Node(identity));
        build(arr, 1, 0, n - 1);
    }

    // Public query method
    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    // Public update method (range update)
    void update(int l, int r, LazyT val) {
        update(1, 0, n - 1, l, r, val);
    }

    void dbg() {
        string res;
        for (int i = 0; i < n; i++) {
            res += to_string(query(i, i)) + ", ";
        }
        res = "[" + res + "]";
        cout << res << endl;
    }

    static constexpr auto MIN = [](T a, T b) { return std::min(a, b); };
    static constexpr auto MAX = [](T a, T b) { return std::max(a, b); };
    static constexpr auto SUM = [](T a, T b) { return a + b; };

private:
    // Node structure to hold value, lazy tag, and a flag indicating if lazy tag is present
    struct Node {
        T value;
        LazyT lazy;
        bool has_lazy; // Boolean flag

        // Constructor for Node
        Node(T val = T{}, LazyT lzy = LazyT{}, bool hl = false)
            : value(val), lazy(lzy), has_lazy(hl) {
        }
    };

    const int n; // Size of the original array
    const T identity; // Default value for tree nodes
    std::vector<Node> tree; // Segment tree nodes

    MergeOperation merge_values; // Function to merge two child nodes
    ApplyLazyToValueOperation apply_lazy_to_value; // Function to apply lazy tag to a node
    CombineLazyOperation combine_lazy; // Function to compose new lazy tag with existing one

    // Builds the segment tree from an array
    void build(const std::vector<T> &arr, int node_idx, int start, int end) {
        if (start == end) {
            tree[node_idx].value = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node_idx, start, mid);
            build(arr, 2 * node_idx + 1, mid + 1, end);
            tree[node_idx].value = merge_values(tree[2 * node_idx].value, tree[2 * node_idx + 1].value);
        }
    }

    // Query method (private, recursive)
    T query(int node_idx, int start, int end, int l, int r) {
        push(node_idx, start, end); // Always push down before query

        if (start > end || start > r || end < l) {
            return identity;
        }

        if (l <= start && end <= r) {
            return tree[node_idx].value;
        }

        int mid = (start + end) / 2;
        T p1 = query(2 * node_idx, start, mid, l, r);
        T p2 = query(2 * node_idx + 1, mid + 1, end, l, r);
        return merge_values(p1, p2);
    }

    // Update method (private, recursive)
    void update(int node_idx, int start, int end, int l, int r, LazyT lazyVal) {
        push(node_idx, start, end); // Always push down before update

        if (start > end || start > r || end < l) {
            return;
        }

        if (l <= start && end <= r) {
            update_lazy(tree[node_idx], lazyVal);
            push(node_idx, start, end);
            return;
        }

        int mid = (start + end) / 2;
        update(2 * node_idx, start, mid, l, r, lazyVal);
        update(2 * node_idx + 1, mid + 1, end, l, r, lazyVal);

        tree[node_idx].value = merge_values(tree[2 * node_idx].value, tree[2 * node_idx + 1].value);
    }


    // Pushes lazy updates down to children
    void push(int node_idx, int start, int end) {
        if (tree[node_idx].has_lazy) {
            // Apply lazy tag to current node's value
            tree[node_idx].value = apply_lazy_to_value(tree[node_idx].value, tree[node_idx].lazy, (end - start + 1));

            // If not a leaf node, propagate to children
            if (start != end) {
                update_lazy(tree[2 * node_idx], tree[node_idx].lazy);
                update_lazy(tree[2 * node_idx + 1], tree[node_idx].lazy);
            }

            // Reset lazy tag and flag for current node
            tree[node_idx].has_lazy = false;
        }
    }

    // Applies the lazy to the given node.
    void update_lazy(Node &node, LazyT newLazy) {
        node.lazy = node.has_lazy ? combine_lazy(node.lazy, newLazy) : newLazy;
        node.has_lazy = true;
    }
};