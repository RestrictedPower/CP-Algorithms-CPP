template <long long mod> class Mint {
    void exgcd(long long a, long long b, long long& x, long long& y) const {
        if(b == 0) { x = 1, y = 0; return; }
        exgcd(b, a % b, x, y); long long tmp = y; y = x - a / b * y; x = tmp;
    }
public:
    long long v;
    operator long long() const { return v; }

    Mint():v(0) {}
    template <typename T> Mint(T _v) :v(_v % mod) { v = (v + mod) % mod; }

    template <typename T> Mint& operator=(T a) { *this = Mint(a); return *this; }
    Mint operator-() const { return Mint((-v + mod) % mod); }
    Mint& operator+=(Mint o) { v = (v + o.v) % mod; return *this; }
    Mint& operator-=(Mint o) { v = (v - o.v + mod) % mod; return *this; }
    Mint inv() const { assert(v != 0); long long x, y; exgcd(v, mod, x, y); return Mint((x + mod) % mod); }

    Mint& operator*=(Mint o) { v = v * o.v % mod; return *this; }
    Mint& operator/=(Mint o) { v = v * o.inv().v % mod; return *this; }

    Mint operator+(Mint o) const { return Mint((v + o.v) % mod); }
    Mint operator-(Mint o) const { return Mint((v - o.v + mod) % mod); }
    Mint operator*(Mint o) const { return Mint(v * o.v % mod); }
    Mint operator/(Mint o) const { return Mint(v * o.inv().v % mod); }

    template <typename T> Mint& operator+=(T o) { *this += Mint(o); return *this; }
    template <typename T> Mint& operator-=(T o) { *this -= Mint(o); return *this; }
    template <typename T> Mint& operator*=(T o) { *this *= Mint(o); return *this; }
    template <typename T> Mint& operator/=(T o) { *this /= Mint(o); return *this; }

    template <typename T> Mint operator+(T o) const { return *this + Mint(o); }
    template <typename T> Mint operator-(T o) const { return *this - Mint(o); }
    template <typename T> Mint operator*(T o) const { return *this * Mint(o); }
    template <typename T> Mint operator/(T o) const { return *this / Mint(o); }

    Mint& operator++() { v = (v + 1) % mod; return *this; }
    Mint& operator--() { v = (v - 1 + mod) % mod; return *this; }

    Mint operator++(int) { Mint old = *this; operator++(); return old; }
    Mint operator--(int) { Mint old = *this; operator--(); return old; }

    bool operator==(Mint o) const { return v == o.v; }
    bool operator!=(Mint o) const { return v != o.v; }

    template <typename T> bool operator==(T o) const { return *this == Mint(o); }
    template <typename T> bool operator!=(T o) const { return *this != Mint(o); }

    template <typename T> friend Mint operator+(T o, Mint x) { return x + o; }
    template <typename T> friend Mint operator-(T o, Mint x) { return Mint(o) - x; }
    template <typename T> friend Mint operator*(T o, Mint x) { return x * o; }
    template <typename T> friend Mint operator/(T o, Mint x) { return Mint(o) * x.inv(); }

    friend std::ostream& operator<<(std::ostream& os, Mint const& a) { return os << a.v; }
    friend std::istream& operator>>(std::istream& is, Mint& a) { long long x; is >> x; a = Mint(x); return is; }
};

using mint = Mint<MOD>;
