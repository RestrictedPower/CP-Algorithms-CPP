template <long long mod> class Mint {
    void exgcd(long long a, long long b, long long& x, long long& y) const {
        if (b == 0) { x = 1, y = 0; return; }
        exgcd(b, a % b, x, y); long long t = y; y = x - a / b * y; x = t;
    }
public:
    long long v;
    operator long long() const { return v; }

    Mint(): v(0) {}
    template <typename T> Mint(T _v): v((_v % mod + mod) % mod) {}

    // assignment
    template <typename T> Mint& operator=(T a) { *this = Mint(a); return *this; }

    // unary
    Mint operator-() const { return Mint(-v); }
    Mint& operator++() { v = (v + 1) % mod; return *this; }
    Mint& operator--() { v = (v - 1 + mod) % mod; return *this; }
    Mint operator++(int) { Mint t = *this; ++*this; return t; }
    Mint operator--(int) { Mint t = *this; --*this; return t; }

    // core compound ops (Mint)
    Mint& operator+=(Mint o) { v = (v + o.v) % mod; return *this; }
    Mint& operator-=(Mint o) { v = (v - o.v + mod) % mod; return *this; }
    Mint& operator*=(Mint o) { v = v * o.v % mod; return *this; }
    Mint& operator/=(Mint o) { return *this *= o.inv(); }

    // core binary ops (Mint)
    Mint operator+(Mint o) const { return Mint(v + o.v); }
    Mint operator-(Mint o) const { return Mint(v - o.v); }
    Mint operator*(Mint o) const { return Mint(v * o.v); }
    Mint operator/(Mint o) const { return *this * o.inv(); }

    // mixed compound ops (T)
    template <typename T> Mint& operator+=(T o) { return *this += Mint(o); }
    template <typename T> Mint& operator-=(T o) { return *this -= Mint(o); }
    template <typename T> Mint& operator*=(T o) { return *this *= Mint(o); }
    template <typename T> Mint& operator/=(T o) { return *this /= Mint(o); }

    // mixed binary ops (T on right)
    template <typename T> Mint operator+(T o) const { return *this + Mint(o); }
    template <typename T> Mint operator-(T o) const { return *this - Mint(o); }
    template <typename T> Mint operator*(T o) const { return *this * Mint(o); }
    template <typename T> Mint operator/(T o) const { return *this / Mint(o); }

    // comparisons
    bool operator==(Mint o) const { return v == o.v; }
    bool operator!=(Mint o) const { return v != o.v; }
    template <typename T> bool operator==(T o) const { return *this == Mint(o); }
    template <typename T> bool operator!=(T o) const { return *this != Mint(o); }

    // inverse
    Mint inv() const { long long x, y; exgcd(v, mod, x, y); return Mint((x + mod) % mod); }

    // reversed mixed binary ops (T on left)
    template <typename T> friend Mint operator+(T a, Mint b) { return b + a; }
    template <typename T> friend Mint operator-(T a, Mint b) { return Mint(a) - b; }
    template <typename T> friend Mint operator*(T a, Mint b) { return b * a; }
    template <typename T> friend Mint operator/(T a, Mint b) { return Mint(a) * b.inv(); }

    // IO
    friend std::ostream& operator<<(std::ostream& os, Mint const& a) { return os << a.v; }
    friend std::istream& operator>>(std::istream& is, Mint& a) { long long x; is >> x; a = Mint(x); return is; }
};

using mint = Mint<MOD>;